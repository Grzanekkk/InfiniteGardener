// Made by Janek Puto :>


#include "Tools/SeedBag.h"
#include "Engine/AssetManager.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "InfiniteGardenerCharacter.h"
#include "Projectiles/SeedProjectile.h"

void ASeedBag::StartUsingTool()
{
	auto AsyncLoadlambda = [this]()
		{
			if (this)
			{
				AInfiniteGardenerCharacter* PlayerOwner = Cast<AInfiniteGardenerCharacter>(GetOwner());
				if (PlayerOwner)
				{
					APlayerController* PlayerController = Cast<APlayerController>(PlayerOwner->GetController());
					FRotator const SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
					FVector const SpawnLocation = GetActorLocation();

					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

					ASeedProjectile* SpawnedProjectile = GetWorld()->SpawnActor<ASeedProjectile>(SoftSeedProjectileClass.LoadSynchronous(), SpawnLocation, SpawnRotation, ActorSpawnParams);
				}
			}
		};

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> ObjectsToLoad;
	ObjectsToLoad.Add(SoftSeedProjectileClass.ToSoftObjectPath());

	FStreamableDelegate Delegate;
	Delegate.BindLambda(AsyncLoadlambda);

	Streamable.RequestAsyncLoad(ObjectsToLoad, Delegate);
}
