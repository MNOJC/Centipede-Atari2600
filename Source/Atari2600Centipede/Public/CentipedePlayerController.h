// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CentipedePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ATARI2600CENTIPEDE_API ACentipedePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	ACentipedePlayerController();

protected:
	
	virtual void SetupInputComponent() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;
};
