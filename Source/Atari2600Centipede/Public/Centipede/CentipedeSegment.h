// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "CentipedeSegment.generated.h"

UCLASS()
class ATARI2600CENTIPEDE_API ACentipedeSegment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACentipedeSegment();

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

	bool bIsHead;

};
