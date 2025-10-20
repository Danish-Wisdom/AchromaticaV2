// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include  "AbilitySystemInterface.h"

#include "AchromaticaPlayerState.generated.h"

class UAchromaticaAbilitySystemComp;
class UAchromaticaAttributeSet;

/**
 * 
 */
UCLASS()
class ACHROMATICA_API AAchromaticaPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AAchromaticaPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure)
	UAchromaticaAbilitySystemComp* GetAchromaticaAbilitySystemComp() const;
	
	UFUNCTION(BlueprintPure)
	UAchromaticaAttributeSet* GetAchromaticaAttributeSet() const;
	
private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAchromaticaAbilitySystemComp> AchromaticaASC;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAchromaticaAttributeSet> AttributeSet;


	
};
