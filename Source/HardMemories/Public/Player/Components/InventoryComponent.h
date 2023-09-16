// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, class ABaseItem *, Item, int32, SlotIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, int32, SlotIndex);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipItem, class ABaseItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnequipItem, class ABaseItem*, Item);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HARDMEMORIES_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	void AddItem(class ABaseItem *Item, int32 Amount);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetFreeFitItemSlot(int32 Rows, int32 Cols) const;
	
	UFUNCTION(BlueprintCallable)
	void RemoveItem(class ABaseItem *Item);
	
	UFUNCTION(BlueprintCallable)
	void RemoveItemByIndex(int32 SlotIndex);

	UFUNCTION(BlueprintCallable)
	void EquipItem(class ABaseItem* Item, int32 SlotIndex);

	UFUNCTION(BlueprintCallable)
	void UnequipItem(class ABaseItem* Item, int32 SlotIndex);

	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable)
	FOnItemRemoved OnItemRemoved;

	UPROPERTY(BlueprintAssignable)
	FOnEquipItem OnEquipItem;

	UPROPERTY(BlueprintAssignable)
	FOnUnequipItem OnUnequipItem;
	
protected:

	virtual void BeginPlay();

private:

	TArray<int32> FreeIndexes;

	UPROPERTY(BlueprintReadOnly, meta = (allowPrivateAccess = "true"))
	int32 ItemSlotsAmount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (allowPrivateAccess = "true"))
	int32 ColsAmount = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (allowPrivateAccess = "true"))
	int32 RowsAmount = 5;
};
