// Fill out your copyright notice in the Description page of Project Settings.


#include "CentipedeGameInstance.h"
#include "CentipedeLoggerCategories.h"

void UCentipedeGameInstance::AddScore(int Amount)
{
	Score += Amount;
	UE_LOG(LogCentipede, Log, TEXT("Gain Score : %d   |   New Score: %d"),Amount, Score);
}
