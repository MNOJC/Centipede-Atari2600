// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/CentipedColorDA.h"
#include "Engine/GameInstance.h"
#include "Interface/ScoreInterface.h"
#include "CentipedeGameInstance.generated.h"

/**
 * 
 */


UCLASS()
class ATARI2600CENTIPEDE_API UCentipedeGameInstance : public UGameInstance, public IScoreInterface
{
	GENERATED_BODY()

	protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int Score;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Colors")
	TArray<UCentipedColorDA*> Colors;
	
	public:

	UCentipedeGameInstance();
	
	UFUNCTION(BlueprintCallable, Category = "Centipede")
	int GetScore() const {return Score;}

	
	UFUNCTION(BlueprintCallable, Category = "Centipede")
	void AddScore(int Amount);

	UFUNCTION(BlueprintCallable, Category = "Centipede")
	void SetScore(int _Score) {Score = _Score;}

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, NewScore);
	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;

	virtual void Add_Score_Implementation(int Amount) override;

	virtual void NextLevel_Implementation();
	
};
