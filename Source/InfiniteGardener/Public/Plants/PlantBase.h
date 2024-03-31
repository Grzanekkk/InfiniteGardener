// Made by Janek Puto :>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlantBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class INFINITEGARDENER_API APlantBase : public AActor
{
	GENERATED_BODY()

public:
	APlantBase();

	void Grow();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Gardener")
	TObjectPtr < UStaticMeshComponent > MainMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gardener")
	float GrowSpeed = 0.2;
};
