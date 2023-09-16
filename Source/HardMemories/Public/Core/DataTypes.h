// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include <AttributeSet.h>

#include "DataTypes.generated.h"

UENUM(BlueprintType)
enum class EFightNotificationType : uint8
{
	FNTE_Miss		UMETA(DisplayName = "Miss"),
	FNTE_Crit		UMETA(DisplayName = "Crit"),
	FNTE_Letality	UMETA(DisplayName = "Letality")
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	IRE_Gold		UMETA(DisplayName="Gold"),
    IRE_Health		UMETA(DisplayName="Health"),
    IRE_Mana		UMETA(DisplayName="Mana"),
    IRE_Quest		UMETA(DisplayName="Quest"),
    IRE_Garbage		UMETA(DisplayName="Garbage"),
    IRE_Common		UMETA(DisplayName="Common"),
    IRE_Rare		UMETA(DisplayName="Rare"),
    IRE_Epic		UMETA(DisplayName="Epic"),
    IRE_Legendary	UMETA(DisplayName="Legendary"),
    IRE_Heavenly	UMETA(DisplayName="Heavenly")
};

UENUM(BlueprintType)
enum class EProbabilityType : uint8
{
	PTE_Tiny		UMETA(DisplayName="Tiny"),
	PTE_Small		UMETA(DisplayName="Small"),
    PTE_Medium		UMETA(DisplayName="Mana"),
	PTE_Big			UMETA(DisplayName="Big"),
    PTE_Huge		UMETA(DisplayName="Huge")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	ITE_None		UMETA(DisplayName = "None"),
	ITE_Knife		UMETA(DisplayName = "Knife"),
	ITE_Sword		UMETA(DisplayName = "Sword"),
	ITE_Bow			UMETA(DisplayName = "Bow"),
	ITE_Axe			UMETA(DisplayName = "Axe"),
	ITE_Spear		UMETA(DisplayName = "Spear"),
	ITE_Hummer		UMETA(DisplayName = "Hummer"),
	ITE_Staff		UMETA(DisplayName = "Staff"),
	ITE_Armor		UMETA(DisplayName = "Armor"),
	ITE_Boots		UMETA(DisplayName = "Boots"),
	ITE_Ring		UMETA(DisplayName = "Ring"),
	ITE_Amulet		UMETA(DisplayName = "Amulet"),
	ITE_Bracers		UMETA(DisplayName = "Bracers"),
	ITE_Helm		UMETA(DisplayName = "Helm"),
	ITE_Leggings	UMETA(DisplayName = "Leggings")
};

UENUM(BlueprintType)
enum class EInventorySlotType : uint8
{
	ISTE_OneToOne		UMETA(DisplayName = "OneToOne"),
	ISTE_TwoToOne		UMETA(DisplayName = "TwoToOne"),
	ISTE_ThreeToOne		UMETA(DisplayName = "ThreeToOne"),
	ISTE_FiveToOne		UMETA(DisplayName = "FiveToOne"),
	ISTE_TwoToTwo		UMETA(DisplayName = "TwoToTwo"),
	ISTE_ThreeToTwo		UMETA(DisplayName = "ThreeToTwo"),
	ISTE_FourToTwo		UMETA(DisplayName = "FourToTwo"),
	ISTE_FiveToTwo		UMETA(DisplayName = "FiveToTwo")
};

UENUM(BlueprintType)
enum class EStatBonusType : uint8
{
	SBTE_Absolute		UMETA(DisplayName = "Absolute"),
	SBTE_Multiplier		UMETA(DisplayName = "Multiplier"),
};

USTRUCT(BlueprintType)
struct FStatBonus
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttribute Stat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EStatBonusType StatBonusType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BonusValue;
};

USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info)
	EItemType ItemType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info)
	TSubclassOf<class ABaseItem> ItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	FText ItemDescription;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	class UTexture2D *ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	int32 MaxCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Game)
	EItemRarity Rarity = EItemRarity::IRE_Common;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Game)
	FName AttachSocket = "Weapon";

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Game)
	//class UGameplayAbility *Ability;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	TArray<FStatBonus> StatBonuses;

};