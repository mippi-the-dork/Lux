// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "TickableEditorObject.h"
#include "LuxEditorSubsystem.generated.h"

class UPointLightComponent;
class UWorld;
class ULuxUserSettings;

/** Manages exactly one transient point light in the editor world. */
UCLASS()
class LUX_API ULuxEditorSubsystem final : public UEditorSubsystem, public FTickableEditorObject
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override { return !IsTemplate() && (bEnabled || bPreferencesDirty); }
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(ULuxEditorSubsystem, STATGROUP_Tickables); }

    bool IsHeadlampActive() const { return bEnabled; }
    void SetHeadlampState(bool bNewEnabled);
    void ToggleHeadlamp() { SetHeadlampState(!bEnabled); }

    float GetIntensity() const;
    float GetAttenuationRadius() const;
    FLinearColor GetLightColor() const;
    bool GetCastShadows() const;
    float GetSourceRadius() const;
    float GetVolumetricScatteringIntensity() const;
    bool GetUseTemperature() const;
    float GetTemperature() const;
    float GetSpecularScale() const;

    void SetIntensity(float Value);
    void SetAttenuationRadius(float Value);
    void SetLightColor(FLinearColor Value);
    void SetCastShadows(bool bValue);
    void SetSourceRadius(float Value);
    void SetVolumetricScatteringIntensity(float Value);
    void SetUseTemperature(bool bValue);
    void SetTemperature(float Value);
    void SetSpecularScale(float Value);

    void ResetToProjectDefaults();
    void RefreshProjectLimits();

private:
    void EnsureLight();
    void ApplyLightSettings();
    void DestroyLight();
    void HandleWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);
    void MarkPreferencesDirty();
    void SavePreferences();

    UPROPERTY(Transient)
    TObjectPtr<UPointLightComponent> TransientLightComponent;

    UPROPERTY(Transient)
    TObjectPtr<ULuxUserSettings> CachedPreferences;

    TWeakObjectPtr<UWorld> LightWorld;
    TWeakObjectPtr<UWorld> UnloadingWorld;
    bool bEnabled = false; // Deliberately session-only, starts off after restart.
    bool bPreferencesDirty = false;
    double LastPreferenceChangeSeconds = 0.0;
};
