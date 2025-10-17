// Fill out your copyright notice in the Description page of Project Settings.


#include "Centipede/CentipedeManager.h"

#include "Centipede/CentipedeEntity.h"
#include "Core/CentipedeGameMode.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACentipedeManager::ACentipedeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACentipedeManager::BeginPlay()
{
	Super::BeginPlay();
	
if(ACentipedeGameMode* GM = Cast<ACentipedeGameMode>(GetWorld()->GetAuthGameMode()))
	SpawnCentipede(20, FVector(0.0f, GM->SpawnedGrid->GetGridBounds().Max.Y, GM->SpawnedGrid->GetGridBounds().Max.Z), EGridDirection::Right);
}

// Called every frame
void ACentipedeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ACentipedeEntity* ACentipedeManager::SpawnCentipede(int NumSegments, FVector StartPos, EGridDirection StartDir)
{
	FActorSpawnParameters Params;
	ACentipedeEntity* NewCenti = GetWorld()->SpawnActor<ACentipedeEntity>(ACentipedeEntity::StaticClass(), StartPos, FRotator::ZeroRotator, Params);

	if (NewCenti)
	{
		NewCenti->Initialize(this, NumSegments, StartPos, StartDir);
		ActiveCentipedes.Add(NewCenti);
	}

	return NewCenti;
}

void ACentipedeManager::OnSegmentDestroyed(ACentipedeEntity* Parent, int32 SegmentIndex)
{
	
}

