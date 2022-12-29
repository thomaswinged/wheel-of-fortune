#include "ActorsPool.h"


AActorsPool::AActorsPool()
{
	PrimaryActorTick.bCanEverTick = true;
}

#if WITH_EDITOR
void AActorsPool::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	InitializePool();
}
#endif

void AActorsPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AActorsPool::GetActorFromPool(APooledActor*& Actor)
{
	for (const auto PooledActor : Pool)
	{
		if (!PooledActor->IsActive())
		{
			Actor = PooledActor;
			return true;
		}
	}

	return false;
}

void AActorsPool::ReturnAllActorsToPool()
{
	for (const auto PooledActor : Pool)
	{
		PooledActor->SetActive(false);
		PooledActor->SetActorTransform(FTransform(GetActorLocation()));
	}
}

void AActorsPool::BeginPlay()
{
	Super::BeginPlay();
}

void AActorsPool::InitializePool()
{
	Pool.Empty();
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (const auto Actor : AttachedActors)
	{
		Actor->Destroy();
	}
	
	if (PooledActorType != nullptr)
	{
		if (UWorld* const World = GetWorld())
		{
			for (int i = 0; i < PoolSize; i++)
			{
				APooledActor* PooledActor = World->SpawnActor<APooledActor>(PooledActorType, GetActorLocation(), FRotator::ZeroRotator);
				if (ensureMsgf(PooledActor, TEXT("Could not create pooled actor during pool initialization!")))
				{
					PooledActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
					PooledActor->SetActive(false);
					Pool.Add(PooledActor);
				}
			}

			UE_LOG(LogTemp, Warning, TEXT("Created actors pool"));
		}
	}
}

