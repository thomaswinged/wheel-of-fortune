#include "MainPlayerController.h"
#include "ControllerStates/ControllerState.h"
#include "ControllerStates/ControllerState_GuessConsonant.h"
#include "ControllerStates/ControllerState_StartTurn.h"
#include "Kismet/GameplayStatics.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ConnectToPawnsAndGameMode();
}

void AMainPlayerController::ConnectToPawnsAndGameMode()
{
	Wheel = Cast<AWheel>(UGameplayStatics::GetActorOfClass(GetWorld(), AWheel::StaticClass()));
	if (Wheel)
	{
		Wheel->WheelLanded.AddDynamic(this, &AMainPlayerController::OnWheelLanded);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> Wheel pawn is not on the map!"), ANSI_TO_TCHAR(__FUNCTION__));
	}
	
	WordPuzzle = Cast<AWordPuzzle>(UGameplayStatics::GetActorOfClass(GetWorld(), AWordPuzzle::StaticClass()));
	if (WordPuzzle)
	{
		WordPuzzle->PuzzleSolved.AddDynamic(this, &AMainPlayerController::OnPuzzleSolved);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> Word Puzzle pawn is not on the map!"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	GameMode = Cast<AStandardMode>(UGameplayStatics::GetActorOfClass(GetWorld(), AStandardMode::StaticClass()));
	if (GameMode)
	{
		GameMode->TurnChanged.AddDynamic(this, &AMainPlayerController::OnTurnChanged);
		GameMode->RoundChanged.AddDynamic(this, &AMainPlayerController::OnRoundChanged);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s >> Wrong game mode!"), ANSI_TO_TCHAR(__FUNCTION__));
	}
}

void AMainPlayerController::OnWheelLanded(TSubclassOf<UWedge> WheelLandedOn, FVector2D SectionRadialSpan)
{	
	CurrentWedge = NewObject<UWedge>(GetTransientPackage(), WheelLandedOn);
	
	if (CurrentWedge->bInstantResolve)
	{
		ResolveCurrentWedge(0);
	}
	else
	{
		State = NewObject<UControllerState_GuessConsonant>(this);
		State->Enter();
	}
}

void AMainPlayerController::ResolveCurrentWedge(int LettersGuessed)
{
	if (IsValid(CurrentWedge))
	{
		CurrentWedge->Resolve(GameMode, LettersGuessed);

		CurrentWedge = nullptr;
	}
}

void AMainPlayerController::OnPuzzleSolved()
{
	GameMode->HandleSolvedPuzzle();
}

void AMainPlayerController::OnTurnChanged(int EventIndex)
{
	State = NewObject<UControllerState_StartTurn>(this);
	State->Enter();
}

void AMainPlayerController::OnRoundChanged(FRoundInfo Info)
{
	WordPuzzle->SetPuzzle(Info.Phrase.Passphrase, Info.Phrase.Hint, true);
	Wheel->ChangeTopRoundValue(Info.TopValue);
}

void AMainPlayerController::BuyVowel()
{
	if (IsValid(State))
	{
		const auto NewState = State->BuyVowel(this);
		if (NewState)
		{
			State = NewState;
			State->Enter();
		}
	}
}

void AMainPlayerController::UseWildCard()
{
	if (IsValid(State))
	{
		const auto NewState = State->UseWildCard(this);
		if (NewState)
		{
			State = NewState;
			State->Enter();
		}
	}
}

void AMainPlayerController::GuessConsonant(const FString& Letter)
{
	if (IsValid(State))
	{
		const auto NewState = State->GuessConsonant(this, Letter);
		if (NewState)
		{
			State = NewState;
			State->Enter();
		}
	}
}

void AMainPlayerController::GuessVowel(const FString& Letter)
{
	if (IsValid(State))
	{
		const auto NewState = State->GuessVowel(this, Letter);
		if (NewState)
		{
			State = NewState;
			State->Enter();
		}
	}
}

void AMainPlayerController::SpinWheel()
{
	if (IsValid(State))
	{
		const auto NewState = State->SpinWheel(this);
		if (NewState)
		{
			State = NewState;
			State->Enter();
		}
	}
}

void AMainPlayerController::Pass()
{
	if (IsValid(State))
	{
		const auto NewState = State->Pass(this);
		if (NewState)
		{
			State = NewState;
			State->Enter();
		}
	}
}