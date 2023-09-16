// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Effects/DamageCalculation.h"
#include "Character/BaseCharacter.h"
#include "GAS/BaseAttributeSet.h"
#include "Character/Hero/BaseHero.h"
#include "Core/DataTypes.h"

DEFINE_LOG_CATEGORY_STATIC(LogDamageCalculation, All, All);

float UDamageCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	Super::CalculateBaseMagnitude_Implementation(Spec);
	
	ABaseCharacter* Avatar = Cast<ABaseCharacter>(Spec.GetEffectContext().GetInstigator());
	ABaseCharacter* Target = Avatar->GetTarget();

	bool IsCrit = false;

	float Damage = 1.f;

	if (Avatar && Target)
	{
		float AvatarPrecision = Avatar->GetAttributes()->GetPrecision();
		float TargetEvasion = Target->GetAttributes()->GetEvasion();

		float EvasionChance = FMath::Clamp(1 - AvatarPrecision / (AvatarPrecision + FMath::Pow(TargetEvasion / 4, 0.8)), 0.05f, 0.95f);
		
		float RandowValue = FMath::RandRange(0.f, 1.f);

		if (RandowValue <= EvasionChance)
		{
			UE_LOG(LogDamageCalculation, Log, TEXT("%s has evaded with %f evasion chance."), *Target->Name, EvasionChance);
			UE_LOG(LogDamageCalculation, Log, TEXT("%s has missed with %f hit chance."), *Avatar->Name, 1 - EvasionChance);
			Avatar->OnFightNotification.Broadcast(EFightNotificationType::FNTE_Miss);
			return 0.f;
		}
		else
		{
			Damage = FMath::RandRange(Avatar->GetAttributes()->GetMinDamage(), Avatar->GetAttributes()->GetMaxDamage());

			UE_LOG(LogDamageCalculation, Log, TEXT("%s has %f damage."), *Avatar->Name, (int32)Damage);

			RandowValue = FMath::RandRange(0.f, 1.f);

			IsCrit = RandowValue <= Avatar->GetAttributes()->GetCritChance();
			if (IsCrit)
			{
				float CriticalMultiplier = FMath::Clamp(Avatar->GetAttributes()->GetCritMultiplier(), 1.f, 10.f);
				Damage *= CriticalMultiplier;
				UE_LOG(LogDamageCalculation, Log, TEXT("%s will hit critically %f damage with %f crit chance and % crit multiplier."), 
					*Avatar->Name, Damage, Avatar->GetAttributes()->GetCritChance(), CriticalMultiplier);
			}

			float TargetArmor = Target->GetAttributes()->GetArmor();

			if (Cast<ABaseHero>(Avatar))
			{
				RandowValue = FMath::RandRange(0.f, 1.f);

				float OverDamagePercent = Damage / FMath::Pow((Target->GetAttributes()->GetMaxHealth() + Target->GetAttributes()->GetArmor() / 10.f), 2);

				if (RandowValue < Avatar->GetAttributes()->GetLetality() + OverDamagePercent)
				{
					UE_LOG(LogDamageCalculation, Log, TEXT("%s has applied letality damage with %f letality chance and %f overdamage percent."),
						*Avatar->Name, Avatar->GetAttributes()->GetLetality(), OverDamagePercent);
					Damage = Target->GetAttributes()->GetMaxHealth();

					Avatar->OnFightNotification.Broadcast(EFightNotificationType::FNTE_Letality);

					return -FMath::RoundToFloat(Damage);
				}
			}
			else
			{
				Damage = FMath::Clamp(Damage - (TargetArmor / 10) * Avatar->GetAttributes()->GetArmorPenetration(), 1.f, Damage);
				UE_LOG(LogDamageCalculation, Log, TEXT("%s has applied %f damage with %f armor penetration, target armor is %f."),
					*Avatar->Name, Damage, Avatar->GetAttributes()->GetArmorPenetration(), TargetArmor);
			}
		}		
	}
	if (IsCrit) Avatar->OnFightNotification.Broadcast(EFightNotificationType::FNTE_Crit);

	return -FMath::RoundToFloat(Damage);
}
