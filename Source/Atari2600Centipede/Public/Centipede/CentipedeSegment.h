// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Centipede/CentipedeEntity.h"
#include "Component/CentipedeMovementComponent.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCentipedeMovementComponent* MovementComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateSegmentType(bool IsHead);
	
	bool bIsHead;

	int32 MaxTrailLength = 1000;
	int32 IndexInChain = 0;

	TObjectPtr<ACentipedeSegment> PrevSegment;
	TObjectPtr<ACentipedeSegment> NextSegment;

	UFUNCTION()
	void OnSegmentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSegmentMoveFinished(FVector NewLocation);
	
	TObjectPtr<ACentipedeEntity> CentipedeEntity;
	
private:

	TObjectPtr<UPaperSprite> HeadSegmentSprite;
	TObjectPtr<UPaperSprite> TailSegmentSprite;

};
