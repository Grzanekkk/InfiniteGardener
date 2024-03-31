// Made by Janek Puto :>

#pragma once

#include "CoreMinimal.h"
#include "Tools/ToolBase.h"
#include "SeedBag.generated.h"

class ASeedProjectile;

/**
 *
 */
UCLASS()
class INFINITEGARDENER_API ASeedBag : public AToolBase
{
	GENERATED_BODY()

public:
	virtual void StartUsingTool() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Gardener")
	TSoftClassPtr<ASeedProjectile> SoftSeedProjectileClass = nullptr;
};
