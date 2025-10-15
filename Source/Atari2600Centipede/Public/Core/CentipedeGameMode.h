// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Centipede/CentipedeEntity.h"
#include "GameFramework/GameModeBase.h"
#include "Grid/CentipedeGridGenerator.h"
#include "Mushrooms/MushroomsManager.h"
#include "CentipedeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ATARI2600CENTIPEDE_API ACentipedeGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	ACentipedeGameMode();

public:

	// Grid
	void SpawnAndInitializeGrid();
	void SpawnCentipedeEntity();
	void SpawnAndInitializeMushroomsManager();
	
 	TSoftObjectPtr<ACentipedeGridGenerator>  SpawnedGrid;
	TSoftObjectPtr<AMushroomsManager> SpawnedMushroomsManager;
	TSoftObjectPtr<ACentipedeEntity> SpawnedCentipedeEntity; //Temp plus tard remplacer par le mananager centipede

	TArray<FVector> GridPoints;
	
};
