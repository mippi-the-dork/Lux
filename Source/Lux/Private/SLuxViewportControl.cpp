// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#include "SLuxViewportControl.h"

#include "LuxEditorSubsystem.h"
#include "LuxProjectSettings.h"
#include "LuxStyle.h"

#include "Editor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ISettingsModule.h"
#include "InputCoreTypes.h"
#include "Modules/ModuleManager.h"
#include "Styling/AppStyle.h"
#include "Styling/SlateColor.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Colors/SColorPicker.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "LuxViewportControl"

namespace
{
    // Keep the widget rows visually close to the native viewport menus: fairly
    // compact, lightly padded, and wide enough for the native property names.
    // Keep the everyday controls close to the width of other native viewport
    // menus. Use a separate width for Advanced because its labels are longer.
    // Preserve the numeric field widths and label/value column alignment.
    constexpr float MainValueColumnWidth = 124.0f;
    constexpr float MainPropertyRowWidth = 320.0f;
    // Longer Advanced property names need more horizontal space than the
    // everyday controls, and must not make the main flyout any wider.
    constexpr float AdvancedValueColumnWidth = 104.0f;
    constexpr float AdvancedPropertyRowWidth = 328.0f;
    const FMargin PropertyRowPadding(8.0f, 2.0f, 8.0f, 2.0f);

    ULuxEditorSubsystem* FindLuxSubsystem()
    {
        return GEditor ? GEditor->GetEditorSubsystem<ULuxEditorSubsystem>() : nullptr;
    }
}

ULuxEditorSubsystem* SLuxViewportControl::GetSubsystem() const
{
    return FindLuxSubsystem();
}

void SLuxViewportControl::Construct(const FArguments& InArgs)
{
    // Retain native editor Slate styling but tighten the gap between the
    // toolbar icon and arrow. Both halves share one explicit visual height.
    // Copy the combo style so its arrow padding is local to Lux only.
    constexpr float ToolbarControlHeight = 24.0f;
    const FButtonStyle& ToolbarButtonStyle = FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton");
    CompactDropdownStyle = FAppStyle::Get().GetWidgetStyle<FComboButtonStyle>("ComboButton");
    CompactDropdownStyle.SetButtonStyle(ToolbarButtonStyle);
    CompactDropdownStyle.SetContentPadding(FMargin(0.0f));
    CompactDropdownStyle.SetDownArrowPadding(FMargin(2.0f, 0.0f, 3.0f, 0.0f));

    ChildSlot
    [
        SNew(SHorizontalBox)
        + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
        [
            SNew(SBox)
            .HeightOverride(ToolbarControlHeight)
            [
                // Preserve independent native hover/pressed behavior: clicking
                // the SVG toggles Lux, while the neighboring arrow opens settings.
                SNew(SButton)
                .ButtonStyle(&ToolbarButtonStyle)
                .ContentPadding(FMargin(3.0f, 3.0f, 1.0f, 3.0f))
                .ToolTipText_Lambda([this]()
                {
                    const ULuxEditorSubsystem* Subsystem = GetSubsystem();
                    return Subsystem && Subsystem->IsHeadlampActive()
                        ? LOCTEXT("DisableHeadlamp", "Lux: Disable editor headlamp")
                        : LOCTEXT("EnableHeadlamp", "Lux: Enable editor headlamp");
                })
                .OnClicked_Lambda([this]() -> FReply
                {
                    if (ULuxEditorSubsystem* Subsystem = GetSubsystem())
                    {
                        Subsystem->SetHeadlampState(!Subsystem->IsHeadlampActive());
                    }
                    return FReply::Handled();
                })
                [
                    SNew(SImage)
                    .Image(FLuxStyle::GetToolbarIcon())
                    .ColorAndOpacity_Lambda([this]() -> FSlateColor
                    {
                        const ULuxEditorSubsystem* Subsystem = GetSubsystem();
                        return FSlateColor(Subsystem && Subsystem->IsHeadlampActive()
                            ? EStyleColor::AccentBlue : EStyleColor::Foreground);
                    })
                ]
            ]
        ]
        + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
        [
            SNew(SBox)
            .HeightOverride(ToolbarControlHeight)
            [
                SNew(SComboButton)
                .ComboButtonStyle(&CompactDropdownStyle)
                .ContentPadding(FMargin(0.0f))
                .ToolTipText(LOCTEXT("SettingsTooltip", "Lux headlamp settings"))
                .HasDownArrow(true)
                .OnGetMenuContent(this, &SLuxViewportControl::MakeSettingsMenu)
                .ButtonContent()
                [
                    // The native arrow is supplied by the FComboButtonStyle;
                    // this slot only ensures a consistent vertical center.
                    SNew(SBox)
                    .WidthOverride(0.0f)
                    .HeightOverride(16.0f)
                ]
            ]
        ]
    ];
}

