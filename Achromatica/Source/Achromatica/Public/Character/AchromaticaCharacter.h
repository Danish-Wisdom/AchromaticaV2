// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "AchromaticaCharacter.generated.h"

class UCameraComponent;

UCLASS()
class ACHROMATICA_API AAchromaticaCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	AAchromaticaCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	void Move(const FVector2D& MoveAxis);
	void Look(const FVector2D& LookAxis);
	
	void InstantJump(const float& JumpHeight);

	void Attack();


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Settings", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 200.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Settings", meta = (AllowPrivateAccess = "true"))
	float StrafeSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Settings", meta = (AllowPrivateAccess = "true"))
	float HorizontalRotationSpeed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Settings", meta = (AllowPrivateAccess = "true"))
	float VerticalRotationSpeed = 10.f;

	bool bLockControllerRotation = false;
public:

	
};
