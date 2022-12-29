#include "ControllerState_GuessConsonant.h"
#include "ControllerState_SuccessfulAnswer.h"
#include "ControllerState_StartTurn.h"

void UControllerState_GuessConsonant::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("%s >> Input available: [GUESS CONSONANT]"), ANSI_TO_TCHAR(__FUNCTION__));
}

UControllerState* UControllerState_GuessConsonant::GuessConsonant(AMainPlayerController* Controller,
                                                                  const FString& Letter)
{
	if (IsValid(Controller))
	{
		const int LettersGuessed = Controller->WordPuzzle->GuessConsonant(Letter);
		if (LettersGuessed == 0)
		{
			Controller->GameMode->HandleWrongAnswer();
			return NewObject<UControllerState_StartTurn>(Controller);
		}
		
		UE_LOG(LogTemp, Warning, TEXT("%s >> Contestant guessed %d consonants"), ANSI_TO_TCHAR(__FUNCTION__), LettersGuessed);

		Controller->ResolveCurrentWedge(LettersGuessed);
		Controller->GameMode->HandleCorrectAnswer();

		return NewObject<UControllerState_SuccessfulAnswer>(Controller);		
	}

	return nullptr;
}
