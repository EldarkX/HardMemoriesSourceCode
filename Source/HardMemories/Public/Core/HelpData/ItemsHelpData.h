// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../DataTypes.h"
#include "ItemsHelpData.generated.h"

/**
 * 
 */
UCLASS()
class HARDMEMORIES_API UItemsHelpData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UItemsHelpData();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UItemWidget> ItemWidgetBaseClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UItemWidget> ItemWidgetBasePluralClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EItemRarity, FLinearColor> ColorByRarity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EItemType, EInventorySlotType> InventorySlotTypeByItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EItemType, class UTexture2D *> InventoryEquipSloyBGByType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EItemType, class UTexture2D*> InventoryEquipSloyEmptyIconByType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EInventorySlotType, FVector2D> RowsAndColsByInventorySlotType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EInventorySlotType, class UTexture2D *> InventorySlotBGTextureByType;

};
