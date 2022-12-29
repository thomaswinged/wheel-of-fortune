#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WheelOfFortune/Core/Mode/MainPlayerController.h"
#include "ControllerState.generated.h"

UCLASS(Abstract)
class WHEELOFFORTUNE_API UControllerState : public UObject
{
	GENERATED_BODY()

public:
	virtual void Enter() {}
	
	virtual UControllerState* BuyVowel(AMainPlayerController* Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> Not available in current state!"), ANSI_TO_TCHAR(__FUNCTION__));
		return nullptr;
	}

	virtual UControllerState* UseWildCard(AMainPlayerController* Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> Not available in current state!"), ANSI_TO_TCHAR(__FUNCTION__));
		return nullptr;
	}

	virtual UControllerState* GuessConsonant(AMainPlayerController* Controller, const FString& Letter)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> Not available in current state!"), ANSI_TO_TCHAR(__FUNCTION__));
		return nullptr;
	}

	virtual UControllerState* GuessVowel(AMainPlayerController* Controller, const FString& Letter)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> Not available in current state!"), ANSI_TO_TCHAR(__FUNCTION__));
		return nullptr;
	}

	virtual UControllerState* SpinWheel(AMainPlayerController* Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> Not available in current state!"), ANSI_TO_TCHAR(__FUNCTION__));
		return nullptr;
	}
	
	virtual UControllerState* Pass(AMainPlayerController* Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> Not available in current state!"), ANSI_TO_TCHAR(__FUNCTION__));
		return nullptr;
	}
};
