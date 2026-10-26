// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#include "LuxStyle.h"
#include "Brushes/SlateImageBrush.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> FLuxStyle::StyleSet;

void FLuxStyle::Initialize()
{
    if (StyleSet.IsValid()) return;
    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("Lux"));
    if (!Plugin.IsValid()) return;

    StyleSet = MakeShared<FSlateStyleSet>(TEXT("LuxStyle"));
    StyleSet->SetContentRoot(FPaths::Combine(Plugin->GetBaseDir(), TEXT("Resources")));
    const FString Icon = StyleSet->RootToContentDir(TEXT("Lux"), TEXT(".svg"));
    StyleSet->Set(TEXT("Lux.ToolbarIcon"), new FSlateVectorImageBrush(Icon, FVector2D(16.0f, 16.0f)));
    FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

void FLuxStyle::Shutdown()
{
    if (!StyleSet.IsValid()) return;
    FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
    StyleSet.Reset();
}

const FSlateBrush* FLuxStyle::GetToolbarIcon()
{
    return StyleSet.IsValid() ? StyleSet->GetBrush(TEXT("Lux.ToolbarIcon")) : nullptr;
}
