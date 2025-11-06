// Fill out your copyright notice in the Description page of Project Settings.


#include "CentipedeManager.h"

#include "EngineUtils.h"
#include "CentipedeEntity.h"
#include "CentipedeGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CentipedeSegment.h"
#include "CentipedeLoggerCategories.h"
#include "Mushrooms.h"


ACentipedeEntity* UCentipedeManager::SpawnCentipede(int NumSegments, FVector StartPos, EGridDirection StartDir, TArray<FVector> SegmentPos, TArray<FVector> NewTrail)
{
	if (NumSegments <= 0)
	{
		return nullptr;
	}
	
	FActorSpawnParameters Params;
	ACentipedeEntity* NewCenti = GetWorld()->SpawnActor<ACentipedeEntity>(ACentipedeEntity::StaticClass(), StartPos, FRotator::ZeroRotator, Params);

	if (NewCenti)
	{
		NewCenti->Initialize(NumSegments, StartPos, StartDir, SegmentPos, NewTrail);
		ActiveCentipedes.Add(NewCenti);
	}

	UE_LOG(LogCentipede, Warning, TEXT("Nombre de centipedes actifs : %d"), ActiveCentipedes.Num());

	return NewCenti;
}

void UCentipedeManager::OnSegmentDestroyed(ACentipedeEntity* Parent, int32 SegmentIndex)
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


	FVector SpawnLocation = Parent->Segments[SegmentIndex]->GetActorLocation();
	FRotator SpawnRotation = FRotator::ZeroRotator;
		
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
	GetWorld()->SpawnActor<AMushrooms>(AMushrooms::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

	int CentipedeSegmentCount = 0;
	for (TActorIterator<ACentipedeSegment> It(GetWorld()); It; ++It)
	{
		++CentipedeSegmentCount;
	}

	if (CentipedeSegmentCount <= 0)
	{
		ACentipedeGameMode* GM = Cast<ACentipedeGameMode>(GetWorld()->GetAuthGameMode());
		GM->SkipLevel();
	}
}

void UCentipedeManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if(ACentipedeGameMode* GM = Cast<ACentipedeGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Yellow, TEXT("ca sedfz"));
		SpawnCentipede(11, FVector(0.0f, GM->SpawnedGrid->GetGridBounds().Max.Y, GM->SpawnedGrid->GetGridBounds().Max.Z), EGridDirection::Right, TArray<FVector>(), TArray<FVector>());
	}
		
}

void UCentipedeManager::Deinitialize()
{
	Super::Deinitialize();
}
