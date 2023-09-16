// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HelpData/ItemsHelpData.h"

UItemsHelpData::UItemsHelpData()
{
	InventorySlotTypeByItemType.Add(EItemType::ITE_Armor,	EInventorySlotType::ISTE_ThreeToTwo);
	InventorySlotTypeByItemType.Add(EItemType::ITE_Axe,		EInventorySlotType::ISTE_ThreeToTwo);
	InventorySlotTypeByItemType.Add(EItemType::ITE_Boots,	EInventorySlotType::ISTE_TwoToTwo);
	InventorySlotTypeByItemType.Add(EItemType::ITE_Bow,		EInventorySlotType::ISTE_ThreeToOne);
	InventorySlotTypeByItemType.Add(EItemType::ITE_Bracers, EInventorySlotType::ISTE_TwoToTwo);
	InventorySlotTypeByItemType.Add(EItemType::ITE_Helm,	EInventorySlotType::ISTE_TwoToTwo);
	InventorySlotTypeByItemType.Add(EItemType::ITE_Hummer,	EInventorySlotType::ISTE_FourToTwo);
	InventorySlotTypeByItemType.Add(EItemType::ITE_Knife,	EInventorySlotType::ISTE_TwoToOne);
	InventorySlotTypeByItemType.Add(EItemType::ITE_Leggings,EInventorySlotType::ISTE_ThreeToTwo);
	InventorySlotTypeByItemType.Add(EItemType::ITE_Spear,	EInventorySlotType::ISTE_FiveToOne);
	InventorySlotTypeByItemType.Add(EItemType::ITE_Staff,	EInventorySlotType::ISTE_FiveToTwo);
	InventorySlotTypeByItemType.Add(EItemType::ITE_Sword,	EInventorySlotType::ISTE_ThreeToOne);

	RowsAndColsByInventorySlotType.Add(EInventorySlotType::ISTE_FiveToOne, FVector2D(5, 1));
	RowsAndColsByInventorySlotType.Add(EInventorySlotType::ISTE_FiveToTwo, FVector2D(5, 2));
	RowsAndColsByInventorySlotType.Add(EInventorySlotType::ISTE_FourToTwo, FVector2D(4, 2));
	RowsAndColsByInventorySlotType.Add(EInventorySlotType::ISTE_OneToOne,  FVector2D(1, 1));
	RowsAndColsByInventorySlotType.Add(EInventorySlotType::ISTE_ThreeToOne, FVector2D(3, 1));
	RowsAndColsByInventorySlotType.Add(EInventorySlotType::ISTE_ThreeToTwo, FVector2D(3, 2));
	RowsAndColsByInventorySlotType.Add(EInventorySlotType::ISTE_TwoToOne, FVector2D(2, 1));
	RowsAndColsByInventorySlotType.Add(EInventorySlotType::ISTE_TwoToTwo, FVector2D(2, 2));

	InventorySlotBGTextureByType.Add(EInventorySlotType::ISTE_FiveToOne, nullptr);
	InventorySlotBGTextureByType.Add(EInventorySlotType::ISTE_FiveToTwo, nullptr);
	InventorySlotBGTextureByType.Add(EInventorySlotType::ISTE_FourToTwo, nullptr);
	InventorySlotBGTextureByType.Add(EInventorySlotType::ISTE_OneToOne, nullptr);
	InventorySlotBGTextureByType.Add(EInventorySlotType::ISTE_ThreeToOne, nullptr);
	InventorySlotBGTextureByType.Add(EInventorySlotType::ISTE_ThreeToTwo, nullptr);
	InventorySlotBGTextureByType.Add(EInventorySlotType::ISTE_TwoToOne, nullptr);
	InventorySlotBGTextureByType.Add(EInventorySlotType::ISTE_TwoToTwo, nullptr);

	InventoryEquipSloyBGByType.Add(EItemType::ITE_Armor, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Axe, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Boots, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Bow, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Bracers, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Helm, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Hummer, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Knife, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Leggings, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Spear, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Staff, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Sword, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Ring, nullptr);
	InventoryEquipSloyBGByType.Add(EItemType::ITE_Amulet, nullptr);
	
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Armor, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Axe, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Boots, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Bow, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Bracers, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Helm, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Hummer, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Knife, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Leggings, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Spear, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Staff, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Sword, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Ring, nullptr);
	InventoryEquipSloyEmptyIconByType.Add(EItemType::ITE_Amulet, nullptr);
}
