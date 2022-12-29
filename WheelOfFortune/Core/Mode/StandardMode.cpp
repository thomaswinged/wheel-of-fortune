#include "StandardMode.h"
#include "Kismet/GameplayStatics.h"


AStandardMode::AStandardMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

#if WITH_EDITOR
void AStandardMode::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	for (auto &Phrase : RoundPassphrases)
	{
		Phrase.Passphrase = Phrase.Passphrase.ToUpper();
		Phrase.Hint = Phrase.Hint.ToUpper();
	}
}
#endif

void AStandardMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeContestants();
}

void AStandardMode::InitializeContestants()
{
	for (int i = 0; i < ContestantsCount; i++)
	{
		Contestants.Add(FContestant(i));
	}

	UE_LOG(LogTemp, Warning, TEXT("%s >> Initialized %d contestants"), ANSI_TO_TCHAR(__FUNCTION__), ContestantsCount);
}

FContestant* AStandardMode::GetCurrentContestant()
{
	return &Contestants[CurrentContestantID];
}

void AStandardMode::NextRound()
{
	for (auto &Contestant : Contestants)
	{
		Contestant.RedeemRoundScore();
	}
	
	CurrentRoundID++;

	// Update round based top dollar value
	switch (CurrentRoundID)
	{
		case 0: // Round 1
			TopDollarValue = 2500;
			break;
		case 1: // Round 2
		case 2: // Round 3
			TopDollarValue = 3500;
			break;
		default: // Round 4, 5, 6, ...
			TopDollarValue = 5000;
	}

	// Set round passphrase
	FRoundPhrase RoundPassphrase;
	if (RoundPassphrases.IsValidIndex(CurrentRoundID))
	{
		RoundPassphrase = RoundPassphrases[CurrentRoundID];
	}
	else
	{
		RoundPassphrase = FRoundPhrase("A", "END OF PHRASES");
		UE_LOG(LogTemp, Warning, TEXT("%s >> There is not enough passphrases in game mode array!"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	const FRoundInfo Info = FRoundInfo(CurrentRoundID, TopDollarValue, RoundPassphrase);

	UE_LOG(LogTemp, Warning, TEXT("%s >> Round #%d started, round's top dollar value: %d"), ANSI_TO_TCHAR(__FUNCTION__), CurrentRoundID, TopDollarValue);

	RoundChanged.Broadcast(Info);

	NextContestant();
}

void AStandardMode::NextContestant()
{	
	CurrentContestantID = FMath::Fmod(CurrentContestantID + 1, ContestantsCount);
	
	UE_LOG(LogTemp, Warning, TEXT("%s >> Next contestant's turn, now playing: #%d"), ANSI_TO_TCHAR(__FUNCTION__), CurrentContestantID);
	
	TurnChanged.Broadcast(CurrentContestantID);
}

void AStandardMode::HandleContestantPass()
{
	UE_LOG(LogTemp, Warning, TEXT("%s >> Contestant #%d chickened out"), ANSI_TO_TCHAR(__FUNCTION__), CurrentContestantID);
	
	NextContestant();
}

void AStandardMode::HandleWrongAnswer()
{
	if (GetCurrentContestant()->HasToken(EGameToken::FreePlay))
	{
		GetCurrentContestant()->DiscardToken(EGameToken::FreePlay);
			
		UE_LOG(LogTemp, Warning, TEXT("%s >> Contestant had Free Play card, she/he can try again!"), ANSI_TO_TCHAR(__FUNCTION__));

		ActivatedToken.Broadcast(EGameToken::FreePlay);
		ContestantUpdate.Broadcast(*GetCurrentContestant());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> No letters guessed"), ANSI_TO_TCHAR(__FUNCTION__));
		
		ContestantFailed.Broadcast(CurrentContestantID);
		
		NextContestant();
	}
}

void AStandardMode::HandleCorrectAnswer()
{
	ContestantSucceeded.Broadcast(CurrentContestantID);
}

bool AStandardMode::HandleVowelBuyRequest()
{
	bool bResult = false;
	
	if (GetCurrentContestant()->SpendMoney(VowelPrice))
	{
		bResult = true;
		UE_LOG(LogTemp, Warning, TEXT("%s >> Contestant bought vowel guess"), ANSI_TO_TCHAR(__FUNCTION__));
	}
	else if (GetCurrentContestant()->HasToken(EGameToken::FreePlay))
	{
		bResult = true;
		GetCurrentContestant()->DiscardToken(EGameToken::FreePlay);
		UE_LOG(LogTemp, Warning, TEXT("%s >> Contestant used Free Play to buy vowel guess"), ANSI_TO_TCHAR(__FUNCTION__));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> Contestant don't have enough money"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	if (bResult)
	{
		BoughtVowel.Broadcast();
		ContestantUpdate.Broadcast(*GetCurrentContestant());
	}

	return bResult;
}

void AStandardMode::HandleSolvedPuzzle()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), ANSI_TO_TCHAR(__FUNCTION__));

	if (GetCurrentContestant()->RoundScore.Money < 1000)
	{
		GetCurrentContestant()->RoundScore.Money = 1000;
	}

	ContestantSucceeded.Broadcast(CurrentContestantID);
	SolvedPuzzle.Broadcast();
}

bool AStandardMode::HandleWildCardUseRequest()
{
	if (GetCurrentContestant()->HasToken(EGameToken::WildCard))
	{
		GetCurrentContestant()->DiscardToken(EGameToken::WildCard);

		ActivatedToken.Broadcast(EGameToken::WildCard);
		ContestantUpdate.Broadcast(*GetCurrentContestant());
	
		UE_LOG(LogTemp, Warning, TEXT("%s >> Contestant used Wild Card"), ANSI_TO_TCHAR(__FUNCTION__));

		return true;
	}

	return false;
}

void AStandardMode::HandleBankrupt()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), ANSI_TO_TCHAR(__FUNCTION__));

	if (GetCurrentContestant()->HasToken(EGameToken::WildCard))
	{
		GetCurrentContestant()->DiscardToken(EGameToken::WildCard);
				
		UE_LOG(LogTemp, Warning, TEXT("%s >> Contestant looses Wild Card due to Bankrupt"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	if (GetCurrentContestant()->HasToken(EGameToken::OneMillion))
	{
		GetCurrentContestant()->DiscardToken(EGameToken::OneMillion);
					
		UE_LOG(LogTemp, Warning, TEXT("%s >> Contestant looses One Million Oppurtunity due to Bankrupt"), ANSI_TO_TCHAR(__FUNCTION__));
	}
		
	GetCurrentContestant()->ClearRoundScore();

	ContestantFailed.Broadcast(CurrentContestantID);
	ContestantBankrupted.Broadcast();
	ContestantUpdate.Broadcast(*GetCurrentContestant());
		
	NextContestant();
}

void AStandardMode::HandleCashWin(int Money)
{
	GetCurrentContestant()->RoundScore.Money += Money;

	ContestantUpdate.Broadcast(*GetCurrentContestant());

	UE_LOG(LogTemp, Warning, TEXT("%s >> Adding $%d to contestant #%d round score"), ANSI_TO_TCHAR(__FUNCTION__), Money, CurrentContestantID);
}

void AStandardMode::HandleTokenWin(EGameToken Token)
{
	GetCurrentContestant()->RoundScore.Tokens.Add(Token);

	ContestantUpdate.Broadcast(*GetCurrentContestant());
	
	UE_LOG(LogTemp, Warning, TEXT("%s >> Contestant #%d received token: %s"), ANSI_TO_TCHAR(__FUNCTION__), CurrentContestantID, *WoF_EnumToString("EGameToken", Token));
}

void AStandardMode::HandleLoseATurn()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), ANSI_TO_TCHAR(__FUNCTION__));

	ContestantFailed.Broadcast(CurrentContestantID);
	ContestantLostATurn.Broadcast();
		
	NextContestant();
}

void AStandardMode::PrepareMysteryResolve(FScore BasicScore, FMysteryAlternative Alternative)
{
	MysteryAlternative = Alternative;
	MysteryBasicScore = BasicScore;
	
	UE_LOG(LogTemp, Warning, TEXT("%s >> Basic score: %d, alternatively bankrupt: %s"), ANSI_TO_TCHAR(__FUNCTION__), BasicScore.Money, Alternative.bBankrupt ? *FString("Yes") : *FString("No"));
}