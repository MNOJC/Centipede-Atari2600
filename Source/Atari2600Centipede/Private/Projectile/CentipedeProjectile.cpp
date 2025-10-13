// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/CentipedeProjectile.h"

// Sets default values
ACentipedeProjectile::ACentipedeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	SpriteComponent->SetupAttachment(RootScene);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootScene;

}

// Called when the game starts or when spawned
void ACentipedeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACentipedeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

