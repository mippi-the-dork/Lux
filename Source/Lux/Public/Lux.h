// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "Modules/ModuleManager.h"

class SBox;
class SWidget;
class UUserWidget;
class UWorld;

class FLuxModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	struct FPanelInstance
	{
		TWeakPtr<SBox> Host;
		TWeakObjectPtr<UUserWidget> Widget;
	};

	void RegisterMenus();
	void HandleEditorPreExit();
	TSharedRef<SWidget> MakePanelHost();
	bool TickPanels(float DeltaTime);
	void HandleWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);
	void ReleasePanels(UWorld* World);

	TArray<FPanelInstance> Panels;
	TSet<TWeakObjectPtr<UClass>> PanelAndMenuClasses;
	TWeakObjectPtr<UWorld> UnloadingWorld;
	FTSTicker::FDelegateHandle PanelTickerHandle;
	bool bShuttingDown = false;
	bool bRebuildingPanels = false;
};
