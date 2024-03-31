// Made by Janek Puto :>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToolBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class INFINITEGARDENER_API AToolBase : public AActor
{
	GENERATED_BODY()
	
public:
	AToolBase();

	virtual void Tick(float DeltaTime) override;

	virtual void StartUsingTool();
	virtual void StopUsingTool();

protected:
	virtual void BeginPlay() override;


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Garden|Component")
	TObjectPtr<UStaticMeshComponent> MainMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Garden|Component")
	TObjectPtr<USceneComponent> RootComp;
};
