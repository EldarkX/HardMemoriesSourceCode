// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnSystem.generated.h"

UCLASS()
class HARDMEMORIES_API AEnemySpawnSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
