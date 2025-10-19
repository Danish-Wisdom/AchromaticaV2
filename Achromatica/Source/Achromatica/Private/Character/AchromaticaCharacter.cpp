// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AchromaticaCharacter.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


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

// Called when the game starts or when spawned
void AAchromaticaCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AAchromaticaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
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

