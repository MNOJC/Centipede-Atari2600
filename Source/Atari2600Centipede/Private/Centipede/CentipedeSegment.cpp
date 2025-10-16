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

	static ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteAsset(TEXT("/Game/Art/Textures/SpriteSheet/Sprites/Sprites_01/T_Centipede_Head_0.T_Centipede_Head_0"));
	SpriteComponent->SetSprite(SpriteAsset.Object);
	SpriteComponent->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
	SpriteComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SpriteComponent->SetRelativeLocation(FVector(1.0f, 0.0f, 0.0f));
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SpriteComponent->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ACentipedeSegment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACentipedeSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

