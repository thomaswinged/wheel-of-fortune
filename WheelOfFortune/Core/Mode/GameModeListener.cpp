#include "GameModeListener.h"
#include "Kismet/GameplayStatics.h"
#include "WheelOfFortune/Core/Mode/StandardMode.h"

void UGameModeListener::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		AStandardMode* GameMode = Cast<AStandardMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (IsValid(GameMode))
		{
			GameMode->RoundChanged.AddDynamic(this, &UGameModeListener::OnRoundChanged);
			GameMode->TurnChanged.AddDynamic(this, &UGameModeListener::OnContestantTurnChanged);
			GameMode->ContestantSucceeded.AddDynamic(this, &UGameModeListener::OnContestantSucceeded);
			GameMode->ContestantFailed.AddDynamic(this, &UGameModeListener::OnContestantFailed);
			GameMode->ContestantUpdate.AddDynamic(this, &UGameModeListener::OnContestantUpdate);
			GameMode->ActivatedToken.AddDynamic(this, &UGameModeListener::OnActivatedToken);
			GameMode->ContestantBankrupted.AddDynamic(this, &UGameModeListener::OnContestantBankrupted);
			GameMode->ContestantLostATurn.AddDynamic(this, &UGameModeListener::OnContestantLostATurn);
			GameMode->BoughtVowel.AddDynamic(this, &UGameModeListener::OnBoughtVowel);
			GameMode->SolvedPuzzle.AddDynamic(this, &UGameModeListener::OnSolvedPuzzle);
		}
	}
}

void UGameModeListener::OnRoundChanged(FRoundInfo Info)
{
	RoundChanged.Broadcast(Info);
}

void UGameModeListener::OnContestantTurnChanged(int ContestantID)
{
	ContestantTurnChanged.Broadcast(ContestantID);
}

void UGameModeListener::OnContestantSucceeded(int ContestantID)
{
	ContestantSucceeded.Broadcast(ContestantID);
}

void UGameModeListener::OnContestantFailed(int ContestantID)
{
	ContestantFailed.Broadcast(ContestantID);
}

void UGameModeListener::OnContestantUpdate(const FContestant& Contestant)
{
	ContestantUpdate.Broadcast(Contestant);
}

void UGameModeListener::OnActivatedToken(EGameToken Token)
{
	ActivatedToken.Broadcast(Token);
}

void UGameModeListener::OnContestantBankrupted()
{
	ContestantBankrupted.Broadcast();
}

void UGameModeListener::OnContestantLostATurn()
{
	ContestantLostATurn.Broadcast();
}

void UGameModeListener::OnBoughtVowel()
{
	BoughtVowel.Broadcast();
}

void UGameModeListener::OnSolvedPuzzle()
{
	SolvedPuzzle.Broadcast();
}

