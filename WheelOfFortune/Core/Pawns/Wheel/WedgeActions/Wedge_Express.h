#pragma once

#include "CoreMinimal.h"
#include "Wedge_Cash.h"
#include "Wedge_Express.generated.h"

UCLASS(Abstract)
class WHEELOFFORTUNE_API UWedge_Express : public UWedge_Cash
{
	GENERATED_BODY()
	
public:
	virtual void Resolve(AStandardMode* Mode, int GuessedLetters) override;
};
