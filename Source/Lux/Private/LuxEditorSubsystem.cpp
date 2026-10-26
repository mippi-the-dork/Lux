// Copyright Mippithedork 2026, Inc. All Rights Reserved.
#include "LuxEditorSubsystem.h"

#include "LuxProjectSettings.h"
#include "LuxUserSettings.h"
#include "LuxViewportTracker.h"

#include "Components/PointLightComponent.h"
#include "Editor.h"
#include "Engine/World.h"
#include "HAL/PlatformTime.h"
#include "LevelEditorViewport.h"

namespace
{
    const ULuxProjectSettings* ProjectSettings()
    {
        return GetDefault<ULuxProjectSettings>();
    }
}

void ULuxEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    CachedPreferences = GetMutableDefault<ULuxUserSettings>();
    if (CachedPreferences && !CachedPreferences->bInitializedFromProject)
    {
        ResetToProjectDefaults();
    }
    RefreshProjectLimits();
    FWorldDelegates::OnWorldCleanup.AddUObject(this, &ULuxEditorSubsystem::HandleWorldCleanup);
}

void ULuxEditorSubsystem::Deinitialize()
{
    FWorldDelegates::OnWorldCleanup.RemoveAll(this);
    bEnabled = false;
    DestroyLight();
    SavePreferences();
    CachedPreferences = nullptr;
    Super::Deinitialize();
}

float ULuxEditorSubsystem::GetIntensity() const { return CachedPreferences ? CachedPreferences->Intensity : 5000.0f; }
float ULuxEditorSubsystem::GetAttenuationRadius() const { return CachedPreferences ? CachedPreferences->AttenuationRadius : 1000.0f; }
FLinearColor ULuxEditorSubsystem::GetLightColor() const { return CachedPreferences ? CachedPreferences->Color : FLinearColor::White; }
bool ULuxEditorSubsystem::GetCastShadows() const { return CachedPreferences ? CachedPreferences->bCastShadows : true; }
float ULuxEditorSubsystem::GetSourceRadius() const { return CachedPreferences ? CachedPreferences->SourceRadius : 0.0f; }
float ULuxEditorSubsystem::GetVolumetricScatteringIntensity() const { return CachedPreferences ? CachedPreferences->VolumetricScatteringIntensity : 0.0f; }
bool ULuxEditorSubsystem::GetUseTemperature() const { return CachedPreferences ? CachedPreferences->bUseTemperature : false; }
float ULuxEditorSubsystem::GetTemperature() const { return CachedPreferences ? CachedPreferences->Temperature : 6500.0f; }
float ULuxEditorSubsystem::GetSpecularScale() const { return CachedPreferences ? CachedPreferences->SpecularScale : 1.0f; }

void ULuxEditorSubsystem::MarkPreferencesDirty()
{
    bPreferencesDirty = true;
    LastPreferenceChangeSeconds = FPlatformTime::Seconds();
}

void ULuxEditorSubsystem::SavePreferences()
{
    if (bPreferencesDirty && CachedPreferences)
    {
        CachedPreferences->SaveConfig();
        bPreferencesDirty = false;
    }
}

void ULuxEditorSubsystem::SetIntensity(float Value)
{
    if (!CachedPreferences) return;
    const ULuxProjectSettings* Settings = ProjectSettings();
    Value = FMath::Clamp(Value, FMath::Max(0.0f, Settings->MinimumIntensity), FMath::Max(Settings->MinimumIntensity, Settings->MaximumIntensity));
    if (FMath::IsNearlyEqual(Value, CachedPreferences->Intensity)) return;
    CachedPreferences->Intensity = Value;
    MarkPreferencesDirty();
    if (IsValid(TransientLightComponent)) TransientLightComponent->SetIntensity(Value);
}

void ULuxEditorSubsystem::SetAttenuationRadius(float Value)
{
    if (!CachedPreferences) return;
    const ULuxProjectSettings* Settings = ProjectSettings();
    Value = FMath::Clamp(Value, FMath::Max(0.0f, Settings->MinimumAttenuationRadius), FMath::Max(Settings->MinimumAttenuationRadius, Settings->MaximumAttenuationRadius));
    if (FMath::IsNearlyEqual(Value, CachedPreferences->AttenuationRadius)) return;
    CachedPreferences->AttenuationRadius = Value;
    MarkPreferencesDirty();
    if (IsValid(TransientLightComponent)) TransientLightComponent->SetAttenuationRadius(Value);
}

