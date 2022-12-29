#pragma once

#include "CoreMinimal.h"
#include "Wedge.h"
#include "Wedge_LoseATurn.generated.h"

UCLASS()
class WHEELOFFORTUNE_API UWedge_LoseATurn : public UWedge
{
	GENERATED_BODY()

public:
	UWedge_LoseATurn();
	
	virtual void Resolve(AStandardMode* Mode, int GuessedLetters) override;
};
