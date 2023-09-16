// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "HMCheatManager.generated.h"

UCLASS()
class HARDMEMORIES_API UHMCheatManager : public UCheatManager
{
	GENERATED_BODY()

	class AHardMemoriesPlayerController* PC;

public:

	UFUNCTION(Exec)
	void CheatSetHeroLevel(int32 Level);

	UFUNCTION(Exec)
	void CheatApplyDamageToHero(int32 Damage);

	UFUNCTION(Exec)
	void CheatApplyDamageToMouseTarget(int32 Damage);

	void ApplyDamage(class ABaseCharacter *Target, int32 Damage);
	
private:
	void InitCheatManager() override;

};
