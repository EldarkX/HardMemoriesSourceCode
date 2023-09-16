// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Core/DataTypes.h"
#include "Interfaces/Highlightable.h"
#include "BaseEnemy.generated.h"

UCLASS()
class HARDMEMORIES_API ABaseEnemy : public ABaseCharacter, public IHighlightableInterface
{
	
	GENERATED_BODY()
	
public:

	virtual void Highlight() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Unhighlight() override;
	
	virtual void Interact() override;

	UPROPERTY(EditDefaultsOnly)
	EProbabilityType ProbabilityType;
	
private:

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<class UGameplayEffect> AddPlayerExperienceEffect;

};
