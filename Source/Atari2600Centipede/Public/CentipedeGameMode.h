// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CentipedeCamera.h"
#include "CentipedeEntity.h"
#include "CentipedeManager.h"
#include "CentipedColorDA.h"
#include "GameFramework/GameModeBase.h"
#include "CentipedeGridGenerator.h"
#include "MushroomsManager.h"
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

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Materials")
	UMaterialInstanceDynamic* PlayerMat;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Materials")
	UMaterialParameterCollectionInstance* MPCi;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Materials")
	UMaterialInstanceDynamic* CentipedeMat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int Score;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int Level = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Colors")
	TArray<TSoftObjectPtr<UCentipedColorDA>> T_Colors_ptr;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Colors")
	TMap<FName, UMaterialInstanceDynamic*> MaterialMap;
	

	ACentipedeGameMode();

public:

	// Grid
	void SpawnAndInitializeGrid();
	void SpawnCentipedeManager();
	void SpawnAndInitializeMushroomsManager();
	void InitializeCentipedeCamera();
	
 	TObjectPtr<ACentipedeGridGenerator>  SpawnedGrid;
	TObjectPtr<AMushroomsManager> SpawnedMushroomsManager;
	TObjectPtr<ACentipedeManager> SpawnedCentipedeManager;
	TObjectPtr<ACentipedeCamera> CentipedeCameraActor;

	TArray<FVector> GridPoints;


	
	UFUNCTION(BlueprintCallable, Category = "Centipede")
	int GetScore() const {return Score;}

	
	UFUNCTION(BlueprintCallable, Category = "Centipede")
	void AddScore(int Amount);

	UFUNCTION(BlueprintCallable, Category = "Centipede")
	void SetScore(int _Score) {Score = _Score;}

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, NewScore);
	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;
	
	UFUNCTION(BlueprintCallable, Category = "Materials")
	void AddMaterial(FName Tag, UMaterialInstanceDynamic* Material);


	void NextLevel();

	UMaterialInstanceDynamic* GetMaterialByTag(FName Tag);

	UFUNCTION(Exec)
	void SkipLevel();
	
};
