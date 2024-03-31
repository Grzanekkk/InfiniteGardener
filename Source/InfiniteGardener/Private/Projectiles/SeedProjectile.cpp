// Made by Janek Puto :>


#include "Projectiles/SeedProjectile.h"
#include "Engine/AssetManager.h"
#include "Plants/PlantBase.h"

void ASeedProjectile::OnHitBehavoiur(FHitResult const& Hit)
{
	int32 PlantToSpawnIndex = FMath::RandRange(0, AvaliblePlants.Num());

	if (AvaliblePlants.IsValidIndex(PlantToSpawnIndex))
	{
		if (!AvaliblePlants[PlantToSpawnIndex].IsNull())
		{
			auto AsyncLoadlambda = [this, PlantToSpawnIndex, Hit]()
				{
					if (this)
					{
						APlantBase* NewPlant = Cast< APlantBase>(GetWorld()->SpawnActor(AvaliblePlants[PlantToSpawnIndex].LoadSynchronous(), &Hit.Location));
					}
				};

			FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

			TArray<FSoftObjectPath> ObjectsToLoad;
			ObjectsToLoad.Add(AvaliblePlants[PlantToSpawnIndex].ToSoftObjectPath());

			FStreamableDelegate Delegate;
			Delegate.BindLambda(AsyncLoadlambda);

			Streamable.RequestAsyncLoad(ObjectsToLoad, Delegate);
		}
	}
}
