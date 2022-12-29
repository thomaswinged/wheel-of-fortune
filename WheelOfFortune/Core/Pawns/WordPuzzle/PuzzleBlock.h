// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheelOfFortune/Core/ObjectPooling/PooledActor.h"
#include "PuzzleBlock.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class WHEELOFFORTUNE_API APuzzleBlock : public APooledActor
{
	GENERATED_BODY()
	
public:
#pragma region Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;
#pragma endregion
	
#pragma region Functions
	APuzzleBlock();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Puzzle Block")
	void InitializeBlock(bool bIsBlockEmpty, const FString& BlockLetter);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Puzzle Block")
	bool IsBlockEmpty();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Puzzle Block")
	bool IsBlockShown();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Puzzle Block")
	FString GetLetter();

	// Implementation dependant - if is not empty, animate in somehow the block to show the hidden letter
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Puzzle Block")
	void ShowLetter(bool bUseTransition = true);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Puzzle Block")
	void ResetBlock();
#pragma endregion
	
protected:
#pragma region Functions
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Puzzle Block")
	int GetLetterAsciiCode();
#pragma endregion

private:
#pragma region Properties
	UPROPERTY()
	bool bIsEmpty = true;

	UPROPERTY()
	bool bIsShown = false;

	UPROPERTY()
	FString Letter = " ";
#pragma endregion
};
