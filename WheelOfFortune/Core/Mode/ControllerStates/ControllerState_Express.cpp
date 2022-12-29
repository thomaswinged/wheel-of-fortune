#include "ControllerState_Express.h"
#include "ControllerState_StartTurn.h"
#include "ControllerState_SuccessfulAnswer.h"

void UControllerState_Express::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("%s >> Input available: [GUESS CONSONANT] or [PASS]!"), ANSI_TO_TCHAR(__FUNCTION__));
}

UControllerState* UControllerState_Express::Pass(AMainPlayerController* Controller)
{
	if (IsValid(Controller))
	{
		Controller->GameMode->HandleContestantPass();

		return NewObject<UControllerState_StartTurn>(Controller);
	}
	return nullptr;
}

UControllerState* UControllerState_Express::GuessConsonant(AMainPlayerController* Controller, const FString& Letter)
{
	if (IsValid(Controller))
	{
		const int LettersGuessed = Controller->WordPuzzle->GuessConsonant(Letter);
		if (LettersGuessed == 0)
		{
			Controller->GameMode->HandleBankrupt();

			return NewObject<UControllerState_StartTurn>(Controller);
		}
		
		UE_LOG(LogTemp, Warning, TEXT("%s >> Contestant guessed %d consonants"), ANSI_TO_TCHAR(__FUNCTION__), LettersGuessed);

		Controller->ResolveCurrentWedge(LettersGuessed);
		Controller->GameMode->HandleCorrectAnswer();
		
		return NewObject<UControllerState_SuccessfulAnswer>(Controller);
	}
	
	return nullptr;
}