// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile/CentipedeProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "PaperSprite.h"
#include "Interface/DamageInterface.h"
#include "Parent/Damageable.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ACentipedeProjectile::ACentipedeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	SpriteComponent->SetupAttachment(RootScene);
	
	static ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteAsset(TEXT("/Game/Art/Textures/SpriteSheet/Sprites/Sprites_01/T_Snake_1.T_Snake_1"));
	SpriteComponent->SetSprite(SpriteAsset.Object);
	
	SpriteComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SpriteComponent->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Block);
	SpriteComponent->SetNotifyRigidBodyCollision(true);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootScene;
	ProjectileMovement->InitialSpeed = 5000.0f;
	ProjectileMovement->MaxSpeed = 5000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->SetVelocityInLocalSpace(FVector(0.0f, 0.0f, 1.0f));
	ProjectileMovement->SetPlaneConstraintEnabled(true);
	ProjectileMovement->SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));
	

}

// Called when the game starts or when spawned
void ACentipedeProjectile::BeginPlay()
{
	Super::BeginPlay();

	CentipedeGameMode = Cast<ACentipedeGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	OnActorBeginOverlap.AddDynamic(this, &ACentipedeProjectile::OnOverlap);
}

void ACentipedeProjectile::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ADamageable* _hitActor = Cast<ADamageable>(OtherActor))
	{
		_hitActor->Damage();
		Destroy();
	}
			
}


// Called every frame
void ACentipedeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckProjectileConstraints();

}

void ACentipedeProjectile::CheckProjectileConstraints()
{
	if (CentipedeGameMode)
	{
		if (this->GetActorLocation().Z >= CentipedeGameMode->SpawnedGrid->GetGridBounds().Max.Z)
		{
			this->Destroy();
		}
	
	}
}

