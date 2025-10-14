// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CentipedeGameInstance.h"
#include "Log/CentipedeLoggerCategories.h"
#include "Function/CentipedeColorFunctions.h"

UCentipedeGameInstance::UCentipedeGameInstance()
{
	T_Colors_ptr.Empty();
	T_Colors_ptr.Reserve(4);
	T_Colors_ptr = TArray<TSoftObjectPtr<UCentipedColorDA>> {
		TSoftObjectPtr<UCentipedColorDA>(FSoftObjectPath(TEXT("/Game/Art/ColorSets/Color_1.Color_1"))),
		TSoftObjectPtr<UCentipedColorDA>(FSoftObjectPath(TEXT("/Game/Art/ColorSets/Color_2.Color_2"))),
		TSoftObjectPtr<UCentipedColorDA>(FSoftObjectPath(TEXT("/Game/Art/ColorSets/Color_3.Color_3"))),
		TSoftObjectPtr<UCentipedColorDA>(FSoftObjectPath(TEXT("/Game/Art/ColorSets/Color_4.Color_4")))
	};

	UMaterialInterface* BaseMat = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Art/Materials/M_Sprites_Centipede.M_Sprites_Centipede"));

	UMaterialInstanceDynamic* PlayerMat = UMaterialInstanceDynamic::Create(BaseMat, this);
	AddMaterial(FName("Player"), PlayerMat);

	UMaterialInstanceDynamic* CentipedeMat = UMaterialInstanceDynamic::Create(BaseMat, this);
	AddMaterial(FName("Centipede"), CentipedeMat);
	
}

void UCentipedeGameInstance::AddScore(int Amount)
{
	Score += Amount;
	UE_LOG(LogCentipede, Log, TEXT("Gain Score : %d   |   New Score: %d"),Amount, Score);
	OnScoreChanged.Broadcast(Score);

	
}

void UCentipedeGameInstance::AddMaterial(FName Tag, UMaterialInstanceDynamic* Material)
{
	if (Material)
	{
		MaterialMap.Add(Tag, Material);
	}
}

void UCentipedeGameInstance::Add_Score_Implementation(int Amount)
{
	AddScore(Amount);
}

void UCentipedeGameInstance::NextLevel_Implementation()
{
	Level++;
}

UMaterialInstanceDynamic* UCentipedeGameInstance::GetMaterialByTag_Implementation(FName Tag)
{
	if (MaterialMap.Contains(Tag))
	{
		return MaterialMap[Tag];
	}
	return nullptr;
}
