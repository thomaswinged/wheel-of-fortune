#include "PooledActor.h"


APooledActor::APooledActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SetActorEnableCollision(false);
}

void APooledActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APooledActor::SetActive(bool bInActive)
{
	bActive = bInActive;
	SetActorEnableCollision(bInActive);
	SetActorHiddenInGame(!bActive);
}

bool APooledActor::IsActive()
{
	return bActive;
}

void APooledActor::ReturnToPool()
{
	SetActive(false);
}

void APooledActor::BeginPlay()
{
	Super::BeginPlay();
}