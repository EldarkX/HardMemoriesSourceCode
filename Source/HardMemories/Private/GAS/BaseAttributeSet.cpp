// Fill out your copyright notice in the Description page of Project Settings.


#include "HardMemories/Public/GAS/BaseAttributeSet.h"
#include "Character/BaseCharacter.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include <HardMemories/Public/Character/Hero/BaseHero.h>
#include "Core/HMBlueprintFunctionsLibrary.h"

void UBaseAttributeSet::Init()
{
	GetOwningAbilitySystemComponent()->GetAllAttributes(Attributes);

    OnNumericValueSet.AddDynamic(this, &UBaseAttributeSet::PostAttributeChange);

    CharacterOwner = Cast<ABaseCharacter>(GetOwningActor());
    if (!CharacterOwner)
    {
        UHMBlueprintFunctionsLibrary::ExitWithErrorWindow(CharacterOwner, "UBaseAttributeSet: owner is not inherited from ABaseCharacter.");
    }
}

void UBaseAttributeSet::SetAttributesByLevel(UCurveTable* StatTable, int32 Level)
{
	auto AllCurves = StatTable->GetCurves();

	for (auto Curve : AllCurves)
	{
        FString AttrName = FString(Curve.CurveName.ToString());
        
        float Value = Curve.CurveToEdit->Eval(Level);

		FGameplayAttribute* Attribute = Attributes.FindByPredicate([&AttrName](FGameplayAttribute Attr) { return Attr.AttributeName == AttrName; });
		if (Attribute)
		{
			DefaultAttributes.Add(*Attribute, Value);
		}
        else
        {
            FString ErrorText = "UBaseAttributeSet: " + AttrName + " does not exist in attribute set.";
            UHMBlueprintFunctionsLibrary::ExitWithErrorWindow(CharacterOwner, ErrorText);
        }
	}

    RecalculateAttributes();

    SetHealth(GetMaxHealth());
    SetMana(GetMaxMana());
    SetExperience(0.);
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
    }
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UBaseAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float NewValue)
{
    if (Attribute == GetHealthAttribute())
    {
        OnHealthChanged.Broadcast(NewValue);
    }
	else if (Attribute == GetManaAttribute())
	{
		OnManaChanged.Broadcast(NewValue);
	}
	else if (Attribute == GetExperienceAttribute())
	{
		OnExperienceChanged.Broadcast(NewValue);
	}
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    //AActor* TargetActor = nullptr;
    //AController* TargetController = nullptr;
    //ABaseCharacter* TargetCharacter = nullptr;
    //    
    //if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
    //{
    //    TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
    //    TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
    //    TargetCharacter = Cast<ABaseCharacter>(TargetActor);

    //    if (!TargetCharacter)
    //    {
    //        UHMBlueprintFunctionsLibrary::ExitWithErrorWindow(TargetActor, FString("BaseAttributeSystem: owner is not inherited from ABaseCharacter."));
    //    }
    //}
    //if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    //{
    //    TargetCharacter->OnHealthChanged(Health.GetCurrentValue());
    //}
    //else if (Data.EvaluatedData.Attribute == GetExperienceAttribute())
    //{
    //    ABaseHero* Hero = Cast<ABaseHero>(TargetCharacter);
    //    if (Hero)
    //    {
    //        Hero->OnExperienceChanged(Experience.GetCurrentValue());
    //    }
    //}
}

void UBaseAttributeSet::GetLifetimeReplicatedProps(::TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MinDamage, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MaxDamage, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Experience, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, ExperienceCost, COND_None, REPNOTIFY_Always);
}

void UBaseAttributeSet::RecalculateAttributes()
{
	for (auto Attribute : DefaultAttributes)
	{
        float Value = Attribute.Value;
        if (Attribute.Key == GetStrengthAttribute() || Attribute.Key == GetDexterityAttribute() || Attribute.Key == GetIntelligenceAttribute())
        {
            Value += CharacterOwner->GetItemsBonusesForAttribute(Attribute.Key, EStatBonusType::SBTE_Absolute);
            Value *= CharacterOwner->GetItemsBonusesForAttribute(Attribute.Key, EStatBonusType::SBTE_Multiplier);
        }
        
        FStructProperty* StructProperty = CastField<FStructProperty>(Attribute.Key.GetUProperty());
        FGameplayAttributeData* DataPtr = StructProperty->ContainerPtrToValuePtr<FGameplayAttributeData>(this);
        DataPtr->SetBaseValue(Value);
		Attribute.Key.SetNumericValueChecked(Value, this);
	}

    TMap<FGameplayAttribute, float> AdditionalStats;

    float NewMaxHealth = GetMaxHealth() + GetStrength() * 10.f;

	AdditionalStats.Add(GetMaxHealthAttribute(), NewMaxHealth);
	AdditionalStats.Add(GetHealthRegenerationAttribute(), NewMaxHealth / 120.f);
	AdditionalStats.Add(GetMinDamageAttribute(), GetMinDamage() + GetStrength());
    AdditionalStats.Add(GetMaxDamageAttribute(), GetMaxDamage() + GetStrength());
    AdditionalStats.Add(GetArmorPenetrationAttribute(), GetStrength() * 0.0005f);
    AdditionalStats.Add(GetLetalityAttribute(), GetStrength() * 0.0005f);

    AdditionalStats.Add(GetAttackSpeedAttribute(), 0.75f + GetDexterity() * 0.01f);
    AdditionalStats.Add(GetCritChanceAttribute(), GetDexterity() * 0.001f);
    AdditionalStats.Add(GetCritMultiplierAttribute(), 1.f + GetDexterity() * 0.01f);
    AdditionalStats.Add(GetEvasionAttribute(), 20.f + GetDexterity() * 5.f);
    AdditionalStats.Add(GetPrecisionAttribute(), 20.f + GetDexterity() * 5.f);

    float NewMaxMana = GetMaxMana() + GetIntelligence() * 10.f;

    AdditionalStats.Add(GetMaxManaAttribute(), NewMaxMana);
    AdditionalStats.Add(GetManaRegenerationAttribute(), NewMaxMana / 120.f);
    AdditionalStats.Add(GetSkillPowerAttribute(), 20.f + GetIntelligence() * 5.f);
    AdditionalStats.Add(GetEffectChanceAttribute(), GetIntelligence() * 0.001f);
    AdditionalStats.Add(GetCooldownReductionAttribute(), GetIntelligence() * 0.005f);

    for (auto Attr : AdditionalStats)
    {
        float Value = Attr.Value;
		Value += CharacterOwner->GetItemsBonusesForAttribute(Attr.Key, EStatBonusType::SBTE_Absolute);
		Value *= CharacterOwner->GetItemsBonusesForAttribute(Attr.Key, EStatBonusType::SBTE_Multiplier);

		FStructProperty* StructProperty = CastField<FStructProperty>(Attr.Key.GetUProperty());
		FGameplayAttributeData* DataPtr = StructProperty->ContainerPtrToValuePtr<FGameplayAttributeData>(this);
		DataPtr->SetBaseValue(Value);
        Attr.Key.SetNumericValueChecked(Value, this);
    }

    AdditionalStats.Empty();
}

