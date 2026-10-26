// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LuxProjectSettings.generated.h"

/** Project-wide bounds and reset values for the Level Editor headlamp. */
UCLASS(Config=Editor, DefaultConfig, meta=(DisplayName="Lux"))
class LUX_API ULuxProjectSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UPROPERTY(Config, EditAnywhere, Category="Intensity", meta=(ClampMin="0", UIMin="0", ToolTip="Lowest intensity allowed in the Lux viewport flyout."))
    float MinimumIntensity = 0.0f;

    UPROPERTY(Config, EditAnywhere, Category="Intensity", meta=(ClampMin="0", UIMin="0", ToolTip="Highest intensity allowed in the Lux viewport flyout."))
    float MaximumIntensity = 50000.0f;

    UPROPERTY(Config, EditAnywhere, Category="Intensity", meta=(ClampMin="0", UIMin="0", ToolTip="Intensity restored by Reset to Project Defaults."))
    float DefaultIntensity = 5000.0f;

    UPROPERTY(Config, EditAnywhere, Category="Attenuation Radius", meta=(ClampMin="0", UIMin="0", Units="cm", ToolTip="Smallest attenuation radius allowed in the Lux viewport flyout."))
    float MinimumAttenuationRadius = 0.0f;

    UPROPERTY(Config, EditAnywhere, Category="Attenuation Radius", meta=(ClampMin="0", UIMin="0", Units="cm", ToolTip="Largest attenuation radius allowed in the Lux viewport flyout."))
    float MaximumAttenuationRadius = 10000.0f;

    UPROPERTY(Config, EditAnywhere, Category="Attenuation Radius", meta=(ClampMin="0", UIMin="0", Units="cm", ToolTip="Attenuation radius restored by Reset to Project Defaults."))
    float DefaultAttenuationRadius = 1000.0f;

    UPROPERTY(Config, EditAnywhere, Category="Light Defaults", meta=(HideAlphaChannel, ToolTip="Color restored by Reset to Project Defaults."))
    FLinearColor DefaultLightColor = FLinearColor::White;

    UPROPERTY(Config, EditAnywhere, Category="Light Defaults", meta=(ToolTip="Whether the Lux point light casts dynamic shadows by default."))
    bool bDefaultCastShadows = true;

    UPROPERTY(Config, EditAnywhere, Category="Light Defaults", meta=(ClampMin="0", UIMin="0", Units="cm", ToolTip="Default point-light source radius for highlights and soft shadows."))
    float DefaultSourceRadius = 0.0f;

    UPROPERTY(Config, EditAnywhere, Category="Light Defaults", meta=(ClampMin="0", UIMin="0", ToolTip="Default contribution to volumetric fog."))
    float DefaultVolumetricScatteringIntensity = 0.0f;

    UPROPERTY(Config, EditAnywhere, Category="Advanced Defaults", meta=(ToolTip="Enable color temperature on the Lux light by default."))
    bool bDefaultUseTemperature = false;

    UPROPERTY(Config, EditAnywhere, Category="Advanced Defaults", meta=(ClampMin="1000", ClampMax="20000", UIMin="1700", UIMax="12000", EditCondition="bDefaultUseTemperature", ToolTip="Default temperature in Kelvin when Use Temperature is enabled."))
    float DefaultTemperature = 6500.0f;

    UPROPERTY(Config, EditAnywhere, Category="Advanced Defaults", meta=(ClampMin="0", ClampMax="1", UIMin="0", UIMax="1", ToolTip="Default specular highlight contribution."))
    float DefaultSpecularScale = 1.0f;

    // Explicit stable navigation IDs. Without GetSectionName(), Unreal registers
    // this section as "LuxProjectSettings", so ShowViewer(..., "Lux") only opens
    // the Project Settings window without selecting Lux.
    virtual FName GetContainerName() const override { return TEXT("Project"); }
    virtual FName GetCategoryName() const override { return TEXT("Plugins"); }
    virtual FName GetSectionName() const override { return TEXT("Lux"); }
    virtual FText GetSectionText() const override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
