// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid/CentipedeGridGenerator.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "CentipedeMovementComponent.generated.h"

UENUM(BlueprintType)
enum class EGridDirection : uint8
{
	Up,
	Down,
	Left,
	Right
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementComplete, FVector, NewLocation);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATARI2600CENTIPEDE_API UCentipedeMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCentipedeMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TObjectPtr<ACentipedeGridGenerator> GridReference;
	
	float MoveSpeed = 500.0f;
	bool bIsMoving = false;
	EGridDirection CurrentDirection;
	
	FOnMovementComplete OnMovementComplete;

private:
	
	FVector StartLocation;
	FVector TargetLocation;
	float MoveProgress = 0.f;
	EGridDirection LastHorizontal;
	float TravelDistance = 0.f;
	float TravelTime = 0.f;

	FVector GetDirectionVector(EGridDirection Direction) const;
	
	
public:
	
	void MoveInDirection(EGridDirection Direction, int32 Cells);
	void HandleMovementPattern();
	void StopAndSnapToGrid();
	
};
