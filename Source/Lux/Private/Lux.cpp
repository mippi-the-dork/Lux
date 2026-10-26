// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#include "Lux.h"
#include "LuxStyle.h"
#include "LuxViewportTracker.h"
#include "SLuxViewportControl.h"

#include "Framework/Application/SlateApplication.h"
#include "ToolMenus.h"
#include "Widgets/SNullWidget.h"

void FLuxModule::StartupModule()
{
    FLuxStyle::Initialize();
    if (FSlateApplication::IsInitialized())
    {
        InputProcessor = MakeShared<FLuxInputProcessor>();
        FSlateApplication::Get().RegisterInputPreProcessor(InputProcessor, 0);
    }
    UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FLuxModule::RegisterMenus));
}

void FLuxModule::ShutdownModule()
{
    UToolMenus::UnRegisterStartupCallback(this);
    UToolMenus::UnregisterOwner(this);
    if (FSlateApplication::IsInitialized() && InputProcessor.IsValid())
    {
        FSlateApplication::Get().UnregisterInputPreProcessor(InputProcessor);
    }
    InputProcessor.Reset();
    FLuxViewportTracker::Reset();
    FLuxStyle::Shutdown();
}

void FLuxModule::RegisterMenus()
{
    FToolMenuOwnerScoped OwnerScoped(this);
    UToolMenu* Toolbar = UToolMenus::Get()->ExtendMenu(TEXT("LevelEditor.ViewportToolbar"));
    if (!Toolbar) return;
    // The right-hand viewport controls are a RIGHT-aligned toolbar section.
    // The desired position is its leftmost entry, not the editor's left toolbar.
    FToolMenuSection& Right = Toolbar->FindOrAddSection(TEXT("Right"));

    FToolMenuEntry Entry = FToolMenuEntry::InitWidget(
        TEXT("LuxViewportControl"), SNullWidget::NullWidget, FText::GetEmpty(), true, false, true);
    Entry.MakeCustomWidget = FNewToolMenuCustomWidget::CreateLambda(
        [](const FToolMenuContext&, const FToolMenuCustomWidgetContext&) -> TSharedRef<SWidget>
        {
            return SNew(SLuxViewportControl);
        });
    // Put Lux at the beginning of the right-aligned group: left of all other
    // entries in that group, while the entire group remains anchored right.
    // Unlike anchoring before Camera/Link, First is independent of their
    // dynamic entries and the order in which other plugins register.
    Entry.InsertPosition = FToolMenuInsert(NAME_None, EToolMenuInsertType::First);
    Right.AddEntry(Entry);
}

IMPLEMENT_MODULE(FLuxModule, Lux)
