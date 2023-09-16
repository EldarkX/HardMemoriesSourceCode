// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BasePluralItem.h"

#include "Core/HMBlueprintFunctionsLibrary.h"

UClass* ABasePluralItem::GetItemWidgetClass()
{
	return UHMBlueprintFunctionsLibrary::GetBasePluralItemWidgetClass(this);
}
