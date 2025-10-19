// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CentipedeManager.generated.h"

enum class EGridDirection : uint8;
class ACentipedeEntity;

UCLASS

()
class ATARI2600CENTIPEDE_API ACentipedeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACentipedeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	ACentipedeEntity* SpawnCentipede(int NumSegments, FVector StartPos, EGridDirection StartDir, TArray<FVector> SegmentPos);

	void OnSegmentDestroyed(ACentipedeEntity* Parent, int32 SegmentIndex);

protected:

	TArray<ACentipedeEntity*> ActiveCentipedes;
};
