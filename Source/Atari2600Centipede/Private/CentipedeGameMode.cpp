// Fill out your copyright notice in the Description page of Project Settings.

#include "CentipedeGameMode.h"

#include "CentipedeManager.h"
#include "MainCharacter.h"
#include "CentipedeHUD.h"
#include "CentipedeColorFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "CentipedeLoggerCategories.h"
#include "Materials/MaterialParameterCollection.h"


void ACentipedeGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnAndInitializeGrid();
	SpawnAndInitializeMushroomsManager();
	SpawnCentipedeManager();
	InitializeCentipedeCamera();
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
	
	AMainCharacter* PlayerPawn = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    PlayerPawn->SetGridBounds(SpawnedGrid->GetGridBounds());
}

void ACentipedeGameMode::SpawnCentipedeManager()
{
	if (!GetWorld()) return;

	UCentipedeManager* CptManager = GetWorld()->GetSubsystem<UCentipedeManager>();
	CptManager->SpawnCentipede(11, FVector(0.0f, SpawnedGrid->GetGridBounds().Max.Y, SpawnedGrid->GetGridBounds().Max.Z), EGridDirection::Right, TArray<FVector>(), TArray<FVector>());
	
}

void ACentipedeGameMode::SpawnAndInitializeMushroomsManager()
{
	
	if (!GetWorld()) return;
	
	SpawnedMushroomsManager = GetWorld()->GetSubsystem<UMushroomsManager>(); 
	
	SpawnedMushroomsManager->GenerateMushroomsOnGrid(GridPoints, 38, 42);
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
	
	//SpawnedCentipedeManager->SpawnCentipede(11, FVector(0.0f, SpawnedGrid->GetGridBounds().Max.Y, SpawnedGrid->GetGridBounds().Max.Z), EGridDirection::Right, TArray<FVector>(), TArray<FVector>());

	if (UCentipedeManager* CentipedeMgr = GetWorld()->GetSubsystem<UCentipedeManager>())
	{
		CentipedeMgr->SpawnCentipede(
			11,
			FVector(0.0f, SpawnedGrid->GetGridBounds().Max.Y, SpawnedGrid->GetGridBounds().Max.Z),
			EGridDirection::Right,
			TArray<FVector>(),
			TArray<FVector>()
		);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CentipedeManager subsystem is null in GameMode!"));
	}
	
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

void ACentipedeGameMode::InitializeCentipedeCamera()
{
	if (!GetWorld()) return;
	
		const FVector CenterLocation = SpawnedGrid->GetGridCenterLocation();

		const FVector CameraLocation(500.f, CenterLocation.Y, CenterLocation.Z - 200);   
		const FRotator CameraRotation(0.f, 180.f, 0.f);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		CentipedeCameraActor = GetWorld()->SpawnActor<ACentipedeCamera>(ACentipedeCamera::StaticClass(), CameraLocation, CameraRotation, SpawnParams);


	if (CentipedeCameraActor)
	{
		if (APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0)))
		{
			PC->SetViewTarget(CentipedeCameraActor);
		}
	}
}