// Made by Janek Puto :>

#pragma once

#include "CoreMinimal.h"
#include "Tools/ToolBase.h"
#include "WateringCan.generated.h"

class AWaterProjectile;

/**
 *
 */
UCLASS()
class INFINITEGARDENER_API AWateringCan : public AToolBase
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	virtual void StartUsingTool() override;
	virtual void StopUsingTool() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	bool bPourWater = false;

	UPROPERTY()
	float TimeSinceLastWaterCreated = 0;

	UPROPERTY()
	float WaterSpawnInterval = 0.1;

	UPROPERTY(EditAnywhere, Category = "Gardener")
	TSoftClassPtr<AWaterProjectile> SoftWaterProjectileClass = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Gardener")
	TSubclassOf<AWaterProjectile> WaterProjectileClass = nullptr;
};

