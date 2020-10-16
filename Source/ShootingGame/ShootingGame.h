// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "SGType.h"

DECLARE_LOG_CATEGORY_EXTERN(ShootingGame, Log, All);
#define SGLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define SGLOG(Verbosity, Format, ...) UE_LOG(ShootingGame, Verbosity, TEXT("%s %s"), *SGLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define SGCHECK(Ptr) {if(Ptr == nullptr) {SGLOG(Error, TEXT("ASSERTION : %s"), TEXT(""#Ptr"")); return;}}
