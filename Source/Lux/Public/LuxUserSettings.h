// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LuxUserSettings.generated.h"

/** Editor-local preferences. These are deliberately NOT stored in shared project defaults. */
UCLASS(Config=EditorPerProjectUserSettings)
class LUX_API ULuxUserSettings : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(Config) bool bInitializedFromProject = false;
    UPROPERTY(Config) float Intensity = 5000.0f;
    UPROPERTY(Config) float AttenuationRadius = 1000.0f;
    UPROPERTY(Config) FLinearColor Color = FLinearColor::White;
    UPROPERTY(Config) bool bCastShadows = true;
    UPROPERTY(Config) float SourceRadius = 0.0f;
    UPROPERTY(Config) float VolumetricScatteringIntensity = 0.0f;
    UPROPERTY(Config) bool bUseTemperature = false;
    UPROPERTY(Config) float Temperature = 6500.0f;
    UPROPERTY(Config) float SpecularScale = 1.0f;
};
