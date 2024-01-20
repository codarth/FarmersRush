// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Countdown_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCountdown_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOCALMULTIPLAYER_API ICountdown_Interface
{
	GENERATED_BODY()

public:

	/** Exit countdown */
	virtual void BeginQuitCountdown();
	virtual void UpdateQuitTimer();
	virtual void StopQuitCountdown();
};
