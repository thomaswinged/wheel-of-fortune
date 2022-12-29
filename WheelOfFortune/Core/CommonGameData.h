#pragma once

#include "CoreMinimal.h"
#include "CommonGameData.generated.h"

class UWedge;

UENUM(BlueprintType)
enum class EGameToken : uint8
{
	OneMillion,
	WildCard,
	Trip,
	Car,
	FreePlay
};

USTRUCT(BlueprintType)
struct FSentenceLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Word Puzzle")
	TArray<FString> Line;
};

USTRUCT(BlueprintType)
struct FWheelSection
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wheel")
	int ZonesCount = 3;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wheel")
	FVector2D RadialSpan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wheel")
	TSubclassOf<UWedge> WedgeType;
};

USTRUCT(BlueprintType)
struct FScore
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wheel of Fortune")
	int Money = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wheel of Fortune")
	TArray<EGameToken> Tokens;

	FScore() = default;

	explicit FScore(const int WinMoney, const TArray<EGameToken> InTokens = TArray<EGameToken>())
	: Money(WinMoney)
	, Tokens(InTokens)
	{}

	void ApplyGuessMultiplier(const int LettersGuessed)
	{
		Money *= LettersGuessed;
	}

	void Clear()
	{
		Money = 0;
		Tokens.Empty();
	}

	FScore operator+(const FScore& Other) const
	{
		FScore Result;
		
		Result.Money = Money + Other.Money;
		
		for (auto Token : Tokens)
		{
			Result.Tokens.AddUnique(Token);
		}

		for (auto Token : Other.Tokens)
		{
			Result.Tokens.AddUnique(Token);
		}
		
		return Result;
	}

	FScore operator+=(const FScore& Other)
	{
		Money += Other.Money;
		
		for (auto Token : Other.Tokens)
		{
			Tokens.AddUnique(Token);
		}

		
		return *this;
	}
};

USTRUCT()
struct FMysteryAlternative
{
	GENERATED_BODY()

	FScore Score;
	bool bBankrupt = false;

	FMysteryAlternative() = default;

	explicit FMysteryAlternative(FScore InScore, bool bInBankrupt)
	: Score(InScore)
	, bBankrupt(bInBankrupt)
	{}
};

USTRUCT(BlueprintType)
struct FRoundPhrase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine="true"), Category="Wheel of Fortune")
	FString Passphrase = "PASSPHRASE";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wheel of Fortune")
	FString Hint = "Hint";
	
	FRoundPhrase() = default;

	explicit FRoundPhrase(const FString& InPassphrase, const FString& InHint)
	{
		Passphrase = InPassphrase.ToUpper();
		Hint = InHint.ToUpper();
	}
};

USTRUCT(BlueprintType)
struct FRoundInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wheel of Fortune")
	int RoundID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wheel of Fortune")
	int TopValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wheel of Fortune")
	FRoundPhrase Phrase;

	FRoundInfo() = default;

	explicit FRoundInfo(int InRoundID, int InTopValue, FRoundPhrase InPhrase)
	: RoundID(InRoundID)
	, TopValue(InTopValue)
	, Phrase(InPhrase)
	{}
};

USTRUCT(BlueprintType)
struct FContestant
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Contestant")
	int ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Contestant")
	FScore RoundScore;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Contestant")
	FScore RedeemedScore;

	FContestant() = default;

	explicit FContestant(const int InID)
	: ID(InID)
	{}

	bool SpendMoney(const int Money)
	{
		if (RoundScore.Money > Money)
		{
			RoundScore.Money -= Money;
			return true;
		}
		
		if (GetTotalMoney() > Money)
		{
			const int LeftToPay = Money - RoundScore.Money;
			RoundScore.Money = 0;
			RedeemedScore.Money -= LeftToPay;
			return true;
		}

		return false;
	}

	int GetTotalMoney() const
	{
		return RoundScore.Money + RedeemedScore.Money;
	}
	
	FScore GetTotalScore() const
	{
		return RedeemedScore + RoundScore;
	}

	void RedeemRoundScore()
	{
		RedeemedScore += RoundScore;
		ClearRoundScore();
	}

	void ClearRoundScore()
	{
		RoundScore.Clear();
	}

	bool HasToken(EGameToken Token) const
	{
		return RoundScore.Tokens.Contains(Token) || RedeemedScore.Tokens.Contains(Token);
	}

	void DiscardToken(EGameToken Token)
	{
		RoundScore.Tokens.Remove(Token);
		RedeemedScore.Tokens.Remove(Token);
	}
};

// Event triggered when wheel ticks rotation
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWheelRotated, float, CurrentAngle);

// Informs about at which section the wheel stopped and about radial coordinates of section start and end for visual purposes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWheelLanded, TSubclassOf<UWedge>, WheelLandedOn, FVector2D, SectionRadialSpan);

// Event that is being triggered when all letters are guessed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLetterGuessed, int, LettersGuessed);

// For broadcasting things like round change or contestant change
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRoundChanged, FRoundInfo, Info);

// For broadcasting things like round change or contestant change
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIndexChanged, int, EventIndex);

// For broadcasting things like round change or contestant change
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FContestantUpdate, const FContestant&, Contestant);

// For broadcasting activation of token, f.e. Wild Card
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTokenAction, EGameToken, Token);

// For broadcasting events like Buy Vowel decision
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FContestantGenericAction);

// Event that is being triggered when all letters are guessed
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPuzzleSolved);

template<typename T>
static FString WoF_EnumToString(const char* EnumName, T EnumValue)
{
	static const FString InvalidEnum("Invalid");

	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, UTF8_TO_TCHAR(EnumName), true);
	if (!EnumPtr)
	{
		return InvalidEnum;
	}
	return EnumPtr->GetNameStringByIndex(static_cast<int32>(EnumValue));
}
