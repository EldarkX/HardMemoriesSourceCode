// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/BaseEnemy.h"
#include "Character/Hero/BaseHero.h"
#include "GAS/BaseAbilitySystemComponent.h"
#include "Engine/World.h"
#include "Player/HardMemoriesPlayerController.h"

void ABaseEnemy::Highlight()
{
	AHardMemoriesPlayerController *PC = Cast<AHardMemoriesPlayerController>(GetWorld()->GetFirstPlayerController());
	PC->UpdateTargetWidget(this);
}

void ABaseEnemy::Unhighlight()
{
	AHardMemoriesPlayerController *PC = Cast<AHardMemoriesPlayerController>(GetWorld()->GetFirstPlayerController());
	PC->UpdateTargetWidget(nullptr);
}

void ABaseEnemy::Interact()
{
	ABaseHero *Hero = Cast<ABaseHero>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Hero->AttackTarget(this);
}
