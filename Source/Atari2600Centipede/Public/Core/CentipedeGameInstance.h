// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CentipedeGameInstance.generated.h"

/**
 * 
 */


UCLASS()
class ATARI2600CENTIPEDE_API UCentipedeGameInstance : public UGameInstance
{
	GENERATED_BODY()

	protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int Score;

	public:

	UFUNCTION(BlueprintCallable, Category = "Centipede")
	int GetScore() const {return Score;}

	
	UFUNCTION(BlueprintCallable, Category = "Centipede")
	void AddScore(int Amount);

	UFUNCTION(BlueprintCallable, Category = "Centipede")
	void SetScore(int _Score) {Score = _Score;}

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int8, NewScore);
	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;
};
