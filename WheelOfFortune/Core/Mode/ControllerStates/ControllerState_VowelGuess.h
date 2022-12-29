// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllerState.h"
#include "UObject/Object.h"
#include "ControllerState_VowelGuess.generated.h"

/**
 * 
 */
UCLASS()
class WHEELOFFORTUNE_API UControllerState_VowelGuess : public UControllerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
	
	virtual UControllerState* GuessVowel(AMainPlayerController* Controller, const FString& Letter) override;
};
