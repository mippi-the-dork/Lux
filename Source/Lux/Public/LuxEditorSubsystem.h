#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Components/PointLightComponent.h"
#include "TickableEditorObject.h"
#include "LuxEditorSubsystem.generated.h"

UCLASS(BlueprintType)
class ULuxEditorSubsystem : public UEditorSubsystem, public FTickableEditorObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// FTickableEditorObject Interface implementation
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return bIsHeadlampActive && !IsTemplate(); }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(ULuxEditorSubsystem, STATGROUP_Tickables); }

	UFUNCTION(BlueprintCallable, Category = "Lux")
	void SetHeadlampState(bool bNewState);

	UFUNCTION(BlueprintCallable, Category = "Lux")
	bool IsHeadlampActive() const { return bIsHeadlampActive; }

	UFUNCTION(BlueprintCallable, Category = "Lux")
	void UpdateLightSettings(float Intensity, FLinearColor Color, float Radius);

	// MOVED TO PUBLIC WITH UPROPERTY: Exposes variables cleanly to your flyout UI initialization logic
	UPROPERTY(BlueprintReadOnly, Category = "Lux")
	float CachedIntensity = 5000.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lux")
	FLinearColor CachedColor = FLinearColor::White;

	UPROPERTY(BlueprintReadOnly, Category = "Lux")
	float CachedRadius = 1000.0f;

private:
	UPROPERTY(Transient)
	UPointLightComponent* TransientLightComponent = nullptr;

	bool bIsHeadlampActive = false;

	// Weak references must not keep an unloaded editor world alive.
	TWeakObjectPtr<UWorld> LightWorld;
	TWeakObjectPtr<UWorld> UnloadingWorld;

	void EnsureLight();
	void HandleWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);
	void DestroyLight();
};
