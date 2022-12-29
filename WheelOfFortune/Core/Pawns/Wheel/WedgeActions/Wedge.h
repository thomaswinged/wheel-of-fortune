
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WheelOfFortune/Core/Mode/StandardMode.h"
#include "Wedge.generated.h"

// Each wedge on the wheel of fortune can be resolved as a command pattern
UCLASS(Abstract, Blueprintable, BlueprintType)
class WHEELOFFORTUNE_API UWedge : public UObject
{
	GENERATED_BODY()

public:
	virtual void Resolve(AStandardMode* Mode, int GuessedLetters);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wheel Of Fortune|Wedge")
	bool bInstantResolve = false;
};
