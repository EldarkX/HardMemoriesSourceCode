// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/ExperienceToEarnCalculation.h"
#include "Character/BaseCharacter.h"
#include "GAS/BaseAttributeSet.h"

float UExperienceToEarnCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	Super::CalculateBaseMagnitude_Implementation(Spec);
	
	ABaseCharacter* Avatar = Cast<ABaseCharacter>(Spec.GetEffectContext().GetInstigator());
	ABaseCharacter* Target = Avatar->GetTarget();

	return Avatar->GetAttributes()->GetExperienceCost();
}
