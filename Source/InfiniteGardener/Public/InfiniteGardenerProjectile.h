// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InfiniteGardenerProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config = Game)
class AInfiniteGardenerProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = "Gardener")
	TObjectPtr < USphereComponent > CollisionComp = nullptr;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gardener", meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UProjectileMovementComponent > ProjectileMovement = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = "Gardener")
	TObjectPtr < UStaticMeshComponent > MainMesh = nullptr;

public:
	AInfiniteGardenerProjectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

protected:
	virtual void OnHitBehavoiur( FHitResult const& Hit);
};

