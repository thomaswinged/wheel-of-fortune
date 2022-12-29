#include "ControllerState_VowelGuess.h"

#include "ControllerState_StartTurn.h"
#include "ControllerState_SuccessfulAnswer.h"

void UControllerState_VowelGuess::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("%s >> Input available: [GUESS VOWEL]"), ANSI_TO_TCHAR(__FUNCTION__));
}

UControllerState* UControllerState_VowelGuess::GuessVowel(AMainPlayerController* Controller, const FString& Letter)
{
	if (IsValid(Controller))
	{
		const int LettersGuessed = Controller->WordPuzzle->GuessVowel(Letter);
		if (LettersGuessed == 0)
		{
			Controller->GameMode->HandleWrongAnswer();

			return NewObject<UControllerState_StartTurn>(Controller);
		}
		
		UE_LOG(LogTemp, Warning, TEXT("%s >> Contestant guessed %d vowels"), ANSI_TO_TCHAR(__FUNCTION__), LettersGuessed);
	
		Controller->GameMode->HandleCorrectAnswer();
		
		return NewObject<UControllerState_SuccessfulAnswer>(Controller);
	}

	return nullptr;
}