float SLuxViewportControl::GetNumber(ENumberProperty Property) const
{
    const ULuxEditorSubsystem* Subsystem = GetSubsystem();
    if (!Subsystem) return 0.0f;
    switch (Property)
    {
    case ENumberProperty::Intensity: return Subsystem->GetIntensity();
    case ENumberProperty::AttenuationRadius: return Subsystem->GetAttenuationRadius();
    case ENumberProperty::SourceRadius: return Subsystem->GetSourceRadius();
    case ENumberProperty::Volumetric: return Subsystem->GetVolumetricScatteringIntensity();
    case ENumberProperty::IndirectLighting: return Subsystem->GetIndirectLightingIntensity();
    case ENumberProperty::Temperature: return Subsystem->GetTemperature();
    case ENumberProperty::Specular: return Subsystem->GetSpecularScale();
    }
    return 0.0f;
}

void SLuxViewportControl::SetNumber(ENumberProperty Property, float Value) const
{
    ULuxEditorSubsystem* Subsystem = GetSubsystem();
    if (!Subsystem) return;
    switch (Property)
    {
    case ENumberProperty::Intensity: Subsystem->SetIntensity(Value); break;
    case ENumberProperty::AttenuationRadius: Subsystem->SetAttenuationRadius(Value); break;
    case ENumberProperty::SourceRadius: Subsystem->SetSourceRadius(Value); break;
    case ENumberProperty::Volumetric: Subsystem->SetVolumetricScatteringIntensity(Value); break;
    case ENumberProperty::IndirectLighting: Subsystem->SetIndirectLightingIntensity(Value); break;
    case ENumberProperty::Temperature: Subsystem->SetTemperature(Value); break;
    case ENumberProperty::Specular: Subsystem->SetSpecularScale(Value); break;
    }
}

TOptional<float> SLuxViewportControl::GetMinimum(ENumberProperty Property) const
{
    const ULuxProjectSettings* Settings = GetDefault<ULuxProjectSettings>();
    if (Property == ENumberProperty::Intensity) return FMath::Max(0.0f, Settings->MinimumIntensity);
    if (Property == ENumberProperty::AttenuationRadius) return FMath::Max(0.0f, Settings->MinimumAttenuationRadius);
    if (Property == ENumberProperty::Temperature) return 1000.0f;
    return 0.0f;
}

TOptional<float> SLuxViewportControl::GetMaximum(ENumberProperty Property) const
{
    const ULuxProjectSettings* Settings = GetDefault<ULuxProjectSettings>();
    if (Property == ENumberProperty::Intensity) return FMath::Max(Settings->MinimumIntensity, Settings->MaximumIntensity);
    if (Property == ENumberProperty::AttenuationRadius) return FMath::Max(Settings->MinimumAttenuationRadius, Settings->MaximumAttenuationRadius);
    if (Property == ENumberProperty::SourceRadius) return 10000.0f;
    if (Property == ENumberProperty::Volumetric) return 100.0f;
    if (Property == ENumberProperty::IndirectLighting) return 6.0f;
    if (Property == ENumberProperty::Temperature) return 20000.0f;
    return 1.0f;
}

