// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EQuestType : uint8
{
	QTE_Kill			UMETA(DisplayName="Kill"),
	QTE_KillBoss		UMETA(DisplayName="KillBoss"),
	QTE_Loot			UMETA(DisplayName="Loot"),
	QTE_Interactive		UMETA(DisplayName="Interactive")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HARDMEMORIES_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
