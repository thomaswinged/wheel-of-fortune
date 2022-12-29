#pragma once

#include "CoreMinimal.h"
#include "WheelOfFortune/Core/CommonGameData.h"
#include "GameModeListener.generated.h"

UCLASS(BlueprintType, Blueprintable)
class WHEELOFFORTUNE_API UGameModeListener : public UActorComponent
{
	GENERATED_BODY()

public:
#pragma region Properties
	UPROPERTY(BlueprintAssignable, Category="Wheel Of Fortune")
	FRoundChanged RoundChanged;

	UPROPERTY(BlueprintAssignable, Category="Wheel Of Fortune")
	FIndexChanged ContestantTurnChanged;

	UPROPERTY(BlueprintAssignable, Category="Wheel Of Fortune")
	FIndexChanged ContestantSucceeded;

	UPROPERTY(BlueprintAssignable, Category="Wheel Of Fortune")
	FIndexChanged ContestantFailed;

	UPROPERTY(BlueprintAssignable, Category="Wheel Of Fortune")
	FContestantUpdate ContestantUpdate;

	UPROPERTY(BlueprintAssignable, Category="Wheel Of Fortune")
	FTokenAction ActivatedToken;

	UPROPERTY(BlueprintAssignable, Category="Wheel Of Fortune")
	FContestantGenericAction ContestantBankrupted;

	UPROPERTY(BlueprintAssignable, Category="Wheel Of Fortune")
	FContestantGenericAction ContestantLostATurn;

	UPROPERTY(BlueprintAssignable, Category="Wheel Of Fortune")
	FContestantGenericAction BoughtVowel;

	UPROPERTY(BlueprintAssignable, Category="Wheel Of Fortune")
	FPuzzleSolved SolvedPuzzle;
#pragma endregion

protected:
#pragma region Functions
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRoundChanged(FRoundInfo Info);
	
	UFUNCTION()
	void OnContestantTurnChanged(int ContestantID);
	
	UFUNCTION()
	void OnContestantSucceeded(int ContestantID);
	
	UFUNCTION()
	void OnContestantFailed(int ContestantID);

	UFUNCTION()
	void OnContestantUpdate(const FContestant& Contestant);
	
	UFUNCTION()
	void OnActivatedToken(EGameToken Token);

	UFUNCTION()
	void OnContestantBankrupted();

	UFUNCTION()
	void OnContestantLostATurn();
	
	UFUNCTION()
	void OnBoughtVowel();

	UFUNCTION()
	void OnSolvedPuzzle();
#pragma endregion
};
