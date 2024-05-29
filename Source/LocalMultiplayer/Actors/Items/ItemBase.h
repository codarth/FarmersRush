// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataStruct.h"
#include "ItemBase.generated.h"

class APlayerFarmerCharacter;
/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API UItemBase : public UObject
{
	GENERATED_BODY()

public:

	UItemBase();

	// Unique ID for this item
	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	FName ID;

	// Quantity of this item in the stack
	UPROPERTY(VisibleAnywhere, Category = "Item Data", meta = (UIMin = 1, UIMax = 100))
	int32 Quantity;

	// Type Information for this item (Tool, Crop, Throwable, etc.)
	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;

	// Text information for this item (Name, Description, etc.)
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData TextData;

	// Numeric information for this item (MaxStackSize, Stackable, SellValue, etc.)
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData NumericData;

	// Asset information for this item (Icon, Mesh, etc.)
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData AssetData;	

	// Flags for this item
	// Is this item a copy of another item?
	bool bIsCopy;
	// Is this item a pickup?
	bool bIsPickup;

	// Reset the flags for this item
	void ResetItemFlags();
	
	// Create a copy of this item
	UFUNCTION(Category = "Item")
	UItemBase* CreateItemCopy() const;

	// Get whether the current quantity is at the max stack size
	FORCEINLINE bool IsFullItemStack() const { return Quantity == NumericData.MaxStackSize; }

	// Get the quantity of this item
	UFUNCTION(Category = "Item")
	void SetQuantity(int32 NewQuantity);

protected:

	// Overloaded comparison operator for this item
	bool operator==(const FName& OtherID) const { return ID == OtherID; } 
};
