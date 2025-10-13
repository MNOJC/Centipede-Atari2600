// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CentipedeHUD.h"
#include "Log/CentipedeLoggerCategories.h"

void ACentipedeHUD::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = GetOwningPlayerController();
	if (!PlayerController)
	{
		UE_LOG(LogCentipede,Warning,TEXT("PlayerController is null, can't create HUD"));
	}
	UUserWidget* PlayerHUD = CreateWidget<UUserWidget>(PlayerController, CentipedePlayerHUD);

	if (PlayerHUD)
	{
		PlayerHUD->AddToViewport();
		return;
	}
	
	UE_LOG(LogCentipede,Error,TEXT("Can't CreateWidget | unknown"));
}
