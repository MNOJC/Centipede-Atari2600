// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "PaperSprite.h"
#include "Projectile/CentipedeProjectile.h"
#include "Mushrooms.generated.h"


class UPaperSpriteComponent;

UCLASS()
class ATARI2600CENTIPEDE_API AMushrooms : public AActor
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
	UPaperSpriteComponent* SpriteComponent;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

};
