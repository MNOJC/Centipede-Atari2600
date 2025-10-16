// Fill out your copyright notice in the Description page of Project Settings.


#include "Centipede/CentipedeEntity.h"

// Sets default values
ACentipedeEntity::ACentipedeEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	SpriteComponent->SetupAttachment(RootScene);

	static ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteAsset(TEXT("/Game/Art/Textures/SpriteSheet/Sprites/Sprites_01/T_Centipede_Head_0.T_Centipede_Head_0"));
	SpriteComponent->SetSprite(SpriteAsset.Object);
	SpriteComponent->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
	SpriteComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SpriteComponent->SetRelativeLocation(FVector(1.0f, 0.0f, 0.0f));
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SpriteComponent->SetGenerateOverlapEvents(true);

	
	CentipedeMovementComponent = CreateDefaultSubobject<UCentipedeMovementComponent>(TEXT("MovementComponent"));
	
}

// Called when the game starts or when spawned
void ACentipedeEntity::BeginPlay()
{
	Super::BeginPlay();
	
	SpriteComponent->OnComponentBeginOverlap.AddDynamic(this, &ACentipedeEntity::OnBeginOverlap);
	CentipedeMovementComponent->OnMovementComplete.AddDynamic(this, &ACentipedeEntity::OnCentipedeMovementComplete);

	GetWorld()->GetTimerManager().SetTimer(
		MyTimerHandle,               
		this,                           
		&ACentipedeEntity::StartCentipedeMovement,
		0.2f,                           
		false                          
	);
	
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
	//if (CentipedeMovementComponent->CurrentDirection == EGridDirection::Down)
	//{
		
	//}
	CentipedeMovementComponent->StopAndSnapToGrid();
}

