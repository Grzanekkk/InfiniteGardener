// Made by Janek Puto :>


#include "Plants/PlantBase.h"

// Sets default values
APlantBase::APlantBase()
{
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	SetRootComponent(MainMesh);
}

void APlantBase::Grow()
{
	if (MainMesh)
	{
		FVector CurrentScale = MainMesh->GetComponentScale();

		CurrentScale += FVector(GrowSpeed);

		MainMesh->SetWorldScale3D(CurrentScale);
	}
}
