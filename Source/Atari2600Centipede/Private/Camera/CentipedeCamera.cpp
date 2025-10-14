// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CentipedeCamera.h"

// Sets default values
ACentipedeCamera::ACentipedeCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootScene);
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
	CameraComponent->OrthoWidth = 2304.0f;
	CameraComponent->SetAspectRatio(4.0f / 3.0f);

}

// Called when the game starts or when spawned
void ACentipedeCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACentipedeCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

