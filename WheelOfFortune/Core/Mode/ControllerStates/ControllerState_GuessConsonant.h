// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllerState.h"
#include "UObject/Object.h"
#include "ControllerState_GuessConsonant.generated.h"

/**
 * 
 */
UCLASS()
class WHEELOFFORTUNE_API UControllerState_GuessConsonant : public UControllerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
	
	virtual UControllerState* GuessConsonant(AMainPlayerController* Controller, const FString& Letter) override;
};
