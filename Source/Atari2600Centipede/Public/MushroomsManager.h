// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Subsystems/WorldSubsystem.h"
#include "CentipedeGridGenerator.h"
#include "MushroomsManager.generated.h"



UCLASS()
class ATARI2600CENTIPEDE_API UMushroomsManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:	

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;

public:	

	void GenerateMushroomsOnGrid(TArray<FVector> GridPoints, int32 MinCount, int32 MaxCount);

	TObjectPtr<ACentipedeGridGenerator> Grid;

};
