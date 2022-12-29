#include "ControllerState_Mystery.h"

void UControllerState_Mystery::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("%s >> Input available: [???]"), ANSI_TO_TCHAR(__FUNCTION__));
}
