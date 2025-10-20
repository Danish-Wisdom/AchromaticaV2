// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PlayerState/AchromaticaPlayerState.h"

#include "GameplayAbilitySystem/Attributes/AchromaticaAttributeSet.h"
#include "GameplayAbilitySystem/AchromaticaAbilitySystemComp.h"

AAchromaticaPlayerState::AAchromaticaPlayerState()
{
	SetNetUpdateFrequency(100.f);
	SetMinNetUpdateFrequency(66.f);

	AchromaticaASC = CreateDefaultSubobject<UAchromaticaAbilitySystemComp>(TEXT("AchromaticaAbilitySystemComp"));
	AchromaticaASC->SetIsReplicated(true);
	AchromaticaASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAchromaticaAttributeSet>(TEXT("AchromaticaAttributeSet"));
	
}

UAbilitySystemComponent* AAchromaticaPlayerState::GetAbilitySystemComponent() const
{
	return AchromaticaASC;
}

UAchromaticaAbilitySystemComp* AAchromaticaPlayerState::GetAchromaticaAbilitySystemComp() const
{
	return AchromaticaASC;
}

UAchromaticaAttributeSet* AAchromaticaPlayerState::GetAchromaticaAttributeSet() const
{
	return AttributeSet;
}
