// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter/MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
	

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeCentipedeCamera();
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ACentipedePlayerController* PC = Cast<ACentipedePlayerController>(NewController))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
			EnhancedInput->BindAction(IA_Shoot, ETriggerEvent::Started, this, &AMainCharacter::Shoot);
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
	
}

void AMainCharacter::InitializeCentipedeCamera()
{
	if (!GetWorld()) return;

	FVector CameraLocation(500.f, 0.f, 0.f);   
	FRotator CameraRotation(0.f, 180.f, 0.f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	CentipedeCameraActor = GetWorld()->SpawnActor<ACentipedeCamera>(ACentipedeCamera::StaticClass(), CameraLocation, CameraRotation, SpawnParams);


	if (CentipedeCameraActor)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			PC->SetViewTarget(CentipedeCameraActor);
		}
	}
}




