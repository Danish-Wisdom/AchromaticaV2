// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AchromaticaCharacter.h"


#include "Camera/CameraComponent.h"
#include "Data/CharacterClassInfo.h"
#include "Game/PlayerState/AchromaticaPlayerState.h"
#include "GameFramework/SpringArmComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayAbilitySystem/AchromaticaAbilitySystemComp.h"
#include "GameplayAbilitySystem/Attributes/AchromaticaAttributeSet.h"
#include "Libraries/AchromaticaAbilitySystemLibrary.h"


// Sets default values
AAchromaticaCharacter::AAchromaticaCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 450.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch	= true;
	bUseControllerRotationRoll	= false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

void AAchromaticaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (HasAuthority())
	{
		InitAbilityActorInfo();
	}
}

void AAchromaticaCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

void AAchromaticaCharacter::InitAbilityActorInfo()
{
	if (AAchromaticaPlayerState* AchromaticaPlayerState = GetPlayerState<AAchromaticaPlayerState>())
	{
		AbilitySystemComp = AchromaticaPlayerState->GetAchromaticaAbilitySystemComp();
		AttributeSet = AchromaticaPlayerState->GetAchromaticaAttributeSet();

		if (IsValid(AbilitySystemComp))
		{
			AbilitySystemComp->InitAbilityActorInfo(AchromaticaPlayerState, this);
			BindCallbacksToDependencies();

			if (HasAuthority())
			{
				InitClassDefaults();
			}
		}
		
	}
}

void AAchromaticaCharacter::InitClassDefaults()
{
	if (!CharacterTag.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("No Character Tag on this character: %s"), *GetNameSafe(this));
	}
	else if (UCharacterClassInfo* ClassInfo = UAchromaticaAbilitySystemLibrary::GetClassDefaults(this))
	{
		if (const FCharacterClassDefaultInfo* SelectedClassInfo = ClassInfo->ClassDefaultInfoMap.Find(CharacterTag))
		{
			if (IsValid(AbilitySystemComp))
			{
				AbilitySystemComp->AddCharacterAbilities(SelectedClassInfo->StartingAbilities);
				AbilitySystemComp->AddCharacterPassives(SelectedClassInfo->StartingPassives);
				AbilitySystemComp->InitializeDefaultAttributes(SelectedClassInfo->DefaultAttributes);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Class Info found for Tag: %s"), *CharacterTag.ToString());
		}
	}
	
}

void AAchromaticaCharacter::BindCallbacksToDependencies()
{
	if (IsValid(AbilitySystemComp) && IsValid(AttributeSet))
	{
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged(Data.NewValue, AttributeSet->GetMaxHealth());
			});

		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnStaminaChanged(Data.NewValue, AttributeSet->GetMaxStamina());
			});

		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged(Data.NewValue, AttributeSet->GetMaxMana());
			});
	}
}

void AAchromaticaCharacter::BroadcastInitialValues()
{
	if (IsValid(AttributeSet))
	{
		OnHealthChanged(AttributeSet->GetHealth(), AttributeSet->GetMaxHealth());
		OnStaminaChanged(AttributeSet->GetStamina(), AttributeSet->GetMaxStamina());
		OnManaChanged(AttributeSet->GetMana(), AttributeSet->GetMaxMana());
	}
}


void AAchromaticaCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	
}


void AAchromaticaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AAchromaticaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/*void AAchromaticaCharacter::MoveForward(const float& MoveAxis)
{
	FRotator ControlRot = Controller->GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	const FVector ForwardDir = FRotationMatrix(ControlRot).GetUnitAxis(EAxis::X);
	
	
	AddMovementInput(ForwardDir, MoveAxis);

	// Rotate Character to Camera Direction
	FRotator TargetRot = ControlRot;
	FRotator NewRot = FMath::RInterpTo(GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.f);
	SetActorRotation(NewRot);
}*/



void AAchromaticaCharacter::Move(const FVector2D& MoveAxis)
{
	if (IsValid(Controller))
	{
		// Get forward and right direction
		const FRotator ControlRot = Controller->GetControlRotation();
		const FRotator YawRotation(0, ControlRot.Yaw, 0);

		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement input
		AddMovementInput(ForwardDir, MoveAxis.Y * WalkSpeed * GetWorld()->GetDeltaSeconds());
		AddMovementInput(RightDir, MoveAxis.X * StrafeSpeed * GetWorld()->GetDeltaSeconds());

	}
}

void AAchromaticaCharacter::Look(const FVector2D& LookAxis)
{
	if (IsValid(Controller) && !bLockControllerRotation)
	{
		AddControllerYawInput(LookAxis.X * HorizontalRotationSpeed * GetWorld()->GetDeltaSeconds());
		AddControllerPitchInput(LookAxis.Y * VerticalRotationSpeed * GetWorld()->GetDeltaSeconds());
	}
}

void AAchromaticaCharacter::InstantJump(const float& JumpHeight)
{
	ACharacter::Jump();
}

void AAchromaticaCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack") );
	bLockControllerRotation = !bLockControllerRotation;
}



