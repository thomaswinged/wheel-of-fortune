#pragma once

#include "CoreMinimal.h"
#include "ControllerState.h"
#include "ControllerState_Wait.generated.h"

UCLASS()
class WHEELOFFORTUNE_API UControllerState_Wait : public UControllerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
};