void ULuxEditorSubsystem::SetLightColor(FLinearColor Value)
{
    if (!CachedPreferences) return;
    Value.A = 1.0f;
    if (CachedPreferences->Color.Equals(Value)) return;
    CachedPreferences->Color = Value;
    MarkPreferencesDirty();
    if (IsValid(TransientLightComponent)) TransientLightComponent->SetLightColor(Value);
}

void ULuxEditorSubsystem::SetCastShadows(bool bValue)
{
    if (!CachedPreferences || CachedPreferences->bCastShadows == bValue) return;
    CachedPreferences->bCastShadows = bValue;
    MarkPreferencesDirty();
    if (IsValid(TransientLightComponent)) TransientLightComponent->SetCastShadows(bValue);
}

void ULuxEditorSubsystem::SetSourceRadius(float Value)
{
    if (!CachedPreferences) return;
    Value = FMath::Clamp(Value, 0.0f, 10000.0f);
    if (FMath::IsNearlyEqual(Value, CachedPreferences->SourceRadius)) return;
    CachedPreferences->SourceRadius = Value;
    MarkPreferencesDirty();
    if (IsValid(TransientLightComponent)) TransientLightComponent->SetSourceRadius(Value);
}

void ULuxEditorSubsystem::SetVolumetricScatteringIntensity(float Value)
{
    if (!CachedPreferences) return;
    Value = FMath::Clamp(Value, 0.0f, 100.0f);
    if (FMath::IsNearlyEqual(Value, CachedPreferences->VolumetricScatteringIntensity)) return;
    CachedPreferences->VolumetricScatteringIntensity = Value;
    MarkPreferencesDirty();
    if (IsValid(TransientLightComponent)) TransientLightComponent->SetVolumetricScatteringIntensity(Value);
}

void ULuxEditorSubsystem::SetUseTemperature(bool bValue)
{
    if (!CachedPreferences || CachedPreferences->bUseTemperature == bValue) return;
    CachedPreferences->bUseTemperature = bValue;
    MarkPreferencesDirty();
    if (IsValid(TransientLightComponent)) TransientLightComponent->SetUseTemperature(bValue);
}

void ULuxEditorSubsystem::SetTemperature(float Value)
{
    if (!CachedPreferences) return;
    Value = FMath::Clamp(Value, 1000.0f, 20000.0f);
    if (FMath::IsNearlyEqual(Value, CachedPreferences->Temperature)) return;
    CachedPreferences->Temperature = Value;
    MarkPreferencesDirty();
    if (IsValid(TransientLightComponent)) TransientLightComponent->SetTemperature(Value);
}

void ULuxEditorSubsystem::SetSpecularScale(float Value)
{
    if (!CachedPreferences) return;
    Value = FMath::Clamp(Value, 0.0f, 1.0f);
    if (FMath::IsNearlyEqual(Value, CachedPreferences->SpecularScale)) return;
    CachedPreferences->SpecularScale = Value;
    MarkPreferencesDirty();
    if (IsValid(TransientLightComponent)) TransientLightComponent->SetSpecularScale(Value);
}

void ULuxEditorSubsystem::ResetToProjectDefaults()
{
    if (!CachedPreferences) return;
    const ULuxProjectSettings* Settings = ProjectSettings();
    CachedPreferences->bInitializedFromProject = true;
    CachedPreferences->Intensity = FMath::Clamp(Settings->DefaultIntensity, Settings->MinimumIntensity, Settings->MaximumIntensity);
    CachedPreferences->AttenuationRadius = FMath::Clamp(Settings->DefaultAttenuationRadius, Settings->MinimumAttenuationRadius, Settings->MaximumAttenuationRadius);
    CachedPreferences->Color = Settings->DefaultLightColor;
    CachedPreferences->Color.A = 1.0f;
    CachedPreferences->bCastShadows = Settings->bDefaultCastShadows;
    CachedPreferences->SourceRadius = FMath::Clamp(Settings->DefaultSourceRadius, 0.0f, 10000.0f);
    CachedPreferences->VolumetricScatteringIntensity = FMath::Clamp(Settings->DefaultVolumetricScatteringIntensity, 0.0f, 100.0f);
    CachedPreferences->bUseTemperature = Settings->bDefaultUseTemperature;
    CachedPreferences->Temperature = FMath::Clamp(Settings->DefaultTemperature, 1000.0f, 20000.0f);
    CachedPreferences->SpecularScale = FMath::Clamp(Settings->DefaultSpecularScale, 0.0f, 1.0f);
    MarkPreferencesDirty();
    ApplyLightSettings();
}

