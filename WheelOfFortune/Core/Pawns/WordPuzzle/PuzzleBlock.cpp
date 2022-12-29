#include "PuzzleBlock.h"


void APuzzleBlock::InitializeBlock_Implementation(bool bIsBlockEmpty, const FString& BlockLetter)
{
	if (BlockLetter != " " && !bIsBlockEmpty)
	{
		bIsEmpty = false;
		Letter = BlockLetter;
	}
}

APuzzleBlock::APuzzleBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(Root);
	Mesh->SetupAttachment(Root);
}

bool APuzzleBlock::IsBlockEmpty()
{
	return bIsEmpty;
}

bool APuzzleBlock::IsBlockShown()
{
	return bIsShown;
}

FString APuzzleBlock::GetLetter()
{
	return Letter;
}

void APuzzleBlock::ShowLetter_Implementation(bool bUseTransition)
{
	bIsShown = true;
}

void APuzzleBlock::ResetBlock_Implementation()
{
	bIsEmpty = true;
	Letter = " ";
	bIsShown = false;
}

void APuzzleBlock::BeginPlay()
{
	Super::BeginPlay();
}

int APuzzleBlock::GetLetterAsciiCode()
{
	char Char = *TCHAR_TO_ANSI(*Letter);
	const int Result = int(Char);
	
	return Result;
}

