// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HMCheatManager.h"
#include "Player/HardMemoriesPlayerController.h"
#include "Character/Hero/BaseHero.h"
#include "GAS/BaseAttributeSet.h"

void UHMCheatManager::CheatSetHeroLevel(int32 Level)
{
	PC->GetHero()->SetLevel(Level);
}

void UHMCheatManager::CheatApplyDamageToHero(int32 Damage)
{
	ApplyDamage(PC->GetHero(), Damage);
}

void UHMCheatManager::CheatApplyDamageToMouseTarget(int32 Damage)
{
	FHitResult HitResult;

	PC->GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, HitResult);

	if (HitResult.bBlockingHit)
	{
		ABaseCharacter* Character = Cast<ABaseCharacter>(HitResult.Actor);
		if (Character)
		{
			ApplyDamage(Character, Damage);
		}
	}
}

void UHMCheatManager::ApplyDamage(class ABaseCharacter* Target, int32 Damage)
{
	float Health = Target->GetAttributes()->GetHealth();
	Target->GetAttributes()->SetHealth(Health - Damage);
}

void UHMCheatManager::InitCheatManager()
{
	Super::InitCheatManager();
	
	PC = Cast<AHardMemoriesPlayerController>(GetWorld()->GetFirstPlayerController());
}
