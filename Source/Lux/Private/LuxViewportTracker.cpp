// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#include "LuxViewportTracker.h"

#include "Editor.h"
#include "ILevelEditor.h"
#include "LevelEditor.h"
#include "LevelEditorViewport.h"
#include "Modules/ModuleManager.h"
#include "SLevelViewport.h"
#include "UnrealClient.h"
#include "Framework/Application/SlateApplication.h"

TWeakPtr<SLevelViewport> FLuxViewportTracker::LastInteractedViewport;

void FLuxViewportTracker::Reset()
{
    LastInteractedViewport.Reset();
}

void FLuxViewportTracker::NotifyInteraction(const FVector2D& ScreenPosition)
{
    FLevelEditorModule* Module = FModuleManager::GetModulePtr<FLevelEditorModule>(TEXT("LevelEditor"));
    if (!Module) return;
    TSharedPtr<ILevelEditor> LevelEditor = Module->GetFirstLevelEditor();
    if (!LevelEditor.IsValid()) return;

    // Same geometry-based matching approach as Metric, without a runtime dependency on it.
    for (const TSharedPtr<SLevelViewport>& Viewport : LevelEditor->GetViewports())
    {
        if (!Viewport.IsValid()) continue;
        const FGeometry& Geometry = Viewport->GetCachedGeometry();
        const FVector2D Local = Geometry.AbsoluteToLocal(ScreenPosition);
        const FVector2D Size = Geometry.GetLocalSize();
        if (Size.X > 8.0f && Size.Y > 8.0f && Local.X >= 0.0f && Local.Y >= 0.0f && Local.X < Size.X && Local.Y < Size.Y)
        {
            LastInteractedViewport = Viewport;
            return;
        }
    }
}

FLevelEditorViewportClient* FLuxViewportTracker::GetActivePerspectiveClient()
{
    FLevelEditorModule* Module = FModuleManager::GetModulePtr<FLevelEditorModule>(TEXT("LevelEditor"));
    if (!Module) return nullptr;
    TSharedPtr<ILevelEditor> LevelEditor = Module->GetFirstLevelEditor();
    if (!LevelEditor.IsValid()) return nullptr;

    const TArray<TSharedPtr<SLevelViewport>>& Viewports = LevelEditor->GetViewports();

    if (TSharedPtr<SLevelViewport> Tracked = LastInteractedViewport.Pin())
    {
        if (Viewports.Contains(Tracked))
        {
            FLevelEditorViewportClient& Client = Tracked->GetLevelViewportClient();
            // Orthographic interactions do not reposition the headlamp at the ortho camera.
            if (Client.IsPerspective()) return &Client;
            return nullptr;
        }
        LastInteractedViewport.Reset();
    }

    // First-run and layout-reset fallback. Never cast a non-LevelEditor viewport client.
    if (GEditor)
    {
        if (FViewport* Active = GEditor->GetActiveViewport())
        {
            FViewportClient* Client = Active->GetClient();
            for (const TSharedPtr<SLevelViewport>& Viewport : Viewports)
            {
                if (Viewport.IsValid() && &Viewport->GetLevelViewportClient() == Client)
                {
                    FLevelEditorViewportClient& LevelClient = Viewport->GetLevelViewportClient();
                    if (LevelClient.IsPerspective())
                    {
                        LastInteractedViewport = Viewport;
                        return &LevelClient;
                    }
                    return nullptr;
                }
            }
        }
    }

    for (const TSharedPtr<SLevelViewport>& Viewport : Viewports)
    {
        if (Viewport.IsValid())
        {
            FLevelEditorViewportClient& Client = Viewport->GetLevelViewportClient();
            if (Client.IsPerspective())
            {
                LastInteractedViewport = Viewport;
                return &Client;
            }
        }
    }
    return nullptr;
}

bool FLuxInputProcessor::HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& Event)
{
    FLuxViewportTracker::NotifyInteraction(Event.GetScreenSpacePosition());
    return false; // Never consume editor input.
}

bool FLuxInputProcessor::HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& Event)
{
    // The cursor can be over a viewport while navigating with keyboard controls.
    // If it is elsewhere, NotifyInteraction leaves the prior viewport unchanged.
    FLuxViewportTracker::NotifyInteraction(SlateApp.GetCursorPos());
    return false;
}