bool UBaseAttributeSet::GetAttributeUIInfo(const FGameplayAttribute& Attribute, FString& Name, FString& Value)
{
    if (Attribute == GetExperienceAttribute() || Attribute == GetExperienceCostAttribute() || Attribute == GetNecessaryExperienceAttribute()
        || Attribute == GetMinDamageAttribute() || Attribute == GetAttackRangeAttribute() || Attribute == GetMaxHealthAttribute()
        || Attribute == GetMaxManaAttribute())
    {
        return false;
    }

    Name = Attribute.AttributeName;

    if (Attribute == GetMaxDamageAttribute())
    {
        Name = "Damage";
        Value = FString::FromInt(GetMinDamage()) + "-" + FString::FromInt(GetMaxDamage());
    }
    else if (Attribute == GetHealthAttribute() || Attribute == GetManaAttribute())
    {
        Value = FString::FromInt(GetHealth()) + "/" + FString::FromInt(GetMaxHealth());
    }
    else if (Attribute == GetArmorPenetrationAttribute() || Attribute == GetLetalityAttribute() || Attribute == GetAttackSpeedAttribute()
        || Attribute == GetCritChanceAttribute() || Attribute == GetCritMultiplierAttribute() || Attribute == GetEffectChanceAttribute()
        || Attribute == GetCooldownReductionAttribute())
    {
        Value = FString::Printf(TEXT("%.2f%%"), Attribute.GetNumericValue(this) * 100);
    }
    else
    {
        Value = FString::FromInt(Attribute.GetNumericValue(this));
    }

    return true;
}

void UBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Health, OldHealth);
}

void UBaseAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UBaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MaxHealth, OldMaxHealth);
}

void UBaseAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Mana, OldMana);
}

void UBaseAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UBaseAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MaxMana, OldMaxMana);
}

void UBaseAttributeSet::OnRep_MinDamage(const FGameplayAttributeData& OldMinDamage)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MinDamage, OldMinDamage);
}

void UBaseAttributeSet::OnRep_MaxDamage(const FGameplayAttributeData& OldMaxDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MaxDamage, OldMaxDamage);
}

void UBaseAttributeSet::OnRep_Experience(const FGameplayAttributeData& OldExperience)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Experience, OldExperience);
}

void UBaseAttributeSet::OnRep_NecessaryExperience(const FGameplayAttributeData& OldNecessaryExperience)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, NecessaryExperience, OldNecessaryExperience);
}

void UBaseAttributeSet::OnRep_ExperienceCost(const FGameplayAttributeData& OldExperienceCost)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, ExperienceCost, OldExperienceCost);
}

void UBaseAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Strength, OldStrength);
}

void UBaseAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Dexterity, OldDexterity);
}

void UBaseAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Intelligence, OldIntelligence);
}

void UBaseAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UBaseAttributeSet::OnRep_Letality(const FGameplayAttributeData& OldLetality)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Letality, OldLetality);
}

void UBaseAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, AttackSpeed, OldAttackSpeed);
}

void UBaseAttributeSet::OnRep_CritChance(const FGameplayAttributeData& OldCritChance)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, CritChance, OldCritChance);
}

void UBaseAttributeSet::OnRep_CritMultiplier(const FGameplayAttributeData& OldCritMultiplier)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, CritMultiplier, OldCritMultiplier);
}

void UBaseAttributeSet::OnRep_Precision(const FGameplayAttributeData& OldPrecision)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Precision, OldPrecision);
}

void UBaseAttributeSet::OnRep_Evasion(const FGameplayAttributeData& OldEvasion)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Evasion, OldEvasion);
}

void UBaseAttributeSet::OnRep_SkillPower(const FGameplayAttributeData& OldSkillPower)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, SkillPower, OldSkillPower);
}

void UBaseAttributeSet::OnRep_EffectChance(const FGameplayAttributeData& OldEffectChance)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, EffectChance, OldEffectChance);
}

void UBaseAttributeSet::OnRep_CooldownReduction(const FGameplayAttributeData& OldCooldownReduction)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, CooldownReduction, OldCooldownReduction);
}

void UBaseAttributeSet::OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, AttackRange, OldAttackRange);
}

void UBaseAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Armor, OldArmor);
}



