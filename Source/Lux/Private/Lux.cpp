// Copyright Epic Games, Inc. All Rights Reserved.

#include "Lux.h"
#include "LuxEditorSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CheckBox.h"
#include "Components/MenuAnchor.h"
#include "Components/TextBlock.h"
#include "Editor.h"
#include "Engine/World.h"
#include "Templates/UnrealTemplate.h"
#include "Slate/SObjectWidget.h"
#include "ToolMenus.h"
#include "UObject/UObjectIterator.h"
#include "UObject/UObjectGlobals.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SNullWidget.h"

void FLuxModule::StartupModule()
{
	bShuttingDown = false;
	FEditorDelegates::OnEditorPreExit.AddRaw(this, &FLuxModule::HandleEditorPreExit);
	FWorldDelegates::OnWorldCleanup.AddRaw(this, &FLuxModule::HandleWorldCleanup);
	PanelTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateRaw(this, &FLuxModule::TickPanels));
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FLuxModule::RegisterMenus));
}

void FLuxModule::ShutdownModule()
{
	HandleEditorPreExit();
	FEditorDelegates::OnEditorPreExit.RemoveAll(this);
	FTSTicker::GetCoreTicker().RemoveTicker(PanelTickerHandle);
	FWorldDelegates::OnWorldCleanup.RemoveAll(this);
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	Panels.Reset();
	PanelAndMenuClasses.Reset();
}

void FLuxModule::HandleEditorPreExit()
{
	if (!bShuttingDown)
	{
		bShuttingDown = true;
		ReleasePanels(nullptr);
	}
}

void FLuxModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);
	UToolMenu* ViewportToolbar = UToolMenus::Get()->ExtendMenu("LevelEditor.ViewportToolbar");
	if (!ViewportToolbar)
	{
		return;
	}

	FToolMenuSection& RightSection = ViewportToolbar->FindOrAddSection("Right");
	FToolMenuEntry Entry = FToolMenuEntry::InitWidget(
		"LuxPanel", SNullWidget::NullWidget, FText::GetEmpty(),
		true /* bNoIndent */, false /* bSearchable */);

	Entry.MakeCustomWidget = FNewToolMenuCustomWidget::CreateLambda(
		[this](const FToolMenuContext&, const FToolMenuCustomWidgetContext&) -> TSharedRef<SWidget>
		{
			return MakePanelHost();
		});
	Entry.InsertPosition = FToolMenuInsert("Camera", EToolMenuInsertType::Before);
	RightSection.AddEntry(Entry);
}

TSharedRef<SWidget> FLuxModule::MakePanelHost()
{
	// The Slate host survives map changes. Its world-owned UMG content does not.
	TSharedRef<SBox> Host = SNew(SBox);
	FPanelInstance& Panel = Panels.AddDefaulted_GetRef();
	Panel.Host = Host;
	TickPanels(0.0f);
	return Host;
}

