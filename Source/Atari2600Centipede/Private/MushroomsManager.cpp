// Fill out your copyright notice in the Description page of Project Settings.

#include "MushroomsManager.h"
#include "Mushrooms.h"
#include "Algo/RandomShuffle.h"
#include "Kismet/GameplayStatics.h"

void UMushroomsManager::GenerateMushroomsOnGrid(TArray<FVector> GridPoints, int32 MinCount, int32 MaxCount)
{
	if (GridPoints.Num() == 0 || MinCount > MaxCount)
		return;

	TArray<FVector> PointsToRemove;

	AActor* GridActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACentipedeGridGenerator::StaticClass());
	Grid = Cast<ACentipedeGridGenerator>(GridActor);
	
	for (FVector Point : GridPoints)
	{
		if (Point.Z == 0.0f || Point.Z == Grid->GetGridBounds().Max.Z || Point.Y == Grid->GetGridBounds().Max.Y || Point.Y == 0)
		{
			PointsToRemove.Add(Point);
		}
	}
	
	for (const FVector& ToRemove : PointsToRemove)
	{
		GridPoints.Remove(ToRemove);
	}
	
	if (GridPoints.Num() == 0)
		return;
	
	int32 MushroomCount = FMath::RandRange(MinCount, MaxCount);
	MushroomCount = FMath::Min(MushroomCount, GridPoints.Num());
	
	Algo::RandomShuffle(GridPoints);
	
	for (int32 i = 0; i < MushroomCount; i++)
	{
		FVector SpawnLocation = GridPoints[i];
		FRotator SpawnRotation = FRotator::ZeroRotator;
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		GetWorld()->SpawnActor<AMushrooms>(AMushrooms::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	}
}

void UMushroomsManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	AActor* GridActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACentipedeGridGenerator::StaticClass());
	Grid = Cast<ACentipedeGridGenerator>(GridActor);
}

void UMushroomsManager::Deinitialize()
{
	Super::Deinitialize();
}
