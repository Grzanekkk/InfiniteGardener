// Made by Janek Puto :>

#include "Tools/ToolBase.h"

AToolBase::AToolBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	SetRootComponent(RootComp);

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>("MainMesh");
	MainMesh->SetupAttachment(RootComponent);
}

void AToolBase::BeginPlay()
{
	Super::BeginPlay();

}

void AToolBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AToolBase::StartUsingTool()
{

}

void AToolBase::StopUsingTool()
{

}