void ULuxEditorSubsystem::RefreshProjectLimits()
{
    if (!CachedPreferences) return;
    // Clamp existing user preferences if the project owner changes the allowed bounds.
    SetIntensity(CachedPreferences->Intensity);
    SetAttenuationRadius(CachedPreferences->AttenuationRadius);
}

void ULuxEditorSubsystem::SetHeadlampState(bool bNewEnabled)
{
    if (bEnabled == bNewEnabled) return;
    bEnabled = bNewEnabled;
    if (bEnabled)
    {
        EnsureLight();
    }
    else
    {
        DestroyLight();
    }
    if (GEditor)
    {
        GEditor->RedrawLevelEditingViewports();
    }
}

void ULuxEditorSubsystem::EnsureLight()
{
    if (!bEnabled || !GEditor) return;
    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!IsValid(World) || World->WorldType != EWorldType::Editor || World == UnloadingWorld.Get()) return;
    if (IsValid(TransientLightComponent) && LightWorld.Get() == World) return;

    // Avoid registering a bright light at the world origin for one frame.
    FLevelEditorViewportClient* ActiveClient = FLuxViewportTracker::GetActivePerspectiveClient();
    if (!ActiveClient || ActiveClient->GetWorld() != World) return;

    DestroyLight();
    LightWorld = World;
    TransientLightComponent = NewObject<UPointLightComponent>(GetTransientPackage(), NAME_None, RF_Transient);
    TransientLightComponent->SetMobility(EComponentMobility::Movable);
    TransientLightComponent->SetWorldLocation(ActiveClient->GetViewLocation());
    ApplyLightSettings();
    TransientLightComponent->RegisterComponentWithWorld(World);
}

void ULuxEditorSubsystem::ApplyLightSettings()
{
    if (!IsValid(TransientLightComponent)) return;

    TransientLightComponent->SetIntensity(GetIntensity());
    TransientLightComponent->SetAttenuationRadius(GetAttenuationRadius());
    TransientLightComponent->SetLightColor(GetLightColor());
    TransientLightComponent->SetCastShadows(GetCastShadows());
    TransientLightComponent->SetSourceRadius(GetSourceRadius());
    TransientLightComponent->SetVolumetricScatteringIntensity(GetVolumetricScatteringIntensity());
    TransientLightComponent->SetUseTemperature(GetUseTemperature());
    TransientLightComponent->SetTemperature(GetTemperature());
    TransientLightComponent->SetSpecularScale(GetSpecularScale());

    if (TransientLightComponent->IsRegistered() && GEditor)
    {
        GEditor->RedrawLevelEditingViewports();
    }
}

void ULuxEditorSubsystem::HandleWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources)
{
    if (World && World->WorldType == EWorldType::Editor &&
        (World == LightWorld.Get() || (GEditor && World == GEditor->GetEditorWorldContext().World())))
    {
        UnloadingWorld = World;
        DestroyLight();
        // Enabled state is retained through map changes, but the old world is not.
    }
}

void ULuxEditorSubsystem::DestroyLight()
{
    UPointLightComponent* OldLight = TransientLightComponent.Get();
    TransientLightComponent = nullptr;
    LightWorld.Reset();
    if (IsValid(OldLight))
    {
        OldLight->DestroyComponent();
    }
}

void ULuxEditorSubsystem::Tick(float DeltaTime)
{
    if (bPreferencesDirty && FPlatformTime::Seconds() - LastPreferenceChangeSeconds > 0.5)
    {
        SavePreferences();
    }
    if (!bEnabled || !GEditor) return;

    UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();
    if (!IsValid(EditorWorld) || EditorWorld->WorldType != EWorldType::Editor || EditorWorld == UnloadingWorld.Get()) return;

    FLevelEditorViewportClient* ViewportClient = FLuxViewportTracker::GetActivePerspectiveClient();
    if (!ViewportClient || !ViewportClient->IsPerspective() || ViewportClient->GetWorld() != EditorWorld) return;

    EnsureLight();
    if (!IsValid(TransientLightComponent)) return;

    const FVector CameraPosition = ViewportClient->GetViewLocation();
    if (!TransientLightComponent->GetComponentLocation().Equals(CameraPosition, 0.01))
    {
        // Point lights are omnidirectional. Camera rotation is deliberately ignored.
        TransientLightComponent->SetWorldLocation(CameraPosition);
    }
}
