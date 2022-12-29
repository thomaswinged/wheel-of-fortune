#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "WheelOfFortune/Core/CommonGameData.h"
#include "StandardMode.generated.h"

// TODO: Refactor this to state based solution - spin wheel state, guess letter state, and so on - get rid of bool checking
UCLASS()
class WHEELOFFORTUNE_API AStandardMode : public AGameModeBase
{
	GENERATED_BODY()

public:
#pragma region Functions
	AStandardMode();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	void NextRound();

	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	void HandleContestantPass();

	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	void HandleWrongAnswer();
	
	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	void HandleCorrectAnswer();

	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	void HandleSolvedPuzzle();

	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	bool HandleWildCardUseRequest();

	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	bool HandleVowelBuyRequest();

	void HandleCashWin(int Money);

	void HandleTokenWin(EGameToken Token);

	void HandleBankrupt();

	void HandleLoseATurn();

	void PrepareMysteryResolve(FScore BasicScore, FMysteryAlternative Alternative);
#pragma endregion

#pragma region Properties
	UPROPERTY(BlueprintAssignable, Category="Wheel Of Fortune")
	FRoundChanged RoundChanged;

	UPROPERTY(BlueprintAssignable, Category="Wheel Of Fortune")
	FIndexChanged TurnChanged;

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
#pragma endregion

#pragma region Properties
	UPROPERTY(EditAnywhere, Category="Wheel Of Fortune")
	int ContestantsCount = 3;

	UPROPERTY(EditAnywhere, Category="Wheel Of Fortune")
	TArray<FRoundPhrase> RoundPassphrases;

	UPROPERTY(EditAnywhere, Category="Wheel Of Fortune")
	int VowelPrice = 250;
#pragma endregion

private:
#pragma region Functions	
	void InitializeContestants();

	void NextContestant();

	FContestant* GetCurrentContestant();
#pragma endregion

#pragma region Properties
	TArray<FContestant> Contestants;

	int CurrentRoundID = -1;
	int CurrentContestantID = -1;

	FScore MysteryBasicScore;
	FMysteryAlternative MysteryAlternative;

	int TopDollarValue = -1;
#pragma endregion
};