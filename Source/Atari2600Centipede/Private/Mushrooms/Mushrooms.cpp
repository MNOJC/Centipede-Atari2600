// Fill out your copyright notice in the Description page of Project Settings.


#include "Mushrooms/Mushrooms.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "Flea.h"
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

void AMushrooms::Damage()
{

	Super::Damage();
	FlipbookComponent->SetPlaybackPositionInFrames(HealthComponent->GetHealth(), false);

	if(!HealthComponent->IsDead())
		return;
	
	int32 MushroomCount = 0;

	for (TActorIterator<AMushrooms> It(GetWorld()); It; ++It)
	{
		++MushroomCount;
	}

	if (MushroomCount < 32)
	{
		TActorIterator<ACentipedeGridGenerator> It(GetWorld());
		TObjectPtr<ACentipedeGridGenerator> Grid = Cast<ACentipedeGridGenerator>(*It);

		
		const float RandomY = FMath::RandRange(Grid->GetGridBounds().Min.Y, Grid->GetGridBounds().Max.Y);
		FVector SpawnLocation(0.f, RandomY, Grid->GetGridBounds().Max.Z);      
		FRotator SpawnRotation(0.f, 0.f, 0.f);       
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;                    
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		AFlea* Flea = GetWorld()->SpawnActor<AFlea>(
		AFlea::StaticClass(),
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);
	}
	
}


