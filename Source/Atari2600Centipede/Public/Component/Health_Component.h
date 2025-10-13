// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health_Component.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATARI2600CENTIPEDE_API UHealth_Component : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealth_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int DefaultHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	int Health;

public:

	void Damage(int DamageAmount);
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	int GetHealth() const { return Health; }

	
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return Health <= 0.0f; }
	
};
