#include "Wedge_Mystery.h"

void UWedge_Mystery::Resolve(AStandardMode* Mode, int GuessedLetters)
{
	Super::Resolve(Mode, GuessedLetters);
	
	Mode->PrepareMysteryResolve(FScore(BasicMoney), FMysteryAlternative(FScore(10000), FMath::RandBool()));

	Mode->HandleCorrectAnswer();
}
