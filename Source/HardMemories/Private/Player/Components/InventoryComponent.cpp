// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Components/InventoryComponent.h"
#include "Items/BaseItem.h"
#include "Core/HMBlueprintFunctionsLibrary.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ItemSlotsAmount = RowsAmount * ColsAmount;

	for (int32 SlotIndex = 0; SlotIndex < ItemSlotsAmount; ++SlotIndex)
	{
		FreeIndexes.Add(SlotIndex);
	}
}

void UInventoryComponent::AddItem(ABaseItem* Item, int32 Amount)
{
	if (Item->ItemInfo.ItemName == "None" || !Item->ItemInfo.ItemClass->IsValidLowLevel() || !Item->ItemInfo.ItemIcon)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryComponent: Can't pick up item. Bad item information."));
	}
	else //Item adding
	{
		FVector2D RowsAndCols = UHMBlueprintFunctionsLibrary::GetRowsAndColsByItemType(GetOwner(), Item->ItemInfo.ItemType);
		const int32 Index = GetFreeFitItemSlot(RowsAndCols.X, RowsAndCols.Y);
		if (Index == -1)
		{
			UE_LOG(LogTemp, Error, TEXT("There isn't any free slots in inventory"));
		}
		else
		{
			for (int32 Row = 0; Row < RowsAndCols.X; ++Row)
			{
				for (int32 Col = 0; Col < RowsAndCols.Y; ++Col)
				{
					FreeIndexes.Remove(Index + Row * ColsAmount + Col);
				}
			}
			Item->SetActorEnableCollision(false);
			Item->SetActorHiddenInGame(true);
			OnItemAdded.Broadcast(Item, Index);
		}
	}
}

int32 UInventoryComponent::GetFreeFitItemSlot(int32 Rows, int32 Cols) const
{
	bool IsSuit;
	for (int32 Index : FreeIndexes)
	{
		IsSuit = true;
		for (int32 Row = 0; Row < Rows && IsSuit; ++Row)
		{
			for (int32 Col = 0; Col < Cols && IsSuit; ++Col)
			{
				IsSuit = FreeIndexes.Contains(Index + Row * ColsAmount + Col);
			}
		}
		if (IsSuit)
			return Index;
	}
	return -1;
}

void UInventoryComponent::RemoveItem(ABaseItem* Item)
{
	//OnItemRemoved.Broadcast(Item);
}

void UInventoryComponent::RemoveItemByIndex(int32 SlotIndex)
{
}

void UInventoryComponent::EquipItem(class ABaseItem* Item, int32 SlotIndex)
{
	OnEquipItem.Broadcast(Item);
}

void UInventoryComponent::UnequipItem(class ABaseItem* Item, int32 SlotIndex)
{
	OnUnequipItem.Broadcast(Item);
}


