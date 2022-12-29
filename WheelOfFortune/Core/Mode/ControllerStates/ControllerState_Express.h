#pragma once

#include "CoreMinimal.h"
#include "ControllerState.h"
#include "ControllerState_Express.generated.h"

UCLASS()
class WHEELOFFORTUNE_API UControllerState_Express : public UControllerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;

	virtual UControllerState* Pass(AMainPlayerController* Controller) override;

	virtual UControllerState* GuessConsonant(AMainPlayerController* Controller, const FString& Letter) override;
};
