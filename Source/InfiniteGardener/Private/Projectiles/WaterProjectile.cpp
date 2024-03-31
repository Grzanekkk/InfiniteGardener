// Made by Janek Puto :>


#include "Projectiles/WaterProjectile.h"
#include "Plants/PlantBase.h"

void AWaterProjectile::OnHitBehavoiur(FHitResult const& Hit)
{
	if (APlantBase* const PlantHit = Cast<APlantBase>(Hit.GetActor()))
	{
		PlantHit->Grow();
	}
}
