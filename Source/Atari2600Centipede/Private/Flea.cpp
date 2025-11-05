// Fill out your copyright notice in the Description page of Project Settings.


#include "Flea.h"
#include "EngineUtils.h"
#include "Mushrooms/Mushrooms.h"

// Sets default values
AFlea::AFlea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);
	
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	SpriteComponent->SetupAttachment(RootScene);
	SpriteComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	SpriteComponent->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SpriteComponent->SetGenerateOverlapEvents(true);

	static ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteAsset(TEXT("/Game/Art/Textures/SpriteSheet/Sprites/Sprites_01/T_Flea_0.T_Flea_0"));
	SpriteComponent->SetSprite(SpriteAsset.Object);

	HealthComponent->SetDefaultHealth(2);
	HealthComponent->SetPoints(200);
}

// Called when the game starts or when spawned
void AFlea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TargetLoc = FVector(this->GetActorLocation().X, this->GetActorLocation().Y, -300.0f);
	FVector NewLocation = FMath::VInterpConstantTo(this->GetActorLocation(), TargetLoc, DeltaTime, FallSpeed);
	this->SetActorLocation(NewLocation);

	if (TargetLoc == GetActorLocation())
	{
		this->Destroy();
	}

	TimeSinceLastSpawn += DeltaTime;

	int32 MushroomCount = 0;

	for (TActorIterator<AMushrooms> It(GetWorld()); It; ++It)
	{
		++MushroomCount;
	}
	
	if (TimeSinceLastSpawn >= FMath::RandRange(SpawnIntervalMin, SpawnIntervalMax) && MushroomCount < 40)
	{

		TimeSinceLastSpawn = 0.0f;


		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		GetWorld()->SpawnActor<AMushrooms>(
			AMushrooms::StaticClass(),
			GetActorLocation(),
			FRotator::ZeroRotator,
			SpawnParams
		);
	}
}

void AFlea::Damage()
{
	Super::Damage();
	FallSpeed = 1200;
}

