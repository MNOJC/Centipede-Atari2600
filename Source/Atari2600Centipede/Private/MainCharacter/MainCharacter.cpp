// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter/MainCharacter.h"
#include "Log/CentipedeLoggerCategories.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperSprite.h"
#include "Core/CentipedeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Log/CentipedeLoggerCategories.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	SpriteComponent->SetupAttachment(RootScene);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootScene;

	
	SpriteComponent->SetSprite(LoadObject<UPaperSprite>(nullptr,TEXT("/Game/Art/Textures/SpriteSheet/Sprites/Sprites_01/T_Snake_2.T_Snake_2")));
	SpriteComponent->SetMaterial(0,LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Art/Materials/M_Sprites_Centipede.M_Sprites_Centipede")));
	SpriteComponent->SetRelativeScale3D(FVector(10,10,10));
	SpriteComponent->SetRelativeRotation(FRotator(0, -90, 0));
	MovementComponent->Acceleration = 15000.0f;
	MovementComponent->Deceleration = 100000.0f;
	MovementComponent->MaxSpeed = 2000.0f;
	


	static ConstructorHelpers::FObjectFinder<UInputAction> MovementActionFinder(TEXT("/Game/Input/InputActions/IA_Movement.IA_Movement"));
	IA_Movement = MovementActionFinder.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> ShootActionFinder(TEXT("/Game/Input/InputActions/IA_Shoot.IA_Shoot"));
	IA_Shoot = ShootActionFinder.Object;

	

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	CentipedeGameMode = Cast<ACentipedeGameMode>(GetWorld()->GetAuthGameMode());
	InitializeCentipedeCamera();
	GridBounds = CentipedeGameMode->SpawnedGrid->GetGridBounds();
	SpriteComponent->SetMaterial(0,Cast<ACentipedeGameMode>(GetWorld()->GetAuthGameMode())->GetMaterialByTag("Player"));
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ConstraintPlayerInBounds();
	
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Movement)
		{
			EnhancedInput->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		}
		if (IA_Shoot)
		{
			EnhancedInput->BindAction(IA_Shoot, ETriggerEvent::Triggered, this, &AMainCharacter::Shoot);
		}
	}

}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	AddMovementInput(FVector(0, 1, 0), MovementVector.X, true);
	AddMovementInput(FVector(0, 0, 1), MovementVector.Y, true);
	
}

void AMainCharacter::Shoot(const FInputActionValue& Value)
{
	if (!GetWorld()) return;

	const FVector SpawnLocation  = this->GetActorLocation();
	const FRotator SpawnRotation  = FRotator(0.0f, 0.0f, 0.0f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	ACentipedeProjectile* Projectile = GetWorld()->SpawnActor<ACentipedeProjectile>(ACentipedeProjectile::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	UE_LOG(LogCentipede, Log, TEXT("Try spawn projectile"));
}

void AMainCharacter::InitializeCentipedeCamera()
{
	if (!GetWorld()) return;

	if (CentipedeGameMode)
	{
		const FVector CenterLocation = CentipedeGameMode->SpawnedGrid->GetGridCenterLocation();

		const FVector CameraLocation(500.f, CenterLocation.Y, CenterLocation.Z - 200);   
		const FRotator CameraRotation(0.f, 180.f, 0.f);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		CentipedeCameraActor = GetWorld()->SpawnActor<ACentipedeCamera>(ACentipedeCamera::StaticClass(), CameraLocation, CameraRotation, SpawnParams);
	}

	if (CentipedeCameraActor)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			PC->SetViewTarget(CentipedeCameraActor);
		}
	}
}

void AMainCharacter::ConstraintPlayerInBounds()
{
	const float ClampedLocationY = FMath::Clamp(this->GetActorLocation().Y, GridBounds.Min.Y, GridBounds.Max.Y);
	const float ClampedLocationZ = FMath::Clamp(this->GetActorLocation().Z, GridBounds.Min.Z, CustomZConstraint);
	
	this->SetActorLocation(FVector(this->GetActorLocation().X, ClampedLocationY,ClampedLocationZ));
}




