// Fill out your copyright notice in the Description page of Project Settings.


#include "Mushrooms/Mushrooms.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
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

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperSprite"));
	FlipbookComponent->SetupAttachment(RootScene);

	FlipbookComponent->SetFlipbook(LoadObject<UPaperFlipbook>(nullptr,TEXT("/Game/Art/Textures/SpriteSheet/FlipBook/T_Shroom.T_Shroom")));
	FlipbookComponent->SetPlaybackPositionInFrames(4,false);
	FlipbookComponent->SetLooping(false);
	FlipbookComponent->Stop();
	FlipbookComponent->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
	FlipbookComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	FlipbookComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	FlipbookComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	FlipbookComponent->SetGenerateOverlapEvents(true);

	FlipbookComponent->SetMaterial(0,LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Art/Materials/M_Sprites_Mobs.M_Sprites_Mobs")));

	HealthComponent = CreateDefaultSubobject<UHealth_Component>(TEXT("HealthComp"));
	HealthComponent -> SetDefaultHealth(4);
	HealthComponent -> SetPoints(100);
	
	
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
	FlipbookComponent->SetPlaybackPositionInFrames(HealthComponent->GetHealth(), false);
	return true;
}


