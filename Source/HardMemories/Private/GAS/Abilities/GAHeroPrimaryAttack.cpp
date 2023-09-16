// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/GAHeroPrimaryAttack.h"

void UGAHeroPrimaryAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
    //ActorInfo->SkeletalMeshComponent->GetAnimInstance()->Montage_Play()

    UE_LOG(LogTemp, Error, TEXT("Primary attack"));
    
    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);    
}
