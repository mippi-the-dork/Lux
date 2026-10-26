// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Framework/Application/IInputProcessor.h"

class FLevelEditorViewportClient;
class SLevelViewport;

/** Records real viewport interactions, independent of GEditor's sometimes-stale active viewport. */
class FLuxViewportTracker
{
public:
    static void NotifyInteraction(const FVector2D& ScreenPosition);
    static FLevelEditorViewportClient* GetActivePerspectiveClient();
    static void Reset();

private:
    static TWeakPtr<SLevelViewport> LastInteractedViewport;
};

class FLuxInputProcessor final : public IInputProcessor
{
public:
    virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override {}
    virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& Event) override;
    virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& Event) override;
    virtual const TCHAR* GetDebugName() const override { return TEXT("LuxViewportInputProcessor"); }
};
