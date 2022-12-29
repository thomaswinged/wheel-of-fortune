#include "Wedge_Cash.h"

void UWedge_Cash::Resolve(AStandardMode* Mode, int GuessedLetters)
{
	Super::Resolve(Mode, GuessedLetters);
	
	Mode->HandleCashWin(Money * GuessedLetters);
}
