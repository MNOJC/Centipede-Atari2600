// Fill out your copyright notice in the Description page of Project Settings.


#include "Centipede/CentipedeSegment.h"

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

		SetActorEnableCollision(false);
	}

	if (!bIsHead && CentipedeEntity)
	{
		SetActorEnableCollision(false);
		int32 DelayIndex = FMath::FloorToInt(20.0f * IndexInChain);
		
		if (CentipedeEntity->Trail.Num() > DelayIndex)
		{
			FVector TargetPos = CentipedeEntity->Trail[DelayIndex];
			
			FVector NewPos = FMath::VInterpTo(GetActorLocation(), TargetPos, DeltaTime, 20.f);
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
	if (bIsHead)
	MovementComponent->StopAndSnapToGrid();
}

void ACentipedeSegment::OnSegmentMoveFinished(FVector NewLocation)
{
	if (bIsHead)
	MovementComponent->HandleMovementPattern();
}

