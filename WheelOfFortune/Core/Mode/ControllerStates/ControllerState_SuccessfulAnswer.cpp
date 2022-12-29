#include "ControllerState_SuccessfulAnswer.h"

#include "ControllerState_GuessConsonant.h"
#include "ControllerState_StartTurn.h"
#include "ControllerState_VowelGuess.h"
#include "ControllerState_Wait.h"

void UControllerState_SuccessfulAnswer::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("%s >> Input available: [SPIN] or [BUY VOWEL] or [USE WILD CARD] or [PASS]"), ANSI_TO_TCHAR(__FUNCTION__));
}

UControllerState* UControllerState_SuccessfulAnswer::SpinWheel(AMainPlayerController* Controller)
{
	if (IsValid(Controller))
	{
		Controller->Wheel->Spin();
		
		return NewObject<UControllerState_Wait>(Controller);
	}

	return nullptr;
}

UControllerState* UControllerState_SuccessfulAnswer::BuyVowel(AMainPlayerController* Controller)
{
	if (IsValid(Controller))
	{
		if (Controller->GameMode->HandleVowelBuyRequest())
		{
			return NewObject<UControllerState_VowelGuess>(Controller);
		}
	}

	return nullptr;
}

UControllerState* UControllerState_SuccessfulAnswer::UseWildCard(AMainPlayerController* Controller)
{
	if (IsValid(Controller))
	{
		if (Controller->GameMode->HandleWildCardUseRequest())
		{
			return NewObject<UControllerState_GuessConsonant>(Controller);
		}
	}

	return nullptr;
}

UControllerState* UControllerState_SuccessfulAnswer::Pass(AMainPlayerController* Controller)
{
	if (IsValid(Controller))
	{
		Controller->GameMode->HandleContestantPass();

		return NewObject<UControllerState_StartTurn>(Controller);
	}

	return nullptr;
}
