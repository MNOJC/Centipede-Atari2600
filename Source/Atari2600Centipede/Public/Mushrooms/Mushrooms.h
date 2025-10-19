// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "PaperSprite.h"
#include "Projectile/CentipedeProjectile.h"
#include "Component/Health_Component.h"
#include "Parent/Damageable.h"
#include "Mushrooms.generated.h"


class UPaperSpriteComponent;

UCLASS()
class ATARI2600CENTIPEDE_API AMushrooms : public ADamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMushrooms();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UPaperFlipbookComponent* FlipbookComponent;
	
	
	UFUNCTION()
	virtual void Damage() override;
};
