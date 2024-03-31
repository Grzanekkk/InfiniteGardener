// Made by Janek Puto :>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "InfiniteGardenerCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

class AToolBase;

UCLASS(config = Game)
class AInfiniteGardenerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AInfiniteGardenerCharacter();

protected:
	virtual void BeginPlay();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:
	void Move(FInputActionValue const& Value);
	void Look(FInputActionValue const& Value);

	UFUNCTION(BlueprintCallable)
	void StartUsingTool();

	UFUNCTION(BlueprintCallable)
	void StopUsingTool();

	UFUNCTION(BlueprintCallable)
	void EquipNewTool(int32 NewToolIndex);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> HandlePoint = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UseItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipToolAction;

	UPROPERTY()
	TObjectPtr<AToolBase> EquipedTool = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Gardener")
	TArray<TSoftClassPtr<AToolBase>> AvalibleTools;

	UPROPERTY()
	FString ToolSnapPointName = "GripPoint";
};

