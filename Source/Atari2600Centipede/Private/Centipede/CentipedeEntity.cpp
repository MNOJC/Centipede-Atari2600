// Fill out your copyright notice in the Description page of Project Settings.


#include "Centipede/CentipedeEntity.h"

// Sets default values
ACentipedeEntity::ACentipedeEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	CentipedeMovementComponent = CreateDefaultSubobject<UCentipedeMovementComponent>(TEXT("MovementComponent"));
	
}

void ACentipedeEntity::Initialize(ACentipedeManager* InManager, int32 NumSegments, const FVector& StartPos, EGridDirection Direction)
{
	Manager = InManager;
	CurrentDirection = Direction;
	
	if (NumSegments <= 0)
		return;

	const float SegmentSpacing = 100.f; 
	FVector DirVec = FVector::ZeroVector;

	switch (Direction)
	{
	case EGridDirection::Right: DirVec = FVector(1, 0, 0); break;
	case EGridDirection::Left:  DirVec = FVector(-1, 0, 0); break;
	case EGridDirection::Up:    DirVec = FVector(0, 1, 0); break;
	case EGridDirection::Down:  DirVec = FVector(0, -1, 0); break;
	}

	FVector CurrentPos = StartPos;

	for (int32 i = 0; i < NumSegments; ++i)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ACentipedeSegment* NewSegment = GetWorld()->SpawnActor<ACentipedeSegment>(
			ACentipedeSegment::StaticClass(),
			CurrentPos,
			FRotator::ZeroRotator,
			Params
		);

		if (NewSegment)
		{
			Segments.Add(NewSegment);
			
			if (i == 0)
				NewSegment->bIsHead = true;
			
		}


		CurrentPos -= DirVec * SegmentSpacing;
	}
}

// Called when the game starts or when spawned
void ACentipedeEntity::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ACentipedeEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACentipedeEntity::OnCentipedeMovementComplete(FVector NewLocation)
{
	CentipedeMovementComponent->HandleMovementPattern();
}

void ACentipedeEntity::StartCentipedeMovement()
{
	CentipedeMovementComponent->CurrentDirection = EGridDirection::Right;
	CentipedeMovementComponent->HandleMovementPattern();
}

void ACentipedeEntity::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CentipedeMovementComponent->StopAndSnapToGrid();
}