TSharedRef<SWidget> SLuxViewportControl::MakeNumberRow(const FText& Label, const FText& Tooltip, ENumberProperty Property, bool bAdvanced)
{
    const bool bCentimeters = Property == ENumberProperty::AttenuationRadius || Property == ENumberProperty::SourceRadius;
    const bool bKelvin = Property == ENumberProperty::Temperature;
    return SNew(SBox)
        .WidthOverride(bAdvanced ? AdvancedPropertyRowWidth : MainPropertyRowWidth)
        .Padding(PropertyRowPadding)
        [
            SNew(SHorizontalBox)
            .IsEnabled_Lambda([this, Property]()
            {
                if (Property != ENumberProperty::Temperature) return true;
                const ULuxEditorSubsystem* Subsystem = GetSubsystem();
                return Subsystem && Subsystem->GetUseTemperature();
            })
            + SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(0.0f, 0.0f, 8.0f, 0.0f)
            [
                SNew(STextBlock).Text(Label).ToolTipText(Tooltip)
            ]
            + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
            [
                SNew(SBox).WidthOverride(bAdvanced ? AdvancedValueColumnWidth : MainValueColumnWidth)
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center)
                    [
                        SNew(SNumericEntryBox<float>)
                        .AllowSpin(true)
                        .MinFractionalDigits(TOptional<int32>(0))
                        .MaxFractionalDigits(TOptional<int32>(2))
                        .MinValue_Lambda([this, Property]() { return GetMinimum(Property); })
                        .MaxValue_Lambda([this, Property]() { return GetMaximum(Property); })
                        .MinSliderValue_Lambda([this, Property]() { return GetMinimum(Property); })
                        .MaxSliderValue_Lambda([this, Property]() { return GetMaximum(Property); })
                        .Value_Lambda([this, Property]() -> TOptional<float> { return GetNumber(Property); })
                        .OnValueChanged_Lambda([this, Property](float Value) { SetNumber(Property, Value); })
                        .OnValueCommitted_Lambda([this, Property](float Value, ETextCommit::Type) { SetNumber(Property, Value); })
                        .ToolTipText(Tooltip)
                    ]
                    + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f, 0.0f, 0.0f)
                    [
                        SNew(STextBlock)
                        .Text(bCentimeters ? LOCTEXT("Centimeters", "cm") : (bKelvin ? LOCTEXT("KelvinUnit", "K") : FText::GetEmpty()))
                        .ColorAndOpacity(FSlateColor(EStyleColor::Foreground))
                        .Visibility((bCentimeters || bKelvin) ? EVisibility::Visible : EVisibility::Collapsed)
                    ]
                ]
            ]
        ];
}

TSharedRef<SWidget> SLuxViewportControl::MakeColorRow()
{
    return SNew(SBox)
        .WidthOverride(MainPropertyRowWidth)
        .Padding(PropertyRowPadding)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(0.0f, 0.0f, 8.0f, 0.0f)
            [
                SNew(STextBlock)
                .Text(LOCTEXT("LightColor", "Light Color"))
                .ToolTipText(LOCTEXT("ColorTooltip", "Choose the headlamp color using Unreal's color picker."))
            ]
            + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
            [
                SNew(SBox).WidthOverride(MainValueColumnWidth).HAlign(HAlign_Left)
                [
                    SNew(SColorBlock)
                    .Size(FVector2D(MainValueColumnWidth, 18.0f))
                    .ShowBackgroundForAlpha(false)
                    .Color_Lambda([this]()
                    {
                        const ULuxEditorSubsystem* Subsystem = GetSubsystem();
                        return Subsystem ? Subsystem->GetLightColor() : FLinearColor::White;
                    })
                    .OnMouseButtonDown(this, &SLuxViewportControl::OnColorClicked)
                    .ToolTipText(LOCTEXT("ColorTooltip", "Choose the headlamp color using Unreal's color picker."))
                ]
            ]
        ];
}

FReply SLuxViewportControl::OnColorClicked(const FGeometry& Geometry, const FPointerEvent& Event)
{
    if (Event.GetEffectingButton() != EKeys::LeftMouseButton) return FReply::Unhandled();
    ULuxEditorSubsystem* Subsystem = GetSubsystem();
    if (!Subsystem) return FReply::Unhandled();

    TWeakObjectPtr<ULuxEditorSubsystem> WeakSubsystem = Subsystem;
    FColorPickerArgs Picker;
    Picker.bUseAlpha = false;
    Picker.bIsModal = false;
    Picker.InitialColor = Subsystem->GetLightColor();
    Picker.ParentWidget = AsShared();
    Picker.OnColorCommitted = FOnLinearColorValueChanged::CreateLambda([WeakSubsystem](FLinearColor Color)
    {
        if (ULuxEditorSubsystem* Target = WeakSubsystem.Get())
        {
            Target->SetLightColor(Color);
        }
    });
    OpenColorPicker(Picker);
    return FReply::Handled();
}

TSharedRef<SWidget> SLuxViewportControl::MakeBooleanRow(const FText& Label, const FText& Tooltip, EBooleanProperty Property, bool bAdvanced)
{
    return SNew(SBox)
        .WidthOverride(bAdvanced ? AdvancedPropertyRowWidth : MainPropertyRowWidth)
        .Padding(PropertyRowPadding)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(0.0f, 0.0f, 8.0f, 0.0f)
            [
                SNew(STextBlock).Text(Label).ToolTipText(Tooltip)
            ]
            + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
            [
                SNew(SBox).WidthOverride(bAdvanced ? AdvancedValueColumnWidth : MainValueColumnWidth).HAlign(HAlign_Left)
                [
                    SNew(SCheckBox)
                    .IsChecked_Lambda([this, Property]()
                    {
                        const ULuxEditorSubsystem* Subsystem = GetSubsystem();
                        if (!Subsystem) return ECheckBoxState::Unchecked;
                        bool bChecked = false;
                        switch (Property)
                        {
                        case EBooleanProperty::CastShadows: bChecked = Subsystem->GetCastShadows(); break;
                        case EBooleanProperty::AffectTranslucentLighting: bChecked = Subsystem->GetAffectTranslucentLighting(); break;
                        case EBooleanProperty::UseTemperature: bChecked = Subsystem->GetUseTemperature(); break;
                        }

                        return bChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
                    })
                    .OnCheckStateChanged_Lambda([this, Property](ECheckBoxState State)
                    {
                        if (ULuxEditorSubsystem* Subsystem = GetSubsystem())
                        {
                            switch (Property)
                            {
                            case EBooleanProperty::CastShadows: Subsystem->SetCastShadows(State == ECheckBoxState::Checked); break;
                            case EBooleanProperty::AffectTranslucentLighting: Subsystem->SetAffectTranslucentLighting(State == ECheckBoxState::Checked); break;
                            case EBooleanProperty::UseTemperature: Subsystem->SetUseTemperature(State == ECheckBoxState::Checked); break;
                            }
                        }
                    })
                    .ToolTipText(Tooltip)
                ]
            ]
        ];
}

void SLuxViewportControl::PopulateAdvancedMenu(FMenuBuilder& MenuBuilder)
{
    // Native submenu sections clarify related properties without repeating the
    // word "Advanced" as an unnecessary secondary heading.
    MenuBuilder.BeginSection(NAME_None, LOCTEXT("AdvancedLightingSection", "Lighting"));
    MenuBuilder.AddWidget(MakeNumberRow(LOCTEXT("SourceRadius", "Source Radius"),
        LOCTEXT("SourceRadiusTooltip", "Physical radius of the light source, affecting highlights and supported shadow methods."),
        ENumberProperty::SourceRadius, true), FText::GetEmpty(), true, false);
    MenuBuilder.AddWidget(MakeNumberRow(LOCTEXT("Volumetric", "Volumetric Scattering Intensity"),
        LOCTEXT("VolumetricTooltip", "Controls how strongly the headlamp contributes to volumetric fog."),
        ENumberProperty::Volumetric, true), FText::GetEmpty(), true, false);
    MenuBuilder.AddWidget(MakeNumberRow(LOCTEXT("Indirect", "Indirect Lighting Intensity"),
        LOCTEXT("IndirectTooltip", "Multiplier for indirect lighting from Lux, where supported by the scene's lighting and renderer. 0 disables its indirect contribution."),
        ENumberProperty::IndirectLighting, true), FText::GetEmpty(), true, false);
    MenuBuilder.AddWidget(MakeNumberRow(LOCTEXT("Specular", "Specular Scale"),
        LOCTEXT("SpecularTooltip", "Multiplier for specular reflections produced by the headlamp (0 to 1)."),
        ENumberProperty::Specular, true), FText::GetEmpty(), true, false);
    MenuBuilder.AddWidget(MakeBooleanRow(LOCTEXT("AffectTranslucent", "Affect Translucent Lighting"),
        LOCTEXT("AffectTranslucentTooltip", "Controls Lux's contribution to supported translucent materials. May affect lighting performance."),
        EBooleanProperty::AffectTranslucentLighting, true), FText::GetEmpty(), true, false);
    MenuBuilder.EndSection();

    MenuBuilder.BeginSection(NAME_None, LOCTEXT("TemperatureSection", "Temperature"));
    MenuBuilder.AddWidget(MakeBooleanRow(LOCTEXT("UseTemperature", "Use Temperature"),
        LOCTEXT("UseTemperatureTooltip", "Multiply Light Color by a blackbody temperature tint."),
        EBooleanProperty::UseTemperature, true), FText::GetEmpty(), true, false);
    MenuBuilder.AddWidget(MakeNumberRow(LOCTEXT("Temperature", "Temperature"),
        LOCTEXT("TemperatureTooltip", "Color temperature in Kelvin when Use Temperature is enabled."),
        ENumberProperty::Temperature, true), FText::GetEmpty(), true, false);
    MenuBuilder.EndSection();
}

