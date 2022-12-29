#include "Wedge_LoseATurn.h"

UWedge_LoseATurn::UWedge_LoseATurn()
{
	bInstantResolve = true;
}

void UWedge_LoseATurn::Resolve(AStandardMode* Mode, int GuessedLetters)
{
	Super::Resolve(Mode, GuessedLetters);

	Mode->HandleLoseATurn();
}
