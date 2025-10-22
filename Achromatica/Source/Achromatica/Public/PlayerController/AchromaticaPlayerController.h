// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Character/AchromaticaCharacter.h"
#include "GameFramework/PlayerController.h"
#include "AchromaticaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ACHROMATICA_API AAchromaticaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAchromaticaPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* TestMappingContext = nullptr;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ControllerLookAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	float ControllerDeadZone = 0.1f;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AAchromaticaCharacter> ControlledCharacter = nullptr;


	
	void HandleMoveAction(const FInputActionValue& Value);
	void HandleLookAction(const FInputActionValue& Value);
	void HandleControllerLookAction(const FInputActionValue& Value);
	
	void HandleJumpAction(const FInputActionValue& Value);
	void HandleAttackAction(const FInputActionValue& Value);
};
