// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CentipedeGameInstance.h"
#include "Log/CentipedeLoggerCategories.h"

void UCentipedeGameInstance::AddScore(int Amount)
{
	Score += Amount;
	UE_LOG(LogCentipede, Log, TEXT("Gain Score : %d   |   New Score: %d"),Amount, Score);
	OnScoreChanged.Broadcast(Score);
}

void UCentipedeGameInstance::Add_Score_Implementation(int Amount)
{
	AddScore(Amount);
}
