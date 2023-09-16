// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Core/DataTypes.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnSystem.generated.h"

UCLASS()
class HARDMEMORIES_API AItemSpawnSystem : public AActor
{
	GENERATED_BODY()
	
public:
	
	AItemSpawnSystem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDataTable *ItemsDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DelayBetweenSpawns = 0.1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BaseSpawnRadius = 20.;

	friend class AHardMemoriesGameMode;
	
protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEnemyDeath(class ABaseCharacter *Enemy);

private:

	UPROPERTY()
	class AHardMemoriesGameMode *GM;

	TMap<EItemRarity, TArray<TSubclassOf<class ABaseItem>>> ItemsByRarity;

	void AssigneOnEnemyDeaths();
	void FillItemsMap();
	
	void SelectItemByProbabilityType(EProbabilityType ProbabilityType,
		AActor *Holder) const;

	EItemRarity RandomSelectItemRarity(EProbabilityType ProbabilityType) const;
	
	int32 RandomSelectItemsAmount() const;

	void SpawnItem(TSubclassOf<ABaseItem> ItemClass, FVector Origin, float Radius);
	void SpawnItem(TSubclassOf<ABaseItem> ItemClass, FVector SpawnLocation);

};
