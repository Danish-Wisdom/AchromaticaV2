// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AchromaticaGameMode.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class ACHROMATICA_API AAchromaticaGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AAchromaticaGameMode();

	UCharacterClassInfo* GetClassDefaults() const;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Custom Values|Class Defaults")
	TObjectPtr<UCharacterClassInfo> ClassDefaults;
};
