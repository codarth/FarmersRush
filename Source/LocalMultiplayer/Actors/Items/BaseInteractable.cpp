// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractable.h"
#include "ItemBase.h"
#include "LocalMultiplayer/Character/PlayerFarmerCharacter.h"
#include "LocalMultiplayer/UI/Interaction/InteractionWidget.h"


// Sets default values
ABaseInteractable::ABaseInteractable()
{
	PrimaryActorTick.bCanEverTick = false;

	// Setup the mesh component
	Interactable_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interactable_Mesh"));
	Interactable_Mesh->SetSimulatePhysics(true);
	RootComponent = Interactable_Mesh;
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();

	InitializeInteractable(UItemBase::StaticClass(), ItemQuantity);
}

void ABaseInteractable::InitializeInteractable(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{
	if (!ItemRowHandle.IsNull())
	{
		const FItemData* ItemData = ItemRowHandle.GetRow<FItemData>(ItemRowHandle.RowName.ToString());

		ItemReference = NewObject<UItemBase>(this, BaseClass);

		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->NumericData = ItemData->NumericData;
		ItemReference->TextData = ItemData->TextData;
		ItemReference->AssetData = ItemData->AssetData;

		ItemReference->NumericData.bIsStackable = ItemData->NumericData.MaxStackSize > 1;
		InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);

		Interactable_Mesh->SetStaticMesh(ItemData->AssetData.Mesh);

		UpdateInteractableData();
	}
}

void ABaseInteractable::Interact(APlayerFarmerCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		TakeInteractable(PlayerCharacter);
	}
}

void ABaseInteractable::UpdateInteractableData()
{
	InstanceInteractableData.InteractableType = EInteractableType::Pickup;
	InstanceInteractableData.Name = ItemReference->TextData.ItemName;
	InstanceInteractableData.Action = ItemReference->TextData.InteractionText;
	InstanceInteractableData.Quantity = ItemReference->Quantity;
	InteractableData = InstanceInteractableData;
}

void ABaseInteractable::TakeInteractable(const APlayerFarmerCharacter* Taker)
{
	if (!IsPendingKillPending())
	{
		if (ItemReference)
		{
			// Taker->HandleAddItem(ItemReference);
			Destroy();
		}
	}
}

void ABaseInteractable::BeginFocus()
{
	if (Interactable_Mesh)
	{
		// Hightlight the mesh
		Interactable_Mesh->SetRenderCustomDepth(true);
	}

	InteractionWidget->SetVisibility(ESlateVisibility::Visible);
}

void ABaseInteractable::EndFocus()
{
	if (Interactable_Mesh)
	{
		// Remove the highlight from the mesh
		Interactable_Mesh->SetRenderCustomDepth(false);
	}

	InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void ABaseInteractable::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangePropertyName = PropertyChangedEvent.Property
		                                 ? PropertyChangedEvent.Property->GetFName()
		                                 : NAME_None;

	if (ChangePropertyName == GET_MEMBER_NAME_CHECKED(FDataTableRowHandle, RowName))
	{
		const FItemData* ItemData = ItemRowHandle.GetRow<FItemData>(ItemRowHandle.RowName.ToString());
		Interactable_Mesh->SetStaticMesh(ItemData->AssetData.Mesh);
	}
}
