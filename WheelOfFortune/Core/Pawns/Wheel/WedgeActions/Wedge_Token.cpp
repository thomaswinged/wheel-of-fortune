#include "Wedge_Token.h"

void UWedge_Token::Resolve(AStandardMode* Mode, int GuessedLetters)
{
	Super::Resolve(Mode, GuessedLetters);

	Mode->HandleTokenWin(Token);
}
