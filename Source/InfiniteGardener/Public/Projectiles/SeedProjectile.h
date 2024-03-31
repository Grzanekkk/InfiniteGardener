// Made by Janek Puto :>

#pragma once

#include "CoreMinimal.h"
#include "InfiniteGardenerProjectile.h"
#include "SeedProjectile.generated.h"

class APlantBase;

/**
 *
 */
UCLASS()
class INFINITEGARDENER_API ASeedProjectile : public AInfiniteGardenerProjectile
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Gardener")
	TArray<TSoftClassPtr<APlantBase>> AvaliblePlants;

protected:
	virtual void OnHitBehavoiur(FHitResult const& Hit) override;
};
