// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Items/DA_BaseItem.h"
#include "Items/Components/ItemWidget.h"
#include "Kismet/GameplayStatics.h"

#include "HardMemoriesGameMode.generated.h"

UCLASS(minimalapi)
class AHardMemoriesGameMode : public AGameModeBase
{
protected:
	virtual void BeginPlay() override;
private:
	GENERATED_BODY()

public:
	AHardMemoriesGameMode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UItemsHelpData *DA_ItemsHelpData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AItemSpawnSystem> ItemSpawnSystemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AItemSpawnSystem> QuestManagerClass;

	UPROPERTY(BlueprintReadOnly)
	class AItemSpawnSystem *ItemSpawnSystem;

	UPROPERTY(BlueprintReadOnly)
	class AQuestManager *QuestManager;
	
	UPROPERTY(BlueprintReadOnly)
	class ARecastNavMesh *NavMesh;

private:
	
	template<class T>
	T *SpawnSubsystem(TSubclassOf<AActor> SubsystemClass);
};

template<class T>
T* AHardMemoriesGameMode::SpawnSubsystem(TSubclassOf<AActor> SubsystemClass)
{
	FTransform WorldCenter = FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector);
	T *NewSubsystem = GetWorld()->SpawnActorDeferred<T>(SubsystemClass,
        WorldCenter, this, GetWorld()->GetFirstPlayerController()->GetPawn(),
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (NewSubsystem)
	{
		NewSubsystem->GM = this;
		UGameplayStatics::FinishSpawningActor(NewSubsystem, WorldCenter);
	}
	return NewSubsystem;
}



