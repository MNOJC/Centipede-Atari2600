// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CentipedeMovementComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCentipedeMovementComponent::UCentipedeMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCentipedeMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	ACentipedeGridGenerator* FoundGrid = Cast<ACentipedeGridGenerator>(UGameplayStatics::GetActorOfClass(GetWorld(), ACentipedeGridGenerator::StaticClass()));
	GridReference = FoundGrid;
	
	
	
}


// Called every frame
void UCentipedeMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsMoving)
	{
		MoveProgress += DeltaTime * MoveSpeed;

		FVector NewLocation = FMath::Lerp(StartLocation, TargetLocation, MoveProgress);
		GetOwner()->SetActorLocation(NewLocation);

		if (MoveProgress >= 1.f)
		{
			GetOwner()->SetActorLocation(TargetLocation);
			bIsMoving = false;
			MoveProgress = 0.f;
			
			OnMovementComplete.Broadcast(TargetLocation);
		}
	}
}

FVector UCentipedeMovementComponent::GetDirectionVector(EGridDirection Direction) const
{
	switch (Direction)
	{
	case EGridDirection::Up:    return FVector::ForwardVector;
	case EGridDirection::Down:  return -FVector::ForwardVector;
	case EGridDirection::Left:  return FVector::RightVector;
	case EGridDirection::Right: return -FVector::RightVector;
	default:                    return FVector::ZeroVector;
	}
}

void UCentipedeMovementComponent::MoveInDirection(EGridDirection Direction, int32 Cells)
{
	if (!GridReference || bIsMoving) return;

	FVector DirVector = GetDirectionVector(Direction);
	float CellSize = GridReference->CellSize;

	StartLocation = GetOwner()->GetActorLocation();
	TargetLocation = StartLocation + DirVector * CellSize * Cells;

	MoveProgress = 0.f;
	bIsMoving = true;
}

