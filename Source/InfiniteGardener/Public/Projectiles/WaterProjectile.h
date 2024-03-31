// Made by Janek Puto :>

#pragma once

#include "CoreMinimal.h"
#include "InfiniteGardenerProjectile.h"
#include "WaterProjectile.generated.h"

/**
 * 
 */
UCLASS()
class INFINITEGARDENER_API AWaterProjectile : public AInfiniteGardenerProjectile
{
	GENERATED_BODY()
	
protected:
	virtual void OnHitBehavoiur(FHitResult const& Hit) override;
};
