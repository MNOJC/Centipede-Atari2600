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
	SpawnCentipede(11, FVector(0.0f, GM->SpawnedGrid->GetGridBounds().Max.Y, GM->SpawnedGrid->GetGridBounds().Max.Z), EGridDirection::Right, TArray<FVector>(), TArray<FVector>());
}

// Called every frame
void ACentipedeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ACentipedeEntity* ACentipedeManager::SpawnCentipede(int NumSegments, FVector StartPos, EGridDirection StartDir, TArray<FVector> SegmentPos, TArray<FVector> NewTrail)
{
	if (NumSegments <= 0)
	{
		return nullptr;
	}
	
	FActorSpawnParameters Params;
	ACentipedeEntity* NewCenti = GetWorld()->SpawnActor<ACentipedeEntity>(ACentipedeEntity::StaticClass(), StartPos, FRotator::ZeroRotator, Params);

	if (NewCenti)
	{
		NewCenti->Initialize(this, NumSegments, StartPos, StartDir, SegmentPos, NewTrail);
		ActiveCentipedes.Add(NewCenti);
	}

	UE_LOG(LogCentipede, Warning, TEXT("Nombre de centipedes actifs : %d"), ActiveCentipedes.Num());

	return NewCenti;
}

void ACentipedeManager::OnSegmentDestroyed(ACentipedeEntity* Parent, int32 SegmentIndex)
{
	int32 SegmentCount = Parent->Segments[SegmentIndex]->CountNextSegments(Parent->Segments[SegmentIndex]);

	if (Parent->Segments[SegmentIndex]->NextSegment == nullptr)
	{
		SegmentCount = 0;
	}
	else if (Parent->Segments[SegmentIndex]->NextSegment->IsPendingKillPending())
	{
		SegmentCount = 0;
	}
	
	int32 TrimCount = 14 * (SegmentIndex + 1);
	
	TArray<FVector> NewTrimTrailArray;

	if (TrimCount < Parent->Trail.Num())
	{
		NewTrimTrailArray.Append(Parent->Trail.GetData() + TrimCount, Parent->Trail.Num() - TrimCount);
	}

	SpawnCentipede(
		SegmentCount,
		Parent->Segments[SegmentIndex]->GetActorLocation(),
		Parent->Segments[0]->MovementComponent->LastHorizontal,
		Parent->Segments[SegmentIndex]->GetNextSegmentsPositions(Parent->Segments[SegmentIndex]),
		NewTrimTrailArray
			);
	
	Parent->Segments[SegmentIndex]->DeleteNextSegments(Parent->Segments[SegmentIndex]);
	Parent->Segments[SegmentIndex]->Destroy();
	Parent->SetGarbageEliminationEnabled(true);
}

