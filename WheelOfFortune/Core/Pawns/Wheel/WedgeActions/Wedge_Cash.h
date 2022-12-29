#pragma once

#include "CoreMinimal.h"
#include "Wedge.h"
#include "Wedge_Cash.generated.h"

UCLASS(Abstract)
class WHEELOFFORTUNE_API UWedge_Cash : public UWedge
{
	GENERATED_BODY()
	
public:
	virtual void Resolve(AStandardMode* Mode, int GuessedLetters) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wheel Of Fortune|Wedge")
	int Money = 0;
};
