// Copyright Epic Games, Inc. All Rights Reserved.

#include "LocalMultiplayer.h"
#include "Modules/ModuleManager.h"

/**
* Custom log category.
* DECLARE_LOG_CATEGORY_EXTERN() in .h file.
* DEFINE_LOG_CATEGORY() in .cpp file.
*/
DEFINE_LOG_CATEGORY(LocalMultiplayer);

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, LocalMultiplayer, "LocalMultiplayer" );
 