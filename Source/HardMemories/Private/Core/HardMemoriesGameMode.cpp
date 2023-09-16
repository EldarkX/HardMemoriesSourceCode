// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/HardMemoriesGameMode.h"

#include "NavMesh/RecastNavMesh.h"
#include "Core/Systems/ItemSpawnSystem.h"
#include "Core/Systems/QuestSystem/QuestManager.h"


AHardMemoriesGameMode::AHardMemoriesGameMode()
{
	
}

void AHardMemoriesGameMode::BeginPlay()
{
	TArray<AActor *> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARecastNavMesh::StaticClass(), Actors);

	if (!Actors.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("AHardMemoriesHameMode: There isn't RecastNavMesh actor."));
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
	}
	else
		NavMesh = Cast<ARecastNavMesh>(Actors[0]);
	
	
	ItemSpawnSystem = SpawnSubsystem<AItemSpawnSystem>(ItemSpawnSystemClass);
	QuestManager = SpawnSubsystem<AQuestManager>(QuestManagerClass);

}
