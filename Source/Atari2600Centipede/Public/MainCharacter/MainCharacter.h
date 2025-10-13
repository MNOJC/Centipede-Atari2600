// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "InputActionValue.h"
#include "Camera/CentipedeCamera.h"
#include "Core/CentipedePlayerController.h"
#include "PaperSpriteComponent.h"
#include "MainCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UPaperSpriteComponent;
class ACentipedeCamera;

UCLASS()
class ATARI2600CENTIPEDE_API AMainCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// Camera
	UPROPERTY()
	ACentipedeCamera* CentipedeCameraActor;

	// Pawn Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UFloatingPawnMovement* MovementComponent;


	//Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* IA_Movement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* IA_Shoot;


	void Move(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);

	void InitializeCentipedeCamera();
};
