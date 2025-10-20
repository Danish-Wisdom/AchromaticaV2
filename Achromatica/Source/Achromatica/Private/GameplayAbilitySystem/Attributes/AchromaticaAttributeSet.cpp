// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Attributes/AchromaticaAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UAchromaticaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAchromaticaAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAchromaticaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAchromaticaAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAchromaticaAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAchromaticaAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAchromaticaAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAchromaticaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Clamp Health to [0, MaxHealth]
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		// Clamp Stamina to [0, MaxStamina]
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}
	
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		// Clamp Mana to [0, MaxMana]
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	
	
}


void UAchromaticaAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAchromaticaAttributeSet, Health, OldHealth);
}

void UAchromaticaAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAchromaticaAttributeSet, MaxHealth, OldMaxHealth);
}

void UAchromaticaAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAchromaticaAttributeSet, Stamina, OldStamina);
}

void UAchromaticaAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAchromaticaAttributeSet, MaxStamina, OldMaxStamina);
}

void UAchromaticaAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAchromaticaAttributeSet, Mana, OldMana);
}

void UAchromaticaAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAchromaticaAttributeSet, MaxMana, OldMaxMana);
}
