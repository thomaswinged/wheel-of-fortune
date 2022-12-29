#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable, HideCategories=(Replication, Input, Cooking, LOD))
class WHEELOFFORTUNE_API APooledActor : public AActor
{
	GENERATED_BODY()

public:
#pragma region Functions
	APooledActor();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Object Pooling")
	void SetActive(bool bInActive);
	
	UFUNCTION(BlueprintCallable, Category="Object Pooling")
	bool IsActive();

	UFUNCTION(BlueprintCallable, Category="Object Pooling")
	void ReturnToPool();
#pragma endregion 

protected:
#pragma region Functions
	virtual void BeginPlay() override;
#pragma endregion

private:
#pragma region Properties
	UPROPERTY()
	bool bActive;
#pragma endregion 
};
