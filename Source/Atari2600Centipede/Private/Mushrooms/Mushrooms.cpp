// Fill out your copyright notice in the Description page of Project Settings.


#include "Mushrooms/Mushrooms.h"
#include "Log/CentipedeLoggerCategories.h"
#include "Interface/ScoreInterface.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMushrooms::AMushrooms()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	SpriteComponent->SetupAttachment(RootScene);

	static ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteAsset(TEXT("/Game/Art/Textures/SpriteSheet/Sprites/Sprites_01/T_Shroom_0.T_Shroom_0"));
	SpriteComponent->SetSprite(SpriteAsset.Object);
	
	SpriteComponent->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
	SpriteComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SpriteComponent->SetGenerateOverlapEvents(true);

	HealthComponent = CreateDefaultSubobject<UHealth_Component>(TEXT("HealthComp"));
	HealthComponent -> SetDefaultHealth(3);
	
}

// Called when the game starts or when spawned
void AMushrooms::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AMushrooms::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMushrooms::ReceiveDamage_Implementation(int DamageAmount)
{
	HealthComponent->Damage(DamageAmount);
	return true;
}