bool FLuxModule::TickPanels(float DeltaTime)
{
	if (bShuttingDown)
	{
		return false;
	}
	if (bRebuildingPanels || !GEditor || IsGarbageCollecting())
	{
		return true;
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!IsValid(World) || World->WorldType != EWorldType::Editor || World == UnloadingWorld.Get())
	{
		return true;
	}

	TGuardValue<bool> RebuildGuard(bRebuildingPanels, true);
	Panels.RemoveAll([](const FPanelInstance& Panel) { return !Panel.Host.IsValid(); });

	// Construct outside the Panels array: Blueprint Construct may itself rebuild a toolbar.
	TArray<TWeakPtr<SBox>> PendingHosts;
	for (const FPanelInstance& Panel : Panels)
	{
		if (!Panel.Widget.IsValid())
		{
			PendingHosts.Add(Panel.Host);
		}
	}
	if (PendingHosts.IsEmpty())
	{
		return true;
	}

	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Lux/EUW_LuxPanel.EUW_LuxPanel_C"));
	if (!WidgetClass)
	{
		return true;
	}
	PanelAndMenuClasses.Add(TWeakObjectPtr<UClass>(WidgetClass));

	for (const TWeakPtr<SBox>& WeakHost : PendingHosts)
	{
		TSharedPtr<SBox> Host = WeakHost.Pin();
		if (!Host.IsValid())
		{
			continue;
		}

		// Preserve the original world context used by Menu Anchor's Menu Class creation.
		UUserWidget* Widget = CreateWidget<UUserWidget>(World, WidgetClass);
		if (!Widget)
		{
			continue;
		}

		if (Widget->WidgetTree)
		{
			Widget->WidgetTree->ForEachWidget([this](UWidget* Child)
				{
					if (UMenuAnchor* Anchor = Cast<UMenuAnchor>(Child))
					{
						if (Anchor->MenuClass)
						{
							PanelAndMenuClasses.Add(TWeakObjectPtr<UClass>(Anchor->MenuClass.Get()));
						}
					}
				});
		}

		for (FPanelInstance& Panel : Panels)
		{
			if (Panel.Host.Pin() == Host)
			{
				Panel.Widget = Widget;
				break;
			}
		}
		Host->SetContent(Widget->TakeWidget());

		// Reflect the existing headlamp state after reconstructing the toolbar.
		if (ULuxEditorSubsystem* Subsystem = GEditor->GetEditorSubsystem<ULuxEditorSubsystem>())
		{
			const bool bEnabled = Subsystem->IsHeadlampActive();
			if (UCheckBox* Toggle = Cast<UCheckBox>(Widget->GetWidgetFromName(TEXT("Toggle_Lux"))))
			{
				Toggle->SetIsChecked(bEnabled);
			}
			if (bEnabled)
			{
				if (UTextBlock* Label = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("Text_LuxLabel"))))
				{
					Label->SetColorAndOpacity(FSlateColor(FLinearColor::White));
				}
			}
		}
	}
	return true;
}

void FLuxModule::HandleWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources)
{
	if (World && World->WorldType == EWorldType::Editor)
	{
		// Do not reconstruct against the old world while it is still in GEditor's context.
		UnloadingWorld = World;
		ReleasePanels(World);
	}
}

void FLuxModule::ReleasePanels(UWorld* World)
{
	// Include flyouts, which Menu Anchor creates separately from the panel's widget tree.
	// Only touch Lux classes discovered from our own panels and their Menu Class settings.
	TArray<TWeakObjectPtr<UUserWidget>> WidgetsToRelease;
	for (TObjectIterator<UUserWidget> It; It; ++It)
	{
		UUserWidget* Widget = *It;
		if (!IsValid(Widget) || Widget->IsTemplate() ||
			!PanelAndMenuClasses.Contains(TWeakObjectPtr<UClass>(Widget->GetClass())))
		{
			continue;
		}
		if (!World || Widget->GetTypedOuter<UWorld>() == World)
		{
			WidgetsToRelease.Add(Widget);
		}
	}

	// Close Lux menus before severing their Slate-to-UObject references.
	for (const TWeakObjectPtr<UUserWidget>& WeakWidget : WidgetsToRelease)
	{
		if (UUserWidget* Widget = WeakWidget.Get())
		{
			if (Widget->WidgetTree)
			{
				Widget->WidgetTree->ForEachWidget([](UWidget* Child)
					{
						if (UMenuAnchor* Anchor = Cast<UMenuAnchor>(Child))
						{
							Anchor->Close();
						}
					});
			}
		}
	}

	for (const TWeakObjectPtr<UUserWidget>& WeakWidget : WidgetsToRelease)
	{
		if (UUserWidget* Widget = WeakWidget.Get())
		{
			TSharedPtr<SWidget> CachedSlateWidget = Widget->GetCachedWidget();
			if (CachedSlateWidget.IsValid() && CachedSlateWidget->GetType() == FName(TEXT("SObjectWidget")))
			{
				// Slate focus or menu history may retain the wrapper after it leaves the toolbar.
				StaticCastSharedPtr<SObjectWidget>(CachedSlateWidget)->ResetWidget();
			}
			Widget->ReleaseSlateResources(true);
		}
	}

	for (FPanelInstance& Panel : Panels)
	{
		UUserWidget* Widget = Panel.Widget.Get();
		if (!World || !Widget || Widget->GetTypedOuter<UWorld>() == World)
		{
			if (TSharedPtr<SBox> Host = Panel.Host.Pin())
			{
				Host->SetContent(SNullWidget::NullWidget);
			}
			Panel.Widget.Reset();
		}
	}
}

IMPLEMENT_MODULE(FLuxModule, Lux)
