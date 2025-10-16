// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CentipedeGridGenerator.generated.h"

USTRUCT(BlueprintType)
struct FBound
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Max;

	FBound() : Min(FVector::ZeroVector), Max(FVector::ZeroVector) {}
};

UCLASS()
class ATARI2600CENTIPEDE_API ACentipedeGridGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACentipedeGridGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid settings")
	int32 SizeY = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid settings")
	int32 SizeZ = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid settings")
	float CellSize = 125.0f;

	TArray<FVector> GenerateGrid();
	FVector GetGridCenterLocation();
	FBound GetGridBounds();
	

};
