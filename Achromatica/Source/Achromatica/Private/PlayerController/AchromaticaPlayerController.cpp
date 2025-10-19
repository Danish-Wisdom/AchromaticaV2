// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/AchromaticaPlayerController.h"
#include "Character/AchromaticaCharacter.h"

#include  "EnhancedInputComponent.h"
#include  "EnhancedInputSubsystems.h"

AAchromaticaPlayerController::AAchromaticaPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAchromaticaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(TestMappingContext, 0);
		
	}
}

void AAchromaticaPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ControlledCharacter = Cast<AAchromaticaCharacter>(InPawn);
}

void AAchromaticaPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	ControlledCharacter = nullptr;
}

void AAchromaticaPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAchromaticaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAchromaticaPlayerController::HandleMoveAction);
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAchromaticaPlayerController::HandleLookAction);
			EnhancedInputComponent->BindAction(ControllerLookAction, ETriggerEvent::Triggered, this, &AAchromaticaPlayerController::HandleControllerLookAction);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AAchromaticaPlayerController::HandleJumpAction);
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AAchromaticaPlayerController::HandleAttackAction);
		}
	}
}



void AAchromaticaPlayerController::HandleMoveAction(const FInputActionValue& Value)
{
	FVector2D MoveAxis = Value.Get<FVector2D>();

	if (!ControlledCharacter) return;

	ControlledCharacter->Move(MoveAxis);
}

void AAchromaticaPlayerController::HandleLookAction(const FInputActionValue& Value)
{
	FVector2D LookAxis = Value.Get<FVector2D>();

	if (!ControlledCharacter) return;
	
	ControlledCharacter->Look(LookAxis);
}

void AAchromaticaPlayerController::HandleControllerLookAction(const FInputActionValue& Value)
{

	
}


void AAchromaticaPlayerController::HandleJumpAction(const FInputActionValue& Value) 
{
	if (!ControlledCharacter) return;

	ControlledCharacter->InstantJump(Value.Get<float>() * 20.f);
}

void AAchromaticaPlayerController::HandleAttackAction(const FInputActionValue& Value) 
{
	if (!ControlledCharacter) return;

	ControlledCharacter->Attack();
}
