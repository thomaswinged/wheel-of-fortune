#include "Wedge_Bankrupt.h"

UWedge_Bankrupt::UWedge_Bankrupt()
{
	bInstantResolve = true;
}

void UWedge_Bankrupt::Resolve(AStandardMode* Mode, int GuessedLetters)
{
	Super::Resolve(Mode, GuessedLetters);

	Mode->HandleBankrupt();
}
