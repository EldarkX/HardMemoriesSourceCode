// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "CalculationHealthRegeneration.generated.h"

UCLASS()
class HARDMEMORIES_API UCalculationHealthRegeneration : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

};
