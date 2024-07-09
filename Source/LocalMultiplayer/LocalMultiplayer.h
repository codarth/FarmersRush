// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Custom log category
DECLARE_LOG_CATEGORY_EXTERN(LocalMultiplayer, Log, All);

// Custom log macros
#define LOG(x, ...) UE_LOG(LocalMultiplayer, Log, TEXT(x), ##__VA_ARGS__)
#define LOG_WARNING(x, ...) UE_LOG(LocalMultiplayer, Warning, TEXT(x), ##__VA_ARGS__)
#define LOG_ERROR(x, ...) UE_LOG(LocalMultiplayer, Error, TEXT(x), ##__VA_ARGS__)


