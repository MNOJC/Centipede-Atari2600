// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CentipedeHUD.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Log/CentipedeLoggerCategories.h"

void ACentipedeHUD::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = GetOwningPlayerController();
	
	TSubclassOf<UUserWidget> LoadedHUDClass = LoadClass<UUserWidget>(
		nullptr,
		TEXT("/Game/Core/HUD/WBP_Centipede_HUD.WBP_Centipede_HUD_C")
	);
	
	if (!PlayerController)
	{
		UE_LOG(LogCentipede,Warning,TEXT("PlayerController is null, can't create HUD"));
	}
	UUserWidget* PlayerHUD = CreateWidget<UUserWidget>(PlayerController, LoadedHUDClass);

	if (PlayerHUD)
	{
		PlayerHUD->AddToViewport();
		return;
	}
	
	UE_LOG(LogCentipede,Error,TEXT("Can't CreateWidget | unknown"));
}
