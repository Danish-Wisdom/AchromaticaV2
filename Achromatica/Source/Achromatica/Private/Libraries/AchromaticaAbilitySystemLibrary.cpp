// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/AchromaticaAbilitySystemLibrary.h"

#include "Game/GameMode/AchromaticaGameMode.h"
#include "Kismet/GameplayStatics.h"

UCharacterClassInfo* UAchromaticaAbilitySystemLibrary::GetClassDefaults(const UObject* WorldContextObject)
{
	if (const AAchromaticaGameMode* AchromaticaGameMode = Cast<AAchromaticaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return AchromaticaGameMode->GetClassDefaults();
	}
	
	return nullptr;
}
