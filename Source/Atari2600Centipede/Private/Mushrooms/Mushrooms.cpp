// Fill out your copyright notice in the Description page of Project Settings.


#include "Mushrooms/Mushrooms.h"

// Sets default values
AMushrooms::AMushrooms()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	SpriteComponent->SetupAttachment(RootScene);
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

