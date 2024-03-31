// Made by Janek Puto :>


#include "Tools/WateringCan.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectiles/WaterProjectile.h"
#include "InfiniteGardenerCharacter.h"
#include "Engine/AssetManager.h"

void AWateringCan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPourWater && WaterProjectileClass)
	{
		TimeSinceLastWaterCreated += DeltaTime;
		if (TimeSinceLastWaterCreated >= WaterSpawnInterval)
		{
			TimeSinceLastWaterCreated = 0;

			AInfiniteGardenerCharacter* PlayerOwner = Cast<AInfiniteGardenerCharacter>(GetOwner());
			if (PlayerOwner)
			{
				APlayerController const* const PlayerController = Cast<APlayerController>(PlayerOwner->GetController());
				FRotator const SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
				FVector const SpawnLocation = GetActorLocation();

				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				AWaterProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AWaterProjectile>(WaterProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}
}

void AWateringCan::StartUsingTool()
{
	bPourWater = true;
}

void AWateringCan::StopUsingTool()
{
	bPourWater = false;
}

void AWateringCan::BeginPlay()
{
	Super::BeginPlay();

	auto AsyncLoadlambda = [this]()
		{
			if (this)
			{
				WaterProjectileClass = SoftWaterProjectileClass.LoadSynchronous();
			}
		};

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

	TArray<FSoftObjectPath> ObjectsToLoad;
	ObjectsToLoad.Add(SoftWaterProjectileClass.ToSoftObjectPath());

	FStreamableDelegate Delegate;
	Delegate.BindLambda(AsyncLoadlambda);

	Streamable.RequestAsyncLoad(ObjectsToLoad, Delegate);

}
