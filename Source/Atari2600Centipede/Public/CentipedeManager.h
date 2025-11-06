// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CentipedeManager.generated.h"

enum class EGridDirection : uint8;
class ACentipedeEntity;

UCLASS

()
class ATARI2600CENTIPEDE_API UCentipedeManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;
	
	ACentipedeEntity* SpawnCentipede(int NumSegments, FVector StartPos, EGridDirection StartDir, TArray<FVector> SegmentPos, TArray<FVector> NewTrail);

	void OnSegmentDestroyed(ACentipedeEntity* Parent, int32 SegmentIndex);

protected:

	TArray<ACentipedeEntity*> ActiveCentipedes;
};
