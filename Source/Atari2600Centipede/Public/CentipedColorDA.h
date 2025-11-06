// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CentipedColorDA.generated.h"

/**
 * 
 */
UCLASS()
class ATARI2600CENTIPEDE_API UCentipedColorDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor Color_R;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor Color_G;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor Color_B;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor Color_Bar;
};
