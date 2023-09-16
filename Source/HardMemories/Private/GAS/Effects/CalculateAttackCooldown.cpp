// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/CalculateAttackCooldown.h"
#include "Character/BaseCharacter.h"
#include "GAS/BaseAttributeSet.h"

float UCalculateAttackCooldown::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	Super::CalculateBaseMagnitude_Implementation(Spec);
	
	ABaseCharacter* Avatar = Cast<ABaseCharacter>(Spec.GetEffectContext().GetInstigator());

	return (1.f / Avatar->GetAttributes()->GetAttackSpeed());
}
