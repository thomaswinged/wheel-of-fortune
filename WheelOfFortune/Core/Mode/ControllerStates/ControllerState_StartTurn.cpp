#include "ControllerState_StartTurn.h"
#include "ControllerState_Wait.h"

void UControllerState_StartTurn::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("%s >> Input available: [SPIN]"), ANSI_TO_TCHAR(__FUNCTION__));
}

UControllerState* UControllerState_StartTurn::SpinWheel(AMainPlayerController* Controller)
{
	if (IsValid(Controller))
	{
		Controller->Wheel->Spin();
		
		return NewObject<UControllerState_Wait>(Controller);
	}

	return nullptr;
}
