// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"


#include "AchromaticaCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UAchromaticaAttributeSet;
class UAchromaticaAbilitySystemComp;

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


	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(const float& CurrentHealth, const float& MaxHealth);

	UFUNCTION(BlueprintImplementableEvent)
	void OnStaminaChanged(const float& CurrentStamina, const float& MaxStamina);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnManaChanged(const float& CurrentMana, const float& MaxMana);

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

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAchromaticaAbilitySystemComp> AbilitySystemComp;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAchromaticaAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, Category = "Custom Values|Character Tags")
	FGameplayTag CharacterTag;

	void InitAbilityActorInfo();
	void InitClassDefaults();
	void BindCallbacksToDependencies();

	UFUNCTION(BlueprintCallable)
	void BroadcastInitialValues();

public:
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
};
