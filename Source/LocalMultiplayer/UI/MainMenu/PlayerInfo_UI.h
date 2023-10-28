// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfo_UI.generated.h"

class UImage;
class UTextBlock;
class UBorder;
/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API UPlayerInfo_UI : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:

	UPROPERTY()
	APawn* PlayerCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info", meta = (BindWidget))
	UTextBlock* Join_NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info", meta = (BindWidget))
	UBorder* PlayerColor_Border;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info", meta = (BindWidget))
	UImage* Ready_Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info", meta = (BindWidget))
	UTextBlock* Ready_Text;
};
