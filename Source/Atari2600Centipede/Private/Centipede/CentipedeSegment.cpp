// Fill out your copyright notice in the Description page of Project Settings.


#include "Centipede/CentipedeSegment.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Mushrooms/Mushrooms.h"
#include "Projectile/CentipedeProjectile.h"

// Sets default values
ACentipedeSegment::ACentipedeSegment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	SpriteComponent->SetupAttachment(RootScene);

	static ConstructorHelpers::FObjectFinder<UPaperSprite> HeadSpriteAsset(TEXT("/Game/Art/Textures/SpriteSheet/Sprites/Sprites_01/T_Centipede_Head_0.T_Centipede_Head_0"));
	static ConstructorHelpers::FObjectFinder<UPaperSprite> TailSpriteAsset(TEXT("/Game/Art/Textures/SpriteSheet/Sprites/Sprites_01/T_Centipede_Body_0.T_Centipede_Body_0"));
	
	HeadSegmentSprite = HeadSpriteAsset.Object;
	TailSegmentSprite = TailSpriteAsset.Object;
	
	SpriteComponent->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
	SpriteComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SpriteComponent->SetRelativeLocation(FVector(1.0f, 0.0f, 0.0f));
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SpriteComponent->SetGenerateOverlapEvents(true);

	MovementComponent = CreateDefaultSubobject<UCentipedeMovementComponent>(TEXT("Movement component"));
}

// Called when the game starts or when spawned
void ACentipedeSegment::BeginPlay()
{
	Super::BeginPlay();
	
	SpriteComponent->OnComponentBeginOverlap.AddDynamic(this, &ACentipedeSegment::OnSegmentBeginOverlap);
	MovementComponent->OnMovementComplete.AddDynamic(this, &ACentipedeSegment::OnSegmentMoveFinished);
	SetActorEnableCollision(true);
}

// Called every frame
void ACentipedeSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsHead)
	{
		
		CentipedeEntity->Trail.Insert(GetActorLocation(), 0);

		if (CentipedeEntity->Trail.Num() > MaxTrailLength)
			CentipedeEntity->Trail.RemoveAt(CentipedeEntity->Trail.Num() - 1);
	}

	if (!bIsHead && CentipedeEntity)
	{
		int32 DelayIndex = FMath::FloorToInt(20.0f * IndexInChain);
		
		if (CentipedeEntity->Trail.Num() > DelayIndex)
		{
			FVector TargetPos = CentipedeEntity->Trail[DelayIndex];
			
			FVector NewPos = FMath::VInterpTo(GetActorLocation(), TargetPos, DeltaTime, 2000.f);
			SetActorLocation(NewPos);
		}
	}
}

void ACentipedeSegment::UpdateSegmentType(bool IsHead)
{
	bIsHead = IsHead;
	
	if (bIsHead)
	{
		SpriteComponent->SetSprite(HeadSegmentSprite);
		MovementComponent->CurrentDirection = EGridDirection::Right;
		MovementComponent->HandleMovementPattern();
	}
	else
	{
		SpriteComponent->SetSprite(TailSegmentSprite);
	}
}

void ACentipedeSegment::OnSegmentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (Cast<ACentipedeProjectile>(OtherActor))
	{
		OtherActor->Destroy();
		ACentipedeManager* CtpManager = Cast<ACentipedeManager>(UGameplayStatics::GetActorOfClass(GetWorld() ,ACentipedeManager::StaticClass()));
		CtpManager->OnSegmentDestroyed(CentipedeEntity, IndexInChain);
	}
	
	if (bIsHead && Cast<AMushrooms>(OtherActor))
	{
		MovementComponent->StopAndSnapToGrid();
	}
	
}

void ACentipedeSegment::OnSegmentMoveFinished(FVector NewLocation)
{
	if (bIsHead)
	{
		MovementComponent->HandleMovementPattern();
	}
	
}

int32 ACentipedeSegment::CountPrevSegments(ACentipedeSegment* Start)
{
	if (Start == nullptr)
	{
		return 0;
	}

	if (Start->NextSegment == nullptr)
	{
		return 0;
	}
	
	int32 Count = 0;
	ACentipedeSegment* Current = Start->PrevSegment;

	while (Current)
	{
		++Count;
		
		Current = Current->PrevSegment;
	}
	
	return Count;
}

int32 ACentipedeSegment::CountNextSegments(ACentipedeSegment* Start)
{
	int32 Count = 0;
	ACentipedeSegment* Current = Start->NextSegment;

	while (Current)
	{
		++Count;
		Current = Current->NextSegment;
	}
	
	return Count;
}

void ACentipedeSegment::DeleteNextSegments(ACentipedeSegment* Start)
{
	if (!Start)
		return;

	ACentipedeSegment* Current = Start->NextSegment;

	while (Current)
	{
		ACentipedeSegment* Next = Current->NextSegment; 
		
		Current->PrevSegment = nullptr;
		Current->NextSegment = nullptr;
		
		Current->Destroy();

		Current = Next;
	}
	
	Start->NextSegment = nullptr;
}

TArray<FVector> ACentipedeSegment::GetNextSegmentsPositions(ACentipedeSegment* Start)
{
	TArray<FVector> Positions;

	if (!Start)
	{
		return Positions;
	}

	ACentipedeSegment* Current = Start->NextSegment;

	while (Current)
	{
		Positions.Add(Current->GetActorLocation());
		
		if (Current == Current->NextSegment)
		{
			break;
		}

		Current = Current->NextSegment;
	}

	return Positions;
}