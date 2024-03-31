// Made by Janek Puto :>

#include "InfiniteGardenerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "InfiniteGardenerProjectile.h"
#include "Engine/StreamableManager.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/LocalPlayer.h"
#include "InputActionValue.h"
#include "Tools/ToolBase.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AInfiniteGardenerCharacter

AInfiniteGardenerCharacter::AInfiniteGardenerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	HandlePoint = CreateDefaultSubobject<USceneComponent>(TEXT("HandlePoint"));
	HandlePoint->SetupAttachment(FirstPersonCameraComponent);

}

void AInfiniteGardenerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AInfiniteGardenerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInfiniteGardenerCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AInfiniteGardenerCharacter::Look);

		EnhancedInputComponent->BindAction(UseItemAction, ETriggerEvent::Started, this, &AInfiniteGardenerCharacter::StartUsingTool);
		EnhancedInputComponent->BindAction(UseItemAction, ETriggerEvent::Completed, this, &AInfiniteGardenerCharacter::StopUsingTool);

		EnhancedInputComponent->BindAction(EquipToolAction, ETriggerEvent::Completed, this, &AInfiniteGardenerCharacter::StopUsingTool);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AInfiniteGardenerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AInfiniteGardenerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AInfiniteGardenerCharacter::StartUsingTool()
{
	if (EquipedTool)
	{
		EquipedTool->StartUsingTool();
	}
}

void AInfiniteGardenerCharacter::StopUsingTool()
{
	if (EquipedTool)
	{
		EquipedTool->StopUsingTool();
	}
}

void AInfiniteGardenerCharacter::EquipNewTool(int32 NewToolIndex)
{
	if (EquipedTool)
	{
		EquipedTool->Destroy();
	}

	if (AvalibleTools.IsValidIndex(NewToolIndex))
	{
		if (!AvalibleTools[NewToolIndex].IsNull())
		{
			auto AsyncLoadlambda = [this, NewToolIndex]()
				{
					if (this)
					{
						AToolBase* NewTool = Cast< AToolBase>(GetWorld()->SpawnActor(AvalibleTools[NewToolIndex].LoadSynchronous()));
						if (NewTool)
						{
							NewTool->SetOwner(this);
							NewTool->AttachToComponent(HandlePoint, FAttachmentTransformRules::SnapToTargetIncludingScale);

							EquipedTool = NewTool;
						}
					}
				};

			FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

			TArray<FSoftObjectPath> ObjectsToLoad;
			ObjectsToLoad.Add(AvalibleTools[NewToolIndex].ToSoftObjectPath());

			FStreamableDelegate Delegate;
			Delegate.BindLambda(AsyncLoadlambda);

			Streamable.RequestAsyncLoad(ObjectsToLoad, Delegate);
		}
	}
}
