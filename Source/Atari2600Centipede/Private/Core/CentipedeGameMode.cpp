// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CentipedeGameMode.h"

void ACentipedeGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnAndInitializeGrid();
}

void ACentipedeGameMode::SpawnAndInitializeGrid()
{
	if (!GridClass || !GetWorld()) return;

	FVector SpawnLocation(0.f, 0.f, 0.f);
	FRotator SpawnRotation(0.f, 0.f, 0.f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	SpawnedGrid = GetWorld()->SpawnActor<ACentipedeGridGenerator>(GridClass, SpawnLocation, SpawnRotation, SpawnParams);
	SpawnedGrid->GenerateGrid();

}
