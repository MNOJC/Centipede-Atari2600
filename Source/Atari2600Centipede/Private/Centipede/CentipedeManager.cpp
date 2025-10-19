// Fill out your copyright notice in the Description page of Project Settings.


#include "Centipede/CentipedeManager.h"

#include "Centipede/CentipedeEntity.h"
#include "Core/CentipedeGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Centipede/CentipedeSegment.h"
#include "Log/CentipedeLoggerCategories.h"

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
	SpawnCentipede(11, FVector(0.0f, GM->SpawnedGrid->GetGridBounds().Max.Y, GM->SpawnedGrid->GetGridBounds().Max.Z), EGridDirection::Right, TArray<FVector>());
}

// Called every frame
void ACentipedeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ACentipedeEntity* ACentipedeManager::SpawnCentipede(int NumSegments, FVector StartPos, EGridDirection StartDir, TArray<FVector> SegmentPos)
{
	if (NumSegments <= 0)
	{
		return nullptr;
	}
	
	FActorSpawnParameters Params;
	ACentipedeEntity* NewCenti = GetWorld()->SpawnActor<ACentipedeEntity>(ACentipedeEntity::StaticClass(), StartPos, FRotator::ZeroRotator, Params);

	if (NewCenti)
	{
		NewCenti->Initialize(this, NumSegments, StartPos, StartDir, SegmentPos);
		ActiveCentipedes.Add(NewCenti);
	}

	UE_LOG(LogCentipede, Warning, TEXT("Nombre de centipedes actifs : %d"), ActiveCentipedes.Num());

	return NewCenti;
}

void ACentipedeManager::OnSegmentDestroyed(ACentipedeEntity* Parent, int32 SegmentIndex)
{
	
	const int32 SegmentCount = Parent->Segments[SegmentIndex]->CountNextSegments(Parent->Segments[SegmentIndex]) - 1 ;
	
	SpawnCentipede(
		SegmentCount,
		Parent->Segments[SegmentIndex]->GetActorLocation(),
		Parent->Segments[SegmentIndex]->MovementComponent->CurrentDirection,
		Parent->Segments[SegmentIndex]->GetNextSegmentsPositions(Parent->Segments[SegmentIndex]
			));
	
	Parent->Segments[SegmentIndex]->DeleteNextSegments(Parent->Segments[SegmentIndex]);
	Parent->Segments[SegmentIndex]->Destroy();
	Parent->SetGarbageEliminationEnabled(true);
}

