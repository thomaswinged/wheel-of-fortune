#pragma once

#include "CoreMinimal.h"
#include "WheelOfFortune/Core/CommonGameData.h"
#include "PuzzleBlock.h"
#include "GameFramework/Actor.h"
#include "WheelOfFortune/Core/ObjectPooling/ActorsPool.h"
#include "WordPuzzle.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, HideCategories=(Input, Actor, LOD, Cooking, Collision, Replication, Rendering))
class WHEELOFFORTUNE_API AWordPuzzle : public AActor
{
	GENERATED_BODY()

public:
#pragma region Functions
	AWordPuzzle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Word Puzzle")
	void SetPuzzle(const FString& NewSentence, const FString& NewHint, bool bUseTransition = true);

	UFUNCTION(BlueprintCallable, Category="Word Puzzle")
	int GuessConsonant(const FString& Consonant);

	UFUNCTION(BlueprintCallable, Category="Word Puzzle")
	int GuessVowel(const FString& Vowel);

	UFUNCTION(BlueprintCallable, Category="Word Puzzle")
	void SolvePuzzle(bool bUseTransition = true);
#pragma endregion

#pragma region Properties
	UPROPERTY(BlueprintAssignable)
	FLetterGuessed ConsonantGuessed;

	UPROPERTY(BlueprintAssignable)
	FLetterGuessed VowelGuessed;
	
	UPROPERTY(BlueprintAssignable)
	FPuzzleSolved PuzzleSolved;
#pragma endregion

protected:
#pragma region Functions
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Word Puzzle")
	TArray<FSentenceLine> GetSentenceLines() const { return SentenceLines; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Word Puzzle")
	int GetLongestLineLength();

	UFUNCTION(BlueprintCallable, Category="Word Puzzle")
	bool FetchBlockFromPool(APuzzleBlock*& Block);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Word Puzzle")
	TArray<APuzzleBlock*> GetBlocks() const { return BlockEntries; }
#pragma endregion
	
#pragma region Properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine="true"), Category="Word Puzzle")
	FString Sentence = "HELLO WORLD";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Word Puzzle")
	FString Hint = "FIRST PROGRAM";
	
	UPROPERTY(EditAnywhere, Category="Word Puzzle")
	AActorsPool* PuzzleBlocksPool;
#pragma endregion
	
private:
#pragma region Functions
	TArray<FSentenceLine> SplitSentenceIntoLines(const FString& InSentence);

	int GuessLetter(const FString& Letter);

	void ClearBlocks();
#pragma endregion

#pragma region Properties	
	TArray<FSentenceLine> SentenceLines;

	UPROPERTY()
	TArray<APuzzleBlock*> BlockEntries;

	int CharactersLeftCount = 0;
#pragma endregion
};
