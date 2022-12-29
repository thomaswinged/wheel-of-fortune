#pragma once

#include "CoreMinimal.h"
#include "ControllerState.h"
#include "ControllerState_SuccessfulAnswer.generated.h"

UCLASS()
class WHEELOFFORTUNE_API UControllerState_SuccessfulAnswer : public UControllerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
	
	virtual UControllerState* SpinWheel(AMainPlayerController* Controller) override;

	virtual UControllerState* BuyVowel(AMainPlayerController* Controller) override;

	virtual UControllerState* UseWildCard(AMainPlayerController* Controller) override;

	virtual UControllerState* Pass(AMainPlayerController* Controller) override;
};
