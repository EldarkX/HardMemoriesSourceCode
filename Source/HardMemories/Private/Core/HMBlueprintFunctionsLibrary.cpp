// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HMBlueprintFunctionsLibrary.h"

#include "Core/HardMemoriesGameMode.h"
#include "Core/Systems/ItemSpawnSystem.h"
#include "Core/HelpData/ItemsHelpData.h"
#include <Misc/MessageDialog.h>
#include <Kismet/KismetSystemLibrary.h>
#include "Player/HardMemoriesPlayerController.h"

void UHMBlueprintFunctionsLibrary::ExitWithErrorWindow(AActor* Context, const FString& ErrorText)
{
	AHardMemoriesPlayerController* PC = GetPlayerController(Context);
	if (!PC->IsErrorTriggered)
	{
		PC->IsErrorTriggered = true;

		FMessageDialog MessageDialog;

		FText WindowTitle = FText::FromString("Error");
		FText ErrorMessage = FText::FromString(ErrorText);

		MessageDialog.Open(EAppMsgType::Ok, ErrorMessage, &WindowTitle);

		UE_LOG(LogTemp, Error, TEXT("Game quit with the error: %s"), *ErrorText);

		UKismetSystemLibrary::QuitGame(Context->GetWorld(), Context->GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
	}
}

class AHardMemoriesPlayerController* UHMBlueprintFunctionsLibrary::GetPlayerController(AActor* Context)
{
	AHardMemoriesPlayerController* PC = Cast<AHardMemoriesPlayerController>(Context->GetWorld()->GetFirstPlayerController());

	return PC;
}

UDataTable* UHMBlueprintFunctionsLibrary::GetItemsDataTable(AActor* Context)
{
	if (Context && Context->GetWorld() && Context->GetWorld()->GetAuthGameMode())
	{
		AHardMemoriesGameMode* GM = Cast<AHardMemoriesGameMode>(Context->GetWorld()->GetAuthGameMode());
		if (GM)
		{
			if (GM->ItemSpawnSystem)
			{
				return GM->ItemSpawnSystem->ItemsDataTable;
			}
		}
	}
	return nullptr;
}

FLinearColor UHMBlueprintFunctionsLibrary::GetColorByRarity(AActor *Context, EItemRarity Rarity)
{
	if (Context && Context->GetWorld() && Context->GetWorld()->GetAuthGameMode())
	{
		AHardMemoriesGameMode* GM = Cast<AHardMemoriesGameMode>(Context->GetWorld()->GetAuthGameMode());
		if (GM)
		{
			return *GM->DA_ItemsHelpData->ColorByRarity.Find(Rarity);
		}
	}
	return FLinearColor::White;
}

UClass* UHMBlueprintFunctionsLibrary::GetBaseItemWidgetClass(AActor* Context)
{
	return (GetItemWidgetClass(Context));
}

UClass* UHMBlueprintFunctionsLibrary::GetBasePluralItemWidgetClass(AActor* Context)
{
	return (GetItemWidgetClass(Context, true));
}

EInventorySlotType UHMBlueprintFunctionsLibrary::GetInventorySlotTypeByItemType(AActor* Context, EItemType ItemType)
{
	if (Context && Context->GetWorld() && Context->GetWorld()->GetAuthGameMode())
	{
		AHardMemoriesGameMode* GM = Cast<AHardMemoriesGameMode>(Context->GetWorld()->GetAuthGameMode());
		if (GM)
		{
			return *GM->DA_ItemsHelpData->InventorySlotTypeByItemType.Find(ItemType);
		}
	}
	return EInventorySlotType::ISTE_OneToOne;
}

bool UHMBlueprintFunctionsLibrary::GetIsWeaponType(AActor* Context, EItemType ItemType)
{
	switch (ItemType)
	{
	case EItemType::ITE_Axe:
	case EItemType::ITE_Bow:
	case EItemType::ITE_Hummer:
	case EItemType::ITE_Knife:
	case EItemType::ITE_Spear:
	case EItemType::ITE_Staff:
	case EItemType::ITE_Sword:
		return true;
	}
	return false;
}

FVector2D UHMBlueprintFunctionsLibrary::GetRowsAndColsByInventorySlotType(AActor* Context, EInventorySlotType InventorySlotType)
{
	if (Context && Context->GetWorld() && Context->GetWorld()->GetAuthGameMode())
	{
		AHardMemoriesGameMode* GM = Cast<AHardMemoriesGameMode>(Context->GetWorld()->GetAuthGameMode());
		if (GM)
		{
			return *GM->DA_ItemsHelpData->RowsAndColsByInventorySlotType.Find(InventorySlotType);
		}
	}
	return FVector2D(1, 1);
}

FVector2D UHMBlueprintFunctionsLibrary::GetRowsAndColsByItemType(AActor* Context, EItemType ItemType)
{
	if (Context && Context->GetWorld() && Context->GetWorld()->GetAuthGameMode())
	{
		AHardMemoriesGameMode* GM = Cast<AHardMemoriesGameMode>(Context->GetWorld()->GetAuthGameMode());
		if (GM)
		{
			return *GM->DA_ItemsHelpData->RowsAndColsByInventorySlotType.Find(*GM->DA_ItemsHelpData->InventorySlotTypeByItemType.Find(ItemType));
		}
	}
	return FVector2D(1, 1);
}

UTexture2D* UHMBlueprintFunctionsLibrary::GetInventorySlotBGTextureByType(AActor* Context, EInventorySlotType InventorySlotType)
{
	if (Context && Context->GetWorld() && Context->GetWorld()->GetAuthGameMode())
	{
		AHardMemoriesGameMode* GM = Cast<AHardMemoriesGameMode>(Context->GetWorld()->GetAuthGameMode());
		if (GM)
		{
			return *GM->DA_ItemsHelpData->InventorySlotBGTextureByType.Find(InventorySlotType);
		}
	}
	return nullptr;
}

UTexture2D* UHMBlueprintFunctionsLibrary::GetInventoryEquipSloyBGByType(AActor* Context, EItemType ItemType)
{
	if (Context && Context->GetWorld() && Context->GetWorld()->GetAuthGameMode())
	{
		AHardMemoriesGameMode* GM = Cast<AHardMemoriesGameMode>(Context->GetWorld()->GetAuthGameMode());
		if (GM)
		{
			return *GM->DA_ItemsHelpData->InventoryEquipSloyBGByType.Find(ItemType);
		}
	}
	return nullptr;
}

UTexture2D* UHMBlueprintFunctionsLibrary::GetInventoryEquipSloyEmptyIconByType(AActor* Context, EItemType ItemType)
{
	if (Context && Context->GetWorld() && Context->GetWorld()->GetAuthGameMode())
	{
		AHardMemoriesGameMode* GM = Cast<AHardMemoriesGameMode>(Context->GetWorld()->GetAuthGameMode());
		if (GM)
		{
			return *GM->DA_ItemsHelpData->InventoryEquipSloyEmptyIconByType.Find(ItemType);
		}
	}
	return nullptr;
}

UClass* UHMBlueprintFunctionsLibrary::GetItemWidgetClass(AActor* Context, bool IsPlural)
{
	if (Context && Context->GetWorld() && Context->GetWorld()->GetAuthGameMode())
	{
		AHardMemoriesGameMode* GM = Cast<AHardMemoriesGameMode>(Context->GetWorld()->GetAuthGameMode());
		if (GM)
		{
			return IsPlural ? GM->DA_ItemsHelpData->ItemWidgetBasePluralClass.Get() : GM->DA_ItemsHelpData->ItemWidgetBaseClass.Get();
		}
	}
	return UItemWidget::StaticClass();
}
