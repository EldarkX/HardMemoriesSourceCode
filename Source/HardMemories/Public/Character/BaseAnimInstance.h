// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HARDMEMORIES_API UBaseAnimInstance : public UAnimInstance
{

	GENERATED_BODY()
	
public:
	
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	
	virtual bool HandleNotify(const FAnimNotifyEvent& AnimNotifyEvent) override;
	
private:

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class ABaseCharacter *Character;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float Speed;
	
};
