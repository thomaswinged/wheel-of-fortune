#include "Wheel.h"

AWheel::AWheel()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel"));
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));

	SetRootComponent(Root);
	Wheel->SetupAttachment(Root);
	Arrow->SetupAttachment(Root);

	SpinTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("SpinTimeline"));
}

void AWheel::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Zones = GenerateWedgeIndexPerZoneList(Wedges);
	UpdateWedgesRadialSpan(Zones.Num());
}

TArray<int> AWheel::GenerateWedgeIndexPerZoneList(TArray<FWheelSection>& InWedges)
{
	TArray<int> Result = TArray<int>();
	
	for (int i = 0; i < InWedges.Num(); i++)
	{
		for (int j = 0; j < InWedges[i].ZonesCount; j++)
		{
			Result.Add(i);
		}
	}

	return Result;
}

void AWheel::UpdateWedgesRadialSpan(int TotalZonesCount)
{
	int WedgeStartZoneIndex = 0;
	int WedgeEndZoneIndex = 0;
	for (int i = 0; i < Wedges.Num(); i++)
	{
		WedgeEndZoneIndex += Wedges[i].ZonesCount;
		Wedges[i].RadialSpan = FVector2D(
			WedgeStartZoneIndex * 360.f / TotalZonesCount,
			WedgeEndZoneIndex * 360.f / TotalZonesCount
		);
		WedgeStartZoneIndex = WedgeEndZoneIndex;
	}
}

int AWheel::GetZonesCount() const
{
	return Zones.Num();
}

float AWheel::GetZoneAngle() const
{
	return 360.0f / Zones.Num();
}

void AWheel::BeginPlay()
{
	Super::BeginPlay();

	InitialSpinRotation = TargetSpinRotation = CurrentSpinRotation = RotationOffset;

	PrepareSpinTimeline();
}

void AWheel::PrepareSpinTimeline()
{
	if (IsValid(SpinSpeedCurve))
	{
		FOnTimelineFloat SpinTimelineCallback;
		SpinTimelineCallback.BindUFunction(this, FName("UpdateWheelRotation"));
		SpinTimeline->AddInterpFloat(SpinSpeedCurve, SpinTimelineCallback);
	
		FOnTimelineEvent SpinTimelineOnFinish;
		SpinTimelineOnFinish.BindUFunction(this, FName("FinishWheelRotation"));
		SpinTimeline->SetTimelineFinishedFunc(SpinTimelineOnFinish);
	}
}

void AWheel::UpdateWheelRotation(float Progress)
{
	const float PreviousSpinRotation = CurrentSpinRotation;
	CurrentSpinRotation = InitialSpinRotation + (TargetSpinRotation - InitialSpinRotation) * Progress;

	const FRotator TickRotation = FRotator(0, -(CurrentSpinRotation - PreviousSpinRotation), 0);
	Wheel->AddRelativeRotation(TickRotation);

	WheelRotated.Broadcast(CurrentSpinRotation);
}

void AWheel::FinishWheelRotation()
{
	const FWheelSection Wedge = GetWedgeFromRotation(CurrentSpinRotation);

	UE_LOG(LogTemp, Warning, TEXT("%s >> Wheel landed on [%s]"), ANSI_TO_TCHAR(__FUNCTION__), *Wedge.WedgeType->GetName());
	WheelLanded.Broadcast(Wedge.WedgeType, Wedge.RadialSpan);
}

FWheelSection& AWheel::GetWedgeFromRotation(float Rotation)
{
	const int ZoneIndex = CalculateZoneIndex(Rotation);
	return GetWedgeInfoInZone(ZoneIndex);
}

int AWheel::CalculateZoneIndex(const float Rotation) const
{
	const float ModuloRotation = FMath::Fmod(Rotation, 360.f);
	const int Result = FMath::Floor(FMath::GetMappedRangeValueClamped(
		FVector2D(0.f, 360.f),
		FVector2D(0.f, static_cast<float>(Zones.Num())),
		ModuloRotation
	));

	return Result;
}

FWheelSection& AWheel::GetWedgeInfoInZone(const int ZoneIndex)
{
	return Wedges[Zones[ZoneIndex]];
}

void AWheel::Spin()
{
	if (!SpinTimeline->IsPlaying())
	{
		InitialSpinRotation = TargetSpinRotation;
		const float SpinStrengthRandomization = FMath::RandRange(-SpinStrengthVariance, +SpinStrengthVariance);
		TargetSpinRotation = InitialSpinRotation + SpinStrength + SpinStrengthRandomization;

		SpinTimeline->SetPlayRate((SpinStrength - SpinStrengthRandomization) / SpinStrength / SpinDuration);
		SpinTimeline->PlayFromStart();

		const FString PredictedWedge = GetWedgeFromRotation(TargetSpinRotation).WedgeType->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s >> Succesfully spinned the wheel, it will land on [%s] wedge"), ANSI_TO_TCHAR(__FUNCTION__), *PredictedWedge);
	}
}

int AWheel::GetCurrentWedgeIndex()
{
	return Zones[CalculateZoneIndex(CurrentSpinRotation)];
}