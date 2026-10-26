// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"

class FSlateStyleSet;
struct FSlateBrush;

class FLuxStyle
{
public:
    static void Initialize();
    static void Shutdown();
    static const FSlateBrush* GetToolbarIcon();

private:
    static TSharedPtr<FSlateStyleSet> StyleSet;
};
