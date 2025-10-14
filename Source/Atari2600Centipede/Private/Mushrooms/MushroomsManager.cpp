// Fill out your copyright notice in the Description page of Project Settings.

#include "Mushrooms/Mushrooms.h"
#include "Algo/RandomShuffle.h"
#include "Mushrooms/MushroomsManager.h"

// Sets default values
AMushroomsManager::AMushroomsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMushroomsManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMushroomsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMushroomsManager::GenerateMushroomsOnGrid(TArray<FVector> GridPoints, int32 MinCount, int32 MaxCount)
{
	if (GridPoints.Num() == 0 || MinCount > MaxCount)
		return;
	
	GridPoints.RemoveAll([](const FVector& Point)
	{
		return Point.Z == 0.0f;
	});

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
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		GetWorld()->SpawnActor<AMushrooms>(AMushrooms::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	}
}

