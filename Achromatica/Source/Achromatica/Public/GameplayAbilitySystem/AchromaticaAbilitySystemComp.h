// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AchromaticaAbilitySystemComp.generated.h"

/**
 * 
 */
UCLASS()
class ACHROMATICA_API UAchromaticaAbilitySystemComp : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:


	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToAdd);
	void AddCharacterPassives(const TArray<TSubclassOf<UGameplayAbility>>& PassivesToAdd);
	void InitializeDefaultAttributes(const TSubclassOf<UGameplayEffect>& DefaultAttributeEffect);
	
};
