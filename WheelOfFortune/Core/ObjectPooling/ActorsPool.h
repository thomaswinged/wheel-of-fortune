#pragma once

#include "CoreMinimal.h"
#include "PooledActor.h"
#include "GameFramework/Actor.h"
#include "ActorsPool.generated.h"

UCLASS(Abstract, HideCategories=(Rendering, Replication, Collision, Input, Cooking, Actor, LOD))
class WHEELOFFORTUNE_API AActorsPool : public AActor
{
	GENERATED_BODY()

public:
#pragma region Functions
	AActorsPool();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Object Pooling")
	bool GetActorFromPool(APooledActor*& Actor);
	
	UFUNCTION(BlueprintCallable, Category="Object Pooling")
	void ReturnAllActorsToPool();
#pragma endregion 

#pragma region Properties
	UPROPERTY(EditAnywhere, Category="Object Pooling")
	TSubclassOf<APooledActor> PooledActorType;

	UPROPERTY(EditAnywhere, Category="Object Pooling")
	int PoolSize = 100;
#pragma endregion 

protected:
#pragma region Functions
	virtual void BeginPlay() override;
#pragma endregion 

private:
#pragma region Functions
	void InitializePool();
#pragma endregion 

#pragma region Properties
	UPROPERTY()
	TArray<APooledActor*> Pool;
#pragma endregion 
};
