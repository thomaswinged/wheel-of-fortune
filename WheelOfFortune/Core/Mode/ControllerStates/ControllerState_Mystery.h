#pragma once

#include "CoreMinimal.h"
#include "ControllerState.h"
#include "ControllerState_Mystery.generated.h"

UCLASS()
class WHEELOFFORTUNE_API UControllerState_Mystery : public UControllerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
};
