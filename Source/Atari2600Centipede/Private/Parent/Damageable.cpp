// Fill out your copyright notice in the Description page of Project Settings.


#include "Parent/Damageable.h"


// Sets default values
ADamageable::ADamageable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	HealthComponent = CreateDefaultSubobject<UHealth_Component>(TEXT("HealthComp"));
}

// Called when the game starts or when spawned
void ADamageable::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ADamageable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ADamageable::Damage(int DamageAmount)
{
	HealthComponent->Damage(DamageAmount);
}
