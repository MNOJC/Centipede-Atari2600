// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/CentipedeMovementComponent.h"
#include "GameFramework/Actor.h"
#include "CentipedeEntity.generated.h"

class ACentipedeSegment;
class ACentipedeManager;

UCLASS()
class ATARI2600CENTIPEDE_API ACentipedeEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACentipedeEntity();

	void Initialize(ACentipedeManager* InManager, int32 NumSegments, const FVector& StartPos, EGridDirection Direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<FVector> Trail;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCentipedeMovementComponent* CentipedeMovementComponent;

	

private:

	UFUNCTION()
	void OnCentipedeMovementComplete(FVector NewLocation);

	FTimerHandle MyTimerHandle;
	void StartCentipedeMovement();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	EGridDirection CurrentDirection;
	TObjectPtr<ACentipedeManager> Manager;
	TArray<ACentipedeSegment*> Segments;
};
