// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/AchromaticaAbilitySystemComp.h"

void UAchromaticaAbilitySystemComp::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToAdd)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : AbilitiesToAdd)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		GiveAbility(AbilitySpec);
	}
}

void UAchromaticaAbilitySystemComp::AddCharacterPassives(const TArray<TSubclassOf<UGameplayAbility>>& PassivesToAdd)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : PassivesToAdd)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UAchromaticaAbilitySystemComp::InitializeDefaultAttributes(const TSubclassOf<UGameplayEffect>& DefaultAttributeEffect)
{
	//check(DefaultAttributeEffect, TEXT("No Default Attribute Effect specified for %s", *GetAvatarActor()->GetName()));

	
	const FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(DefaultAttributeEffect, 1, ContextHandle);
	ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
