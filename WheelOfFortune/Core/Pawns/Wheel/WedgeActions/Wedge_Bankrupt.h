#pragma once

#include "CoreMinimal.h"
#include "Wedge.h"
#include "Wedge_Bankrupt.generated.h"

UCLASS()
class WHEELOFFORTUNE_API UWedge_Bankrupt : public UWedge
{
	GENERATED_BODY()

public:
	UWedge_Bankrupt();
	
	virtual void Resolve(AStandardMode* Mode, int GuessedLetters) override;
};
