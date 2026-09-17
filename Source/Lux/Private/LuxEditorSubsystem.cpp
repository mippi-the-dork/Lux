#include "LuxEditorSubsystem.h"
#include "LevelEditor.h"
#include "EditorViewportClient.h"
#include "IAssetViewport.h" // Needed for modern UE 5.8 viewport pointers
#include "Editor.h"
#include "Engine/World.h"

void ULuxEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	FWorldDelegates::OnWorldCleanup.AddUObject(this, &ULuxEditorSubsystem::HandleWorldCleanup);
}

void ULuxEditorSubsystem::Deinitialize()
{
	FWorldDelegates::OnWorldCleanup.RemoveAll(this);
	bIsHeadlampActive = false;
	DestroyLight();
	UnloadingWorld.Reset();
	Super::Deinitialize();
}

void ULuxEditorSubsystem::SetHeadlampState(bool bNewState)
{
	bIsHeadlampActive = bNewState;

	if (bIsHeadlampActive)
	{
		EnsureLight();
	}
	else
	{
		DestroyLight();
	}
}

void ULuxEditorSubsystem::EnsureLight()
{
	if (!bIsHeadlampActive || !GEditor)
	{
		return;
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!IsValid(World) || World->WorldType != EWorldType::Editor || World == UnloadingWorld.Get())
	{
		return;
	}

	if (IsValid(TransientLightComponent) && LightWorld.Get() == World)
	{
		return;
	}

	DestroyLight();
	LightWorld = World;
	TransientLightComponent = NewObject<UPointLightComponent>(GetTransientPackage(), NAME_None, RF_Transient);
	TransientLightComponent->SetMobility(EComponentMobility::Movable);
	TransientLightComponent->SetIntensity(CachedIntensity);
	TransientLightComponent->SetLightColor(CachedColor);
	TransientLightComponent->SetAttenuationRadius(CachedRadius);
	TransientLightComponent->RegisterComponentWithWorld(World);
}

void ULuxEditorSubsystem::HandleWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources)
{
	// Ignore PIE and preview worlds, and release the light before the old map is collected.
	if (World && (World == LightWorld.Get() ||
		(GEditor && World == GEditor->GetEditorWorldContext().World())))
	{
		UnloadingWorld = World;
		DestroyLight();
		// Keep the user's enabled state and settings. Tick recreates the light in the next editor world.
	}
}

void ULuxEditorSubsystem::UpdateLightSettings(float Intensity, FLinearColor Color, float Radius)
{
	CachedIntensity = Intensity;
	CachedColor = Color;
	CachedRadius = Radius;

	if (TransientLightComponent)
	{
		TransientLightComponent->SetIntensity(CachedIntensity);
		TransientLightComponent->SetLightColor(CachedColor);
		TransientLightComponent->SetAttenuationRadius(CachedRadius);

		// CRITICAL FIX: Forces the runtime rendering proxy to reconstruct mid-frame
		TransientLightComponent->MarkRenderStateDirty();

		// FORCES ALL 3D VIEWS TO RE-RENDER INSTANTLY ON SLIDER VALUE SHIFTS
		if (GEditor)
		{
			GEditor->RedrawLevelEditingViewports();
		}
	}
}

void ULuxEditorSubsystem::DestroyLight()
{
	UPointLightComponent* LightToDestroy = TransientLightComponent;
	TransientLightComponent = nullptr;
	LightWorld.Reset();
	if (IsValid(LightToDestroy))
	{
		LightToDestroy->DestroyComponent();
	}
}

void ULuxEditorSubsystem::Tick(float DeltaTime)
{
	if (!bIsHeadlampActive)
	{
		return;
	}

	if (!FModuleManager::Get().IsModuleLoaded("LevelEditor"))
	{
		return;
	}

	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");

	// FIXED FOR UE 5.8: Active viewports now utilize the IAssetViewport type interface
	TSharedPtr<IAssetViewport> ActiveViewport = LevelEditorModule.GetFirstActiveViewport();

	if (ActiveViewport.IsValid())
	{
		// FIXED FOR UE 5.8: Pull via GetAssetViewportClient() instead of GetLevelViewportClient()
		FEditorViewportClient& ViewportClient = ActiveViewport->GetAssetViewportClient();
		UWorld* EditorWorld = GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
		if (!IsValid(EditorWorld) || EditorWorld == UnloadingWorld.Get() ||
			ViewportClient.GetWorld() != EditorWorld)
		{
			return;
		}

		EnsureLight();
		if (!IsValid(TransientLightComponent))
		{
			return;
		}

		FVector ViewLocation = ViewportClient.GetViewLocation();
		FRotator ViewRotation = ViewportClient.GetViewRotation(); // Fixed typo here

		TransientLightComponent->SetWorldLocationAndRotation(ViewLocation, ViewRotation);
	}
}
