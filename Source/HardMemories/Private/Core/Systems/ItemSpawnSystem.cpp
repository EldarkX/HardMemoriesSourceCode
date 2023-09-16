// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Systems/ItemSpawnSystem.h"


#include "Character/Enemy/BaseEnemy.h"
#include "Core/HardMemoriesGameMode.h"
#include "Items/BaseItem.h"
#include "Kismet/GameplayStatics.h"
#include "NavMesh/RecastNavMesh.h"

AItemSpawnSystem::AItemSpawnSystem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AItemSpawnSystem::BeginPlay()
{
	Super::BeginPlay();

	AssigneOnEnemyDeaths();

	FillItemsMap();
}

void AItemSpawnSystem::AssigneOnEnemyDeaths()
{
	TArray<AActor *> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseEnemy::StaticClass(), Enemies);

	for (auto EnemyActor : Enemies)
	{
		ABaseEnemy *Enemy = Cast<ABaseEnemy>(EnemyActor);
		Enemy->OnDeath.AddUniqueDynamic(this, &AItemSpawnSystem::OnEnemyDeath);
	}
}

void AItemSpawnSystem::OnEnemyDeath(ABaseCharacter* Enemy)
{
	SelectItemByProbabilityType(Cast<ABaseEnemy>(Enemy)->ProbabilityType, Enemy);
}

void AItemSpawnSystem::FillItemsMap()
{
	if (ItemsDataTable)
	{
		TArray<FItemInfo *> ItemInfos;
		ItemsDataTable->GetAllRows(FString("ItemsDataTAble") ,ItemInfos);

		for (auto ItemInfo : ItemInfos)
		{
			TArray<TSubclassOf<ABaseItem>> *Items = ItemsByRarity.Find(ItemInfo->Rarity);
			if (Items)
			{
				Items->AddUnique(ItemInfo->ItemClass);
			}
			else
			{
				TArray<TSubclassOf<ABaseItem>> NewItems;
				NewItems.Add(ItemInfo->ItemClass);
				ItemsByRarity.Add(ItemInfo->Rarity, NewItems);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ItemsSpawnSystem.cpp: there isn't the ItemsDataTable"));
	}
}

void AItemSpawnSystem::SelectItemByProbabilityType(EProbabilityType ProbabilityType, AActor *Holder) const
{
	int32 Amount = RandomSelectItemsAmount();
	FVector Origin = Holder->GetActorLocation();
	float SpawnRadius = BaseSpawnRadius * Amount;
	SpawnRadius = SpawnRadius > 600. ? 600. : SpawnRadius;
	// spawn gold
	
	for (int i = 1; i <= Amount; ++i)
	{
		EItemRarity ItemRarity = RandomSelectItemRarity(ProbabilityType);

		const TArray<TSubclassOf<ABaseItem>> *Items = ItemsByRarity.Find(ItemRarity);
		if (Items)
		{
			int32 RandIndex = FMath::RandRange(0, Items->Num() - 1);
			TSubclassOf<ABaseItem> ItemClass = Items->GetData()[RandIndex];

			FTimerHandle SpawnItemTimerHandle;
			FTimerDelegate SpawnItemTimerDelegate;
			SpawnItemTimerDelegate.BindUObject(const_cast<AItemSpawnSystem*>(this), &AItemSpawnSystem::SpawnItem, ItemClass, Origin, SpawnRadius);
			GetWorld()->GetTimerManager().SetTimer(SpawnItemTimerHandle, SpawnItemTimerDelegate, 1., false, DelayBetweenSpawns * i);
		}
	}
}

EItemRarity AItemSpawnSystem::RandomSelectItemRarity(EProbabilityType ProbabilityType) const
{
	float ProbabilityCoef = 0.05 * static_cast<int32>(ProbabilityType);
	float Probabilty = FMath::RandRange(0.f, 1.f - ProbabilityCoef);
	if (Probabilty > 0.6)
	{
		return EItemRarity::IRE_Garbage;
	}
	if (Probabilty > 0.25)
	{
		return EItemRarity::IRE_Common;
	}
	if (Probabilty > 0.08)
	{
		return EItemRarity::IRE_Rare;
	}
	if (Probabilty > 0.01)
	{
		return EItemRarity::IRE_Epic;
	}
	if (Probabilty > 0.005)
	{
		return EItemRarity::IRE_Legendary;
	}
	return EItemRarity::IRE_Heavenly;
}

int32 AItemSpawnSystem::RandomSelectItemsAmount() const
{
	int32 Value = FMath::RandRange(0, 125);
	Value = FMath::Pow(Value, 0.3);
	return 5 - Value;
}

void AItemSpawnSystem::SpawnItem(TSubclassOf<ABaseItem> ItemClass, FVector Origin, float Radius)
{
	FNavLocation NavLocation;
	GM->NavMesh->GetRandomReachablePointInRadius(Origin, Radius, NavLocation);

	SpawnItem(ItemClass, NavLocation.Location);
}

void AItemSpawnSystem::SpawnItem(TSubclassOf<ABaseItem> ItemClass, FVector SpawnLocation)
{
	FTransform ItemTransform = FTransform(FRotator::ZeroRotator, SpawnLocation, FVector::OneVector);
	
	ABaseItem *NewItem = GetWorld()->SpawnActorDeferred<ABaseItem>(ItemClass, ItemTransform,
        this, GetWorld()->GetFirstPlayerController()->GetPawn(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (NewItem)
	{
		UGameplayStatics::FinishSpawningActor(NewItem, ItemTransform);
	}
}

