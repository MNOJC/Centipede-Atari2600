// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "PaperSprite.h"
#include "Damageable.h"
#include "Flea.generated.h"

UCLASS()
class ATARI2600CENTIPEDE_API AFlea : public ADamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlea();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UPaperSpriteComponent* SpriteComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Damage() override;

	float FallSpeed = 800.0f;
	float SpawnIntervalMin = 0.1f;
	float SpawnIntervalMax = 0.5f; 

private:
	
	float TimeSinceLastSpawn = 0.0f;

};
