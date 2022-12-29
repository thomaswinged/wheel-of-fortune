#include "ControllerState_Wait.h"

void UControllerState_Wait::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("%s >> Input available: [NONE]"), ANSI_TO_TCHAR(__FUNCTION__));
}
