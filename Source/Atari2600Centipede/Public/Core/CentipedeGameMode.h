// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

public:

	// Grid
	void SpawnAndInitializeGrid();

	void SpawnAndInitializeMushroomsManager();
	
	UPROPERTY(EditDefaultsOnly, Category="Grid")
	TSubclassOf<ACentipedeGridGenerator> GridClass;


 	TSoftObjectPtr<ACentipedeGridGenerator>  SpawnedGrid;
	TSoftObjectPtr<AMushroomsManager> SpawnedMushroomsManager;

	TArray<FVector> GridPoints;
	
};
