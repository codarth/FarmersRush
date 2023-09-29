#pragma once

#include "CoreMinimal.h"
#include "GameModeInterface.generated.h"

class AInputReciever_FR;

UINTERFACE(Blueprintable)
class LOCALMULTIPLAYER_API UGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

class LOCALMULTIPLAYER_API IGameModeInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameModeInterface")
	void SpawnPlayerAtInputReceiver(int32 CurrentPlayerIndex, AInputReciever_FR* InputReceiver, int32 CharacterChoice);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameModeInterface")
	void DisplayCharacterCustomize(int32 CurrentPlayerIndex);
};