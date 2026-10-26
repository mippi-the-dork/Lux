// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class ULuxEditorSubsystem;

/** Native Level Editor toolbar split control and property menu. */
class SLuxViewportControl final : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SLuxViewportControl) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    enum class ENumberProperty : uint8
    {
        Intensity, AttenuationRadius, SourceRadius, Volumetric, Temperature, Specular
    };

    enum class EBooleanProperty : uint8
    {
        CastShadows, UseTemperature
    };

    ULuxEditorSubsystem* GetSubsystem() const;
    TSharedRef<SWidget> MakeSettingsMenu();
    TSharedRef<SWidget> MakeNumberRow(const FText& Label, const FText& Tooltip, ENumberProperty Property);
    TSharedRef<SWidget> MakeBooleanRow(const FText& Label, const FText& Tooltip, EBooleanProperty Property);
    TSharedRef<SWidget> MakeColorRow();
    TSharedRef<SWidget> MakeAdvancedContent();
    FReply OnColorClicked(const FGeometry& Geometry, const FPointerEvent& Event);
    float GetNumber(ENumberProperty Property) const;
    void SetNumber(ENumberProperty Property, float Value) const;
    TOptional<float> GetMinimum(ENumberProperty Property) const;
    TOptional<float> GetMaximum(ENumberProperty Property) const;
};
