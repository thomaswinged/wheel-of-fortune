#include "WordPuzzle.h"

#include "Kismet/KismetStringLibrary.h"


AWordPuzzle::AWordPuzzle()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWordPuzzle::BeginPlay()
{
	Super::BeginPlay();
}

#if WITH_EDITOR
void AWordPuzzle::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	SetPuzzle(Sentence, Hint, false);
}
#endif

void AWordPuzzle::SetPuzzle_Implementation(const FString& NewSentence, const FString& NewHint, bool bUseTransition)
{
	Sentence = NewSentence.ToUpper();
	Hint = NewHint.ToUpper();

	SentenceLines = SplitSentenceIntoLines(Sentence);
	
	ClearBlocks();
}

void AWordPuzzle::ClearBlocks()
{
	if (PuzzleBlocksPool != nullptr)
	{
		for (const auto Block : BlockEntries)
		{
			Block->Mesh->SetRelativeTransform(FTransform());
		}
		
		PuzzleBlocksPool->ReturnAllActorsToPool();
		BlockEntries.Empty();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No PuzzleBlocksPool selected!"))
	}
}

bool AWordPuzzle::FetchBlockFromPool(APuzzleBlock*& Block)
{
	if (PuzzleBlocksPool)
	{
		APooledActor* PooledActor;
		if (PuzzleBlocksPool->GetActorFromPool(PooledActor))
		{
			PooledActor->SetActive(true);
			APuzzleBlock* PooledBlock = CastChecked<APuzzleBlock>(PooledActor);
			PooledBlock->ResetBlock();

			Block = PooledBlock;
			
			BlockEntries.Add(PooledBlock);

			return true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No PuzzleBlocksPool selected!"))
	}
	
	return false;
}

int AWordPuzzle::GetLongestLineLength()
{
	int Result = 0;
	
	for (auto LineEntry : SentenceLines)
	{
		Result = FMath::Max(Result, LineEntry.Line.Num());
	}

	return Result;
}

TArray<FSentenceLine> AWordPuzzle::SplitSentenceIntoLines(const FString& InSentence)
{
	TArray<FSentenceLine> Result;
	FString ToTrim = InSentence;
	FString Left, Right;
	FSentenceLine Line = FSentenceLine();

	CharactersLeftCount = 0;

	while(true)
	{
		if (ToTrim.Split(LINE_TERMINATOR, &Left, &Right))
		{
			ToTrim = Right;
			Line.Line = UKismetStringLibrary::GetCharacterArrayFromString(Left);
			Result.Add(Line);
		}
		else
		{
			Line.Line = UKismetStringLibrary::GetCharacterArrayFromString(ToTrim);
			Result.Add(Line);
			break;
		}
	}

	// Count guessable characters
	for (auto ResultLine : Result)
	{
		for (auto Character : ResultLine.Line)
		{
			if (Character != " ")
			{
				CharactersLeftCount++;
			}
		}
	}

	return Result;
}

int AWordPuzzle::GuessConsonant(const FString& Consonant)
{
	if (Consonant.Equals("A") || Consonant.Equals("E") || Consonant.Equals("I") || Consonant.Equals("O") || Consonant.Equals("U") || Consonant.Equals("Y"))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> Letter is not consonant!"), ANSI_TO_TCHAR(__FUNCTION__));
		return 0;
	}
	
	const int ConsonantsGuessed = GuessLetter(Consonant);

	ConsonantGuessed.Broadcast(ConsonantsGuessed);

	CharactersLeftCount -= ConsonantsGuessed;
	if (CharactersLeftCount <= 0)
	{
		PuzzleSolved.Broadcast();
	}

	return ConsonantsGuessed;
}

int AWordPuzzle::GuessVowel(const FString& Vowel)
{
	if (!(Vowel.Equals("A") && Vowel.Equals("E") && Vowel.Equals("I") && Vowel.Equals("O") && Vowel.Equals("U") && Vowel.Equals("Y")))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> Letter is not vowel!"), ANSI_TO_TCHAR(__FUNCTION__));
		return 0;
	}
	
	const int VowelsGuessed = GuessLetter(Vowel);

	VowelGuessed.Broadcast(VowelsGuessed);

	CharactersLeftCount -= VowelsGuessed;
	if (CharactersLeftCount <= 0)
	{
		PuzzleSolved.Broadcast();
	}

	return VowelsGuessed;
}

int AWordPuzzle::GuessLetter(const FString& Letter)
{
	int LettersGuessed = 0;
	
	for (const auto Block : BlockEntries)
	{
		if (IsValid(Block))
		{
			if (!Block->IsBlockEmpty() && !Block->IsBlockShown())
			{
				if (Block->GetLetter().Equals(Letter))
				{
					Block->ShowLetter(true);
					LettersGuessed++;
				}
			}
		}
	}

	return LettersGuessed;
}

void AWordPuzzle::SolvePuzzle(bool bUseTransition)
{
	for (const auto Block : BlockEntries)
	{
		if (IsValid(Block))
		{
			if (!Block->IsBlockEmpty() && !Block->IsBlockShown())
			{
				Block->ShowLetter(bUseTransition);
			}
		}
	}

	CharactersLeftCount = 0;
	
	PuzzleSolved.Broadcast();
}