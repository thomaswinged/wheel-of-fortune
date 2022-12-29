#pragma once

#include "CoreMinimal.h"
#include "WheelOfFortune/Core/CommonGameData.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "WedgeActions/Wedge.h"
#include "Wheel.generated.h"

UCLASS()
class WHEELOFFORTUNE_API AWheel : public AActor
{
	GENERATED_BODY()

public:
#pragma region Functions
	AWheel();

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category="Wheel")
	void Spin();

	UFUNCTION(BlueprintImplementableEvent, Category="Wheel")
	void ChangeTopRoundValue(int NewValue); // TODO: Implement it
#pragma endregion

#pragma region Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* Wheel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* Arrow;
#pragma endregion

#pragma region Properties
	UPROPERTY(BlueprintAssignable)
	FWheelLanded WheelLanded;
#pragma endregion
	
protected:
#pragma region Functions
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	int GetZonesCount() const;

	UFUNCTION(BlueprintPure)
	float GetZoneAngle() const;

	UFUNCTION(BlueprintPure)
	int GetCurrentWedgeIndex();

	UFUNCTION(BlueprintCallable, Category="Wheel")
	int CalculateZoneIndex(float Rotation) const;

	UPROPERTY(BlueprintAssignable)
	FWheelRotated WheelRotated;
#pragma endregion
	
#pragma region Properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wheel")
	float WheelRadius = 5000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wheel")
	float RotationOffset = 0;

	UPROPERTY(EditAnywhere, Category="Wheel")
	float SpinStrength = 720.0;

	UPROPERTY(EditAnywhere, Category="Wheel")
	float SpinStrengthVariance = 180;

	UPROPERTY(EditAnywhere, Category="Wheel")
	float SpinDuration = 12;
	
	UPROPERTY(EditAnywhere, Category="Wheel")
	UCurveFloat* SpinSpeedCurve;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wheel")
	TArray<FWheelSection> Wedges;
#pragma endregion
	
private:
#pragma region Functions
	static TArray<int> GenerateWedgeIndexPerZoneList(TArray<FWheelSection>& InWedges);
	void UpdateWedgesRadialSpan(int TotalZonesCount);
	
	void PrepareSpinTimeline();

	UFUNCTION()
	void UpdateWheelRotation(float Progress);
	UFUNCTION()
	void FinishWheelRotation();

	FWheelSection& GetWedgeFromRotation(float Rotation);
	FWheelSection& GetWedgeInfoInZone(int ZoneIndex);
#pragma endregion

#pragma region Properties
	UPROPERTY()
	TArray<int> Zones;
	
	UPROPERTY()
	UTimelineComponent* SpinTimeline;
	
	float InitialSpinRotation = 0;
	float CurrentSpinRotation = 0;
	float TargetSpinRotation = 0;
#pragma endregion
};
