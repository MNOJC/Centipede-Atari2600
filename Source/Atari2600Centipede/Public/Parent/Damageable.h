// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Health_Component.h"
#include "GameFramework/Actor.h"
#include "Damageable.generated.h"

UCLASS()
class ATARI2600CENTIPEDE_API ADamageable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamageable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UHealth_Component* HealthComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Damage();
};
