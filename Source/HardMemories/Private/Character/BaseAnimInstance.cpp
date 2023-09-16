// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseAnimInstance.h"


#include "AbilitySystemBlueprintLibrary.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Particles/Event/ParticleModuleEventSendToGame.h"

void UBaseAnimInstance::NativeBeginPlay()
{
	Character = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Character)
	{
		Speed = Character->GetVelocity().Size() / Character->GetMovementComponent()->GetMaxSpeed();
	}
}

bool UBaseAnimInstance::HandleNotify(const FAnimNotifyEvent& AnimNotifyEvent)
{
	if (AnimNotifyEvent.NotifyName.ToString() == "ApplyDamage")
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Character, FGameplayTag::EmptyTag, FGameplayEventData());
		return true;
	}
	return false;
}


