#pragma once

#include "CoreMinimal.h"
#include "ControllerState.h"
#include "ControllerState_StartTurn.generated.h"

UCLASS()
class WHEELOFFORTUNE_API UControllerState_StartTurn : public UControllerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
	
	virtual UControllerState* SpinWheel(AMainPlayerController* Controller) override;
};
