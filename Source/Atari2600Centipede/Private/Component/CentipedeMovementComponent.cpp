// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CentipedeMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Mushrooms/Mushrooms.h"

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
		MoveProgress += DeltaTime / TravelTime;

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
	case EGridDirection::Up:    return FVector::UpVector;
	case EGridDirection::Down:  return -FVector::UpVector;
	case EGridDirection::Left:  return FVector::RightVector;
	case EGridDirection::Right: return -FVector::RightVector;
	default:                    return FVector::ZeroVector;
	}
}

void UCentipedeMovementComponent::MoveInDirection(EGridDirection Direction, int32 Cells)
{
	if (!GridReference || bIsMoving)
		return;
	
	CurrentDirection = Direction;

	if (Direction == EGridDirection::Right || Direction == EGridDirection::Left)
	{
		LastHorizontal = Direction;
	}

	FVector DirVector = GetDirectionVector(Direction);
	float CellSize = GridReference->CellSize;

	StartLocation = GetOwner()->GetActorLocation();
	TargetLocation = StartLocation + DirVector * CellSize * Cells;
	
	FVector ClampedLocation;
	
	ClampedLocation.X = FMath::Clamp(TargetLocation.X, GridReference->GetGridBounds().Min.X, GridReference->GetGridBounds().Max.X);
	ClampedLocation.Y = FMath::Clamp(TargetLocation.Y, GridReference->GetGridBounds().Min.Y, GridReference->GetGridBounds().Max.Y);
	ClampedLocation.Z = FMath::Clamp(TargetLocation.Z, GridReference->GetGridBounds().Min.Z, GridReference->GetGridBounds().Max.Z);

	TargetLocation = ClampedLocation;

	TravelDistance = FVector::Distance(StartLocation, TargetLocation);
	TravelTime = TravelDistance / MoveSpeed; 
	MoveProgress = 0.f;
	bIsMoving = true;
}


void UCentipedeMovementComponent::HandleMovementPattern()
{
	if (bIsMoving) return;

	UE_LOG(LogTemp, Warning, TEXT("Current Direction: %s"), *UEnum::GetValueAsString(CurrentDirection));

	
	switch (CurrentDirection)
	{
	case EGridDirection::Right:
		MoveInDirection(EGridDirection::Right, 99);
		CurrentDirection = EGridDirection::Down;
		break;

	case EGridDirection::Left:
		MoveInDirection(EGridDirection::Left, 99);
		CurrentDirection = EGridDirection::Down;
		break;

	case EGridDirection::Down:
		
		MoveInDirection(EGridDirection::Down, 1);

		CurrentDirection = (LastHorizontal == EGridDirection::Right) ? EGridDirection::Left : EGridDirection::Right;
		LastHorizontal = CurrentDirection;
		
		break;
	}
}

void UCentipedeMovementComponent::StopAndSnapToGrid()
{
	if (!GridReference)
		return;
	
	bIsMoving = false;
	MoveProgress = 0.f;
	
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	const float CellSize = GridReference->CellSize;
	
	FVector SnappedLocation;
	SnappedLocation.X = GetOwner()->GetActorLocation().X;
	SnappedLocation.Y = GetOwner()->GetActorLocation().Y;
	SnappedLocation.Z = FMath::GridSnap(CurrentLocation.Z, CellSize);
	
	const FBound Bounds = GridReference->GetGridBounds();
	SnappedLocation.X = FMath::Clamp(SnappedLocation.X, Bounds.Min.X, Bounds.Max.X);
	SnappedLocation.Y = FMath::Clamp(SnappedLocation.Y, Bounds.Min.Y, Bounds.Max.Y);
	SnappedLocation.Z = FMath::Clamp(SnappedLocation.Z, Bounds.Min.Z, Bounds.Max.Z);

	GetOwner()->SetActorLocation(SnappedLocation);
	
	OnMovementComplete.Broadcast(SnappedLocation);
	
}