// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Items/DA_BaseItem.h"
#include "Items/Components/ItemWidget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HMBlueprintFunctionsLibrary.generated.h"

UCLASS()
class HARDMEMORIES_API UHMBlueprintFunctionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static void ExitWithErrorWindow(AActor* Context, const FString& ErrorText);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static class AHardMemoriesPlayerController* GetPlayerController(AActor* Context);

	UFUNCTION(BlueprintCallable, BlueprintPure)
    static class UDataTable *GetItemsDataTable(AActor *Context);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FLinearColor GetColorByRarity(AActor *Context, EItemRarity Rarity);

	UFUNCTION(BlueprintCallable, BlueprintPure)
    static UClass* GetBaseItemWidgetClass(AActor *Context);

	UFUNCTION(BlueprintCallable, BlueprintPure)
    static UClass* GetBasePluralItemWidgetClass(AActor *Context);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static EInventorySlotType GetInventorySlotTypeByItemType(AActor* Context, EItemType ItemType);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetIsWeaponType(AActor* Context, EItemType ItemType);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector2D GetRowsAndColsByInventorySlotType(AActor* Context, EInventorySlotType InventorySlotType);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector2D GetRowsAndColsByItemType(AActor* Context, EItemType ItemType);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UTexture2D* GetInventorySlotBGTextureByType(AActor* Context, EInventorySlotType InventorySlotType);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UTexture2D* GetInventoryEquipSloyBGByType(AActor* Context, EItemType ItemType);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UTexture2D* GetInventoryEquipSloyEmptyIconByType(AActor* Context, EItemType ItemType);

private:
	
	static UClass *GetItemWidgetClass(AActor *Context, bool IsPlural = false);

};
