// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CentipedeHUD.h"
#include "Blueprint/UserWidget.h"
#include "Core/CentipedeGameMode.h"
#include "Engine/Canvas.h"
#include "UObject/ConstructorHelpers.h"
#include "Log/CentipedeLoggerCategories.h"

void ACentipedeHUD::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = GetOwningPlayerController();
	
	Font = LoadObject<UFont>(nullptr, TEXT("/Game/Art/Font/PressStart2P_Font.PressStart2P_Font"));

}

void ACentipedeHUD::DrawHUD()
{
	Super::DrawHUD();
	
	const float ScreenX = Canvas->SizeX;
	const float ScreenY = Canvas->SizeY;
	
	DrawLine(0,ScreenY-100,ScreenX,ScreenY-100, FColor::Cyan, 5);
	FString ScoreText = FString::Printf(TEXT("%d"), PlayerScore);
	DrawText(ScoreText, FLinearColor::Yellow, ScreenX -200, ScreenY - 50,Font,1);
}

void ACentipedeHUD::SetScore(int32 NewScore)
{
	PlayerScore = NewScore;
}

void ACentipedeHUD::AddScore(int32 NewScore)
{
	PlayerScore += NewScore;
}
