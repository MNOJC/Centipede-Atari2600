// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/Health_Component.h"

#include "Core/CentipedeGameMode.h"
#include "Core/CentipedeHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Log/CentipedeLoggerCategories.h"

// Sets default values for this component's properties
UHealth_Component::UHealth_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealth_Component::BeginPlay()
{	
	Super::BeginPlay();
	Health = DefaultHealth;
}

void UHealth_Component::BeginDestroy()
{
	Super::BeginDestroy();
}
void UHealth_Component::HandleDeath() const
{
	Cast<ACentipedeGameMode>(GetWorld()->GetAuthGameMode())->AddScore(Points);

	// Now safe to destroy the actor
	GetOwner()->Destroy();
}

void UHealth_Component::Damage()
{
	Health -= 1;
	if (IsDead()) HandleDeath();
}