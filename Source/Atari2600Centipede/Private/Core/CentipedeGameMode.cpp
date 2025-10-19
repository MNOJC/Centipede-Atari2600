// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/CentipedeGameMode.h"

#include "Centipede/CentipedeManager.h"
#include "MainCharacter/MainCharacter.h"
#include "Core/CentipedeHUD.h"
#include "Function/CentipedeColorFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "Log/CentipedeLoggerCategories.h"
#include "Materials/MaterialParameterCollection.h"


void ACentipedeGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnAndInitializeGrid();
	SpawnAndInitializeMushroomsManager();
	SpawnCentipedeManager();
}

ACentipedeGameMode::ACentipedeGameMode()
{
	PlayerControllerClass = ACentipedePlayerController::StaticClass();
	DefaultPawnClass = AMainCharacter::StaticClass();
	HUDClass = ACentipedeHUD::StaticClass();

	
	T_Colors_ptr.Empty();
	T_Colors_ptr.Reserve(4);
	T_Colors_ptr = TArray<TSoftObjectPtr<UCentipedColorDA>> {
		TSoftObjectPtr<UCentipedColorDA>(FSoftObjectPath(TEXT("/Game/Art/ColorSets/Color_1.Color_1"))),
		TSoftObjectPtr<UCentipedColorDA>(FSoftObjectPath(TEXT("/Game/Art/ColorSets/Color_2.Color_2"))),
		TSoftObjectPtr<UCentipedColorDA>(FSoftObjectPath(TEXT("/Game/Art/ColorSets/Color_3.Color_3"))),
		TSoftObjectPtr<UCentipedColorDA>(FSoftObjectPath(TEXT("/Game/Art/ColorSets/Color_4.Color_4")))
	};

	UMaterialInterface* BaseMat = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Art/Materials/M_Sprites_Centipede.M_Sprites_Centipede"));

	PlayerMat = UMaterialInstanceDynamic::Create(BaseMat, this);
	AddMaterial(FName("Player"), PlayerMat);

	CentipedeMat = UMaterialInstanceDynamic::Create(BaseMat, this);
	AddMaterial(FName("Centipede"), CentipedeMat);

	
}

void ACentipedeGameMode::SpawnAndInitializeGrid()
{
	if (!GetWorld()) return;

	const FVector SpawnLocation(0.f, 0.f, 0.f);
	const FRotator SpawnRotation(0.f, 0.f, 0.f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	SpawnedGrid = GetWorld()->SpawnActor<ACentipedeGridGenerator>(ACentipedeGridGenerator::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	GridPoints = SpawnedGrid->GenerateGrid();
	
}

void ACentipedeGameMode::SpawnCentipedeManager()
{
	if (!GetWorld()) return;

	const FVector SpawnLocation(0.f,0.f, 0.f);
	const FRotator SpawnRotation(0.f, 0.f, 0.f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	SpawnedCentipedeManager = GetWorld()->SpawnActor<ACentipedeManager>(SpawnLocation, SpawnRotation, SpawnParams);
	
}

void ACentipedeGameMode::SpawnAndInitializeMushroomsManager()
{
	
	if (!GetWorld()) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FVector SpawnLocation = FVector::ZeroVector;      
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	SpawnedMushroomsManager = GetWorld()->SpawnActor<AMushroomsManager>(
		AMushroomsManager::StaticClass(),
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	SpawnedMushroomsManager->GenerateMushroomsOnGrid(GridPoints, 25, 30);
}


void ACentipedeGameMode::AddScore(int Amount)
{
	Score += Amount;
	UE_LOG(LogCentipede, Log, TEXT("Gain Score : %d   |   New Score: %d"),Amount, Score);
	Cast<ACentipedeHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD())->AddScore(Amount);
}

void ACentipedeGameMode::AddMaterial(FName Tag, UMaterialInstanceDynamic* Material)
{
	if (Material)
	{
		MaterialMap.Add(Tag, Material);
	}
}
void ACentipedeGameMode::NextLevel()
{
	Level++;

	if (!MPCi)
		MPCi =  GetWorld()->GetParameterCollectionInstance(LoadObject<UMaterialParameterCollection>(nullptr,TEXT("/Game/Art/MPC_Colors.MPC_Colors")));

	ColorHelper::ApplyCentipedeColorTarget(T_Colors_ptr[(Level+1)%(T_Colors_ptr.Num())], PlayerMat);
	ColorHelper::ApplyCentipedeColorTarget(T_Colors_ptr[(Level+1)%(T_Colors_ptr.Num())], PlayerMat);
	ColorHelper::ApplyCentipedeColorMob(T_Colors_ptr[Level % (T_Colors_ptr.Num())], MPCi);
}

UMaterialInstanceDynamic* ACentipedeGameMode::GetMaterialByTag(FName Tag)
{
	if (MaterialMap.Contains(Tag))
	{
		return MaterialMap[Tag];
	}
	return nullptr;
}

void ACentipedeGameMode::SkipLevel()
{
	UE_LOG(LogCentipede, Log, TEXT("Skip Level: %d"), Level);
	NextLevel();
}
