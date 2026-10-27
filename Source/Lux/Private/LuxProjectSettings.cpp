// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#include "LuxProjectSettings.h"

#if WITH_EDITOR
#include "Editor.h"
#include "LuxEditorSubsystem.h"
#endif

#define LOCTEXT_NAMESPACE "LuxProjectSettings"

FText ULuxProjectSettings::GetSectionText() const
{
    return LOCTEXT("LuxSection", "Lux");
}

#if WITH_EDITOR
void ULuxProjectSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    MinimumIntensity = FMath::Max(0.0f, MinimumIntensity);
    MaximumIntensity = FMath::Max(MinimumIntensity, MaximumIntensity);
    DefaultIntensity = FMath::Clamp(DefaultIntensity, MinimumIntensity, MaximumIntensity);

    MinimumAttenuationRadius = FMath::Max(0.0f, MinimumAttenuationRadius);
    MaximumAttenuationRadius = FMath::Max(MinimumAttenuationRadius, MaximumAttenuationRadius);
    DefaultAttenuationRadius = FMath::Clamp(DefaultAttenuationRadius, MinimumAttenuationRadius, MaximumAttenuationRadius);

    DefaultSourceRadius = FMath::Max(0.0f, DefaultSourceRadius);
    DefaultVolumetricScatteringIntensity = FMath::Clamp(DefaultVolumetricScatteringIntensity, 0.0f, 100.0f);
    DefaultIndirectLightingIntensity = FMath::Clamp(DefaultIndirectLightingIntensity, 0.0f, 6.0f);
    DefaultTemperature = FMath::Clamp(DefaultTemperature, 1000.0f, 20000.0f);
    DefaultSpecularScale = FMath::Clamp(DefaultSpecularScale, 0.0f, 1.0f);

    Super::PostEditChangeProperty(PropertyChangedEvent);
    if (GEditor)
    {
        if (ULuxEditorSubsystem* Subsystem = GEditor->GetEditorSubsystem<ULuxEditorSubsystem>())
        {
            Subsystem->RefreshProjectLimits();
        }
    }
}
#endif

#undef LOCTEXT_NAMESPACE
