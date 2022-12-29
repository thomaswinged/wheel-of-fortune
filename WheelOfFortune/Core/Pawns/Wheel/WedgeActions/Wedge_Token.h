#pragma once

#include "CoreMinimal.h"
#include "Wedge_Cash.h"
#include "Wedge_Token.generated.h"

UCLASS(Abstract)
class WHEELOFFORTUNE_API UWedge_Token : public UWedge_Cash
{
	GENERATED_BODY()

public:
	virtual void Resolve(AStandardMode* Mode, int GuessedLetters) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wheel Of Fortune|Wedge")
	EGameToken Token;
};
