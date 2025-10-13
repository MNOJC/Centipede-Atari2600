// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/CentipedeGridGenerator.h"

#include "IPropertyTable.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACentipedeGridGenerator::ACentipedeGridGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACentipedeGridGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACentipedeGridGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACentipedeGridGenerator::GenerateGrid()
{
	if (SizeY > 0 && SizeZ > 0 && CellSize > 0)
	{
		for (int32 i = 0; SizeZ > i; i++)
		{
			for (int32 y = 0; SizeY > y; y++)
			{
				const FVector CellLocation = FVector(0.0f, y * CellSize, i * CellSize);
				
				UKismetSystemLibrary::DrawDebugCircle(GetWorld(), CellLocation, 20.0f, 4, FLinearColor::Yellow, 99999.0f, 6.0f, FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), false);
			}
		}
		
	}
}

FVector ACentipedeGridGenerator::GetGridCenterLocation()
{
	return FVector(0.0f, (static_cast<float>(SizeY) / 2.0f) * CellSize, (static_cast<float>(SizeZ) / 2 ) * CellSize);
}

FBound ACentipedeGridGenerator::GetGridBounds()
{
	FBound Bound;
	Bound.Min = FVector(0.0f, 0.0f, 0.0f);
	Bound.Max = FVector(0.0f, (SizeY - 1) * CellSize, (SizeZ - 1) * CellSize);
	
	return Bound;
}

