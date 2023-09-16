// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Core/DataTypes.h"
#include "DA_BaseItem.generated.h"

UCLASS()
class HARDMEMORIES_API UDA_BaseItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UDA_BaseItem() {}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Info)
	FPrimaryAssetType ItemType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	FText ItemName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	UTexture2D *ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info)
	EItemRarity Rarity;
	
};
