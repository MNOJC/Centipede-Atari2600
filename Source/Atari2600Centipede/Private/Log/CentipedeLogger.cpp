// Fill out your copyright notice in the Description page of Project Settings.


#include "Log/CentipedeLogger.h"
#include "Log/CentipedeLoggerCategories.h"

void UCentipedeLogger::CentipedeLog(const FString& Message, EBPLogVerbosity Verbosity)
{
	switch (Verbosity)
	{
	case EBPLogVerbosity::Warning:
		UE_LOG(LogCentipede, Warning, TEXT("%s"), *Message);
		break;

	case EBPLogVerbosity::Error:
		UE_LOG(LogCentipede, Error, TEXT("%s"), *Message);
		break;

	default:
		UE_LOG(LogCentipede, Log, TEXT("%s"), *Message);
		break;
	}
}

