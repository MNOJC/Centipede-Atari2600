// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CentipedeLogger.generated.h"

UENUM(BlueprintType)
enum class EBPLogVerbosity : uint8
{
    Log     UMETA(DisplayName="Log"),
    Warning UMETA(DisplayName="Warning"),
    Error   UMETA(DisplayName="Error")
};

UCLASS()
class ATARI2600CENTIPEDE_API UCentipedeLogger : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    /** Logs a message to a custom log category */
    UFUNCTION(BlueprintCallable, Category = "Logging", meta=(DisplayName = "CentipedeLogger", DevelopmentOnly))
    static void CentipedeLog(const FString& Message, EBPLogVerbosity Verbosity);
};
