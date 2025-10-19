// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "CentipedeHUD.generated.h"

/**
 * 
 */
UCLASS()
class ATARI2600CENTIPEDE_API ACentipedeHUD : public AHUD
{
	GENERATED_BODY()

	protected:
	UFont* Font = nullptr;
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	
public:
	// Function to update the score
	void SetScore(int32 NewScore);
	
	void AddScore(int32 NewScore);
	
private:
	int32 PlayerScore = 0; // current score value
	
};
