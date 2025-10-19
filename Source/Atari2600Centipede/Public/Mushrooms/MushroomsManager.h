// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid/CentipedeGridGenerator.h"
#include "MushroomsManager.generated.h"



UCLASS()
class ATARI2600CENTIPEDE_API AMushroomsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMushroomsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GenerateMushroomsOnGrid(TArray<FVector> GridPoints, int32 MinCount, int32 MaxCount);

	TObjectPtr<ACentipedeGridGenerator> Grid;

};
