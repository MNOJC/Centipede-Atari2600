// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/CentipedeGameMode.h"

#include "Centipede/CentipedeManager.h"
#include "MainCharacter/MainCharacter.h"
#include "Core/CentipedeHUD.h"


void ACentipedeGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnAndInitializeGrid();
	SpawnAndInitializeMushroomsManager();
	SpawnCentipedeManager();
}

ACentipedeGameMode::ACentipedeGameMode()
{
	PlayerControllerClass = ACentipedePlayerController::StaticClass();
	DefaultPawnClass = AMainCharacter::StaticClass();
	HUDClass = ACentipedeHUD::StaticClass();
}

void ACentipedeGameMode::SpawnAndInitializeGrid()
{
	if (!GetWorld()) return;

	const FVector SpawnLocation(0.f, 0.f, 0.f);
	const FRotator SpawnRotation(0.f, 0.f, 0.f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	SpawnedGrid = GetWorld()->SpawnActor<ACentipedeGridGenerator>(ACentipedeGridGenerator::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	GridPoints = SpawnedGrid->GenerateGrid();
	
}

void ACentipedeGameMode::SpawnCentipedeManager()
{
	if (!GetWorld()) return;

	const FVector SpawnLocation(0.f,0.f, 0.f);
	const FRotator SpawnRotation(0.f, 0.f, 0.f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	SpawnedCentipedeManager = GetWorld()->SpawnActor<ACentipedeManager>(SpawnLocation, SpawnRotation, SpawnParams);
	
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

	SpawnedMushroomsManager->GenerateMushroomsOnGrid(GridPoints, 25, 30);
}
