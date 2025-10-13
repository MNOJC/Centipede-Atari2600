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
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Interface")
	TSubclassOf<UUserWidget> CentipedePlayerHUD;
	
};