TSharedRef<SWidget> SLuxViewportControl::MakeSettingsMenu()
{
    // Native MultiBox sections, submenus, separators, and actionable menu
    // entries. The property editors remain native Slate widgets with
    // Details-like alignment, but the overall menu structure follows the
    // viewport toolbar's native menu grammar.
    FMenuBuilder MenuBuilder(true, nullptr);

    MenuBuilder.BeginSection(NAME_None, LOCTEXT("HeadlampSection", "Headlamp"));
    MenuBuilder.AddWidget(MakeNumberRow(LOCTEXT("Intensity", "Intensity"),
        LOCTEXT("IntensityTooltip", "Point light intensity. Drag the value to scrub. Bounds are configured in Lux Project Settings."),
        ENumberProperty::Intensity), FText::GetEmpty(), true, false);
    MenuBuilder.AddWidget(MakeNumberRow(LOCTEXT("Attenuation", "Attenuation Radius"),
        LOCTEXT("RadiusTooltip", "Maximum influence radius of the headlamp. Bounds are configured in Lux Project Settings."),
        ENumberProperty::AttenuationRadius), FText::GetEmpty(), true, false);
    MenuBuilder.AddWidget(MakeColorRow(), FText::GetEmpty(), true, false);
    MenuBuilder.AddWidget(MakeBooleanRow(LOCTEXT("CastShadows", "Cast Shadows"),
        LOCTEXT("CastShadowsTooltip", "Whether the movable point light casts dynamic shadows."),
        EBooleanProperty::CastShadows), FText::GetEmpty(), true, false);
    MenuBuilder.EndSection();

    // Advanced contains all secondary controls, rather than splitting them
    // between an "Additional Properties" section and a separate submenu.
    MenuBuilder.AddSubMenu(
        LOCTEXT("Advanced", "Advanced"),
        LOCTEXT("AdvancedTooltip", "Open additional Lux headlamp properties."),
        FNewMenuDelegate::CreateSP(this, &SLuxViewportControl::PopulateAdvancedMenu),
        false,
        FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Settings"));

    // Native separation of editable properties from commands.
    MenuBuilder.AddMenuSeparator();
    MenuBuilder.BeginSection(NAME_None, FText::GetEmpty());
    MenuBuilder.AddMenuEntry(
        LOCTEXT("Reset", "Reset to Project Defaults"),
        LOCTEXT("ResetTooltip", "Restore all headlamp properties to the defaults configured in Project Settings > Plugins > Lux."),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateLambda([]()
        {
            if (ULuxEditorSubsystem* Subsystem = FindLuxSubsystem())
            {
                Subsystem->ResetToProjectDefaults();
            }
        })));
    MenuBuilder.AddMenuEntry(
        LOCTEXT("ProjectSettings", "Lux Project Settings"),
        LOCTEXT("ProjectSettingsTooltip", "Open Project Settings directly to Plugins > Lux."),
        FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Settings"),
        FUIAction(FExecuteAction::CreateLambda([]()
        {
            if (ISettingsModule* Settings = FModuleManager::LoadModulePtr<ISettingsModule>(TEXT("Settings")))
            {
                // This is a real registered identifier, matched by ULuxProjectSettings::GetSectionName().
                Settings->ShowViewer(TEXT("Project"), TEXT("Plugins"), TEXT("Lux"));
            }
        })));
    MenuBuilder.EndSection();

    return MenuBuilder.MakeWidget();
}

#undef LOCTEXT_NAMESPACE
