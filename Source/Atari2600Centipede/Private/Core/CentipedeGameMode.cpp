// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CentipedeGameMode.h"

void ACentipedeGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnAndInitializeGrid();
	SpawnAndInitializeMushroomsManager();
}

void ACentipedeGameMode::SpawnAndInitializeGrid()
{
	if (!GridClass || !GetWorld()) return;

	FVector SpawnLocation(0.f, 0.f, 0.f);
	FRotator SpawnRotation(0.f, 0.f, 0.f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	SpawnedGrid = GetWorld()->SpawnActor<ACentipedeGridGenerator>(GridClass, SpawnLocation, SpawnRotation, SpawnParams);
	GridPoints = SpawnedGrid->GenerateGrid();
	
}

void ACentipedeGameMode::SpawnAndInitializeMushroomsManager()
{
	
	if (!GetWorld()) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FVector SpawnLocation = FVector::ZeroVector;      
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	SpawnedMushroomsManager = GetWorld()->SpawnActor<AMushroomsManager>(
		AMushroomsManager::StaticClass(),
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	SpawnedMushroomsManager->GenerateMushroomsOnGrid(GridPoints, 28, 32);
}
