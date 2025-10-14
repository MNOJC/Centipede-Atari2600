// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/CentipedePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"


ACentipedePlayerController::ACentipedePlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(TEXT("/Game/Input/IMC_Default.IMC_Default"));

	if (MappingContextFinder.Succeeded())
	{
		DefaultMappingContext = MappingContextFinder.Object;
	}
}

void ACentipedePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}
