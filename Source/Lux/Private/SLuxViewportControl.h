// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateTypes.h"
#include "Widgets/SCompoundWidget.h"

class FMenuBuilder;

class ULuxEditorSubsystem;

/** Native Level Editor toolbar split control and property menu. */
class SLuxViewportControl final : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SLuxViewportControl) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    // The native combo style is copied per widget so we can tighten arrow
    // padding without changing the global Unreal Editor style.
    FComboButtonStyle CompactDropdownStyle;

    enum class ENumberProperty : uint8
    {
        Intensity, AttenuationRadius, SourceRadius, Volumetric, IndirectLighting, Temperature, Specular
    };

    enum class EBooleanProperty : uint8
    {
        CastShadows, AffectTranslucentLighting, UseTemperature
    };

    ULuxEditorSubsystem* GetSubsystem() const;
    TSharedRef<SWidget> MakeSettingsMenu();
    TSharedRef<SWidget> MakeNumberRow(const FText& Label, const FText& Tooltip, ENumberProperty Property, bool bAdvanced = false);
    TSharedRef<SWidget> MakeBooleanRow(const FText& Label, const FText& Tooltip, EBooleanProperty Property, bool bAdvanced = false);
    TSharedRef<SWidget> MakeColorRow();
    void PopulateAdvancedMenu(FMenuBuilder& MenuBuilder);
    FReply OnColorClicked(const FGeometry& Geometry, const FPointerEvent& Event);
    float GetNumber(ENumberProperty Property) const;
    void SetNumber(ENumberProperty Property, float Value) const;
    TOptional<float> GetMinimum(ENumberProperty Property) const;
    TOptional<float> GetMaximum(ENumberProperty Property) const;
};
