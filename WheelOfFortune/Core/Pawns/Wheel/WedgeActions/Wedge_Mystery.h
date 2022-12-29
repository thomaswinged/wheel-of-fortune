#pragma once

#include "CoreMinimal.h"
#include "Wedge.h"
#include "Wedge_Mystery.generated.h"

UCLASS(Abstract)
class WHEELOFFORTUNE_API UWedge_Mystery : public UWedge
{
	GENERATED_BODY()
	
public:
	virtual void Resolve(AStandardMode* Mode, int GuessedLetters) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wheel Of Fortune|Wedge")
	int BasicMoney = 0;
};
