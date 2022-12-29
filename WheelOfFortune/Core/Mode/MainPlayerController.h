#pragma once

#include "CoreMinimal.h"
#include "StandardMode.h"
#include "GameFramework/PlayerController.h"
#include "WheelOfFortune/Core/Pawns/Wheel/Wheel.h"
#include "WheelOfFortune/Core/Pawns/Wheel/WedgeActions/Wedge.h"
#include "WheelOfFortune/Core/Pawns/WordPuzzle/WordPuzzle.h"
#include "MainPlayerController.generated.h"

class UControllerState;

UCLASS()
class WHEELOFFORTUNE_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	friend class UControllerState_GuessConsonant;
	friend class UControllerState_Express;
	
#pragma region Properties
	UPROPERTY(BlueprintReadOnly, Category="Wheel Of Fortune")
	AWheel* Wheel;

	UPROPERTY(BlueprintReadOnly, Category="Wheel Of Fortune")
	AWordPuzzle* WordPuzzle;

	UPROPERTY(BlueprintReadOnly, Category="Wheel Of Fortune")
	AStandardMode* GameMode;
#pragma endregion

protected:
#pragma region Functions
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	void BuyVowel();

	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	void UseWildCard();

	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	void GuessConsonant(const FString& Letter);

	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	void GuessVowel(const FString& Letter);

	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	void SpinWheel();
	
	UFUNCTION(BlueprintCallable, Category="Wheel Of Fortune")
	void Pass();
#pragma endregion

private:
	UPROPERTY()
	UControllerState* State;

	UPROPERTY()
	UWedge* CurrentWedge;
	
	void ConnectToPawnsAndGameMode();

	UFUNCTION()
	void OnWheelLanded(TSubclassOf<UWedge> WheelLandedOn, FVector2D SectionRadialSpan);

	void ResolveCurrentWedge(int LettersGuessed);

	UFUNCTION()
	void OnPuzzleSolved();

	UFUNCTION()
	void OnTurnChanged(int EventIndex);

	UFUNCTION()
	void OnRoundChanged(FRoundInfo Info);
};
