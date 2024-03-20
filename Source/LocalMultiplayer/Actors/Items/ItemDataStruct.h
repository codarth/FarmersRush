﻿#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStruct.generated.h"

UENUM()
enum class EItemQuality : uint8
{
	Shoddy UMETA(DisplayName = "Shoddy"),
	Common UMETA(DisplayName = "Common"),
	Quality UMETA(DisplayName = "Quality"),
	Exceptional UMETA(DisplayName = "Exceptional"),
	Masterwork UMETA(DisplayName = "Masterwork")
};

UENUM()
enum class EItemType : uint8
{
	Armor UMETA(DisplayName = "Armor"),
	Weapon UMETA(DisplayName = "Weapon"),
	Shield UMETA(DisplayName = "Shield"),
	Spell UMETA(DisplayName = "Spell"),
	Consumable UMETA(DisplayName = "Comsumable"),
	Quest UMETA(DisplayName = "Quest"),
	Mundane UMETA(DisplayName = "Mundane")	
};

USTRUCT()
struct FItemStatistics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float ArmorRating;
	UPROPERTY(EditAnywhere)
	float DamageValue;
	UPROPERTY(EditAnywhere)
	float RestorationAmount;
	UPROPERTY(EditAnywhere)
	float SellValue;
};

USTRUCT()
struct FItemTextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText ItemName;
	UPROPERTY(EditAnywhere)
	FText Description;
	UPROPERTY(EditAnywhere)
	FText InteractionText;
	UPROPERTY(EditAnywhere)
	FText UsageText;
};

USTRUCT()
struct FItemNumericData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Weight;
	UPROPERTY(EditAnywhere)
	int32 MaxStackSize;
	UPROPERTY(EditAnywhere)
	bool bIsStackable;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;
	// sound?
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ItemID;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemStatistics ItemStatistics;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData TextData;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData NumericData;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData AssetData;	
};
