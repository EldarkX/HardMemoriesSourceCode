// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChanged, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExperienceChanged, float, NewExperience);

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class HARDMEMORIES_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	
	void Init();
	void SetAttributesByLevel(UCurveTable* StatTable, int32 Level);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	UFUNCTION()
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float NewValue);

	virtual void GetLifetimeReplicatedProps(::TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void RecalculateAttributes();

	UFUNCTION(BlueprintCallable)
	bool GetAttributeUIInfo(const FGameplayAttribute& Attribute, FString &Name, FString &Value);

	/*HEALTH*/
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Health);
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData &OldHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HealthRegeneration);

	UFUNCTION()
	virtual void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHealth)

	UFUNCTION()
    virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	/*MANA*/
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Mana);
	UPROPERTY(BlueprintAssignable)
	FOnManaChanged OnManaChanged;

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_ManaRegeneration)
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, ManaRegeneration);

	UFUNCTION()
	virtual void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxMana)

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	
	/*DAMAGE*/
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MinDamage)
	FGameplayAttributeData MinDamage;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MinDamage);

	UFUNCTION()
    virtual void OnRep_MinDamage(const FGameplayAttributeData &OldMinDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxDamage)
	FGameplayAttributeData MaxDamage;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxDamage);

	UFUNCTION()
	virtual void OnRep_MaxDamage(const FGameplayAttributeData& OldMaxDamage);

	/*EXPERIENCE*/
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Experience)
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Experience);
	UPROPERTY(BlueprintAssignable)
	FOnExperienceChanged OnExperienceChanged;

	UFUNCTION()
	virtual void OnRep_Experience(const FGameplayAttributeData& OldExperience);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_NecessaryExperience)
	FGameplayAttributeData NecessaryExperience;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, NecessaryExperience);

	UFUNCTION()
	virtual void OnRep_NecessaryExperience(const FGameplayAttributeData& OldNecessaryExperience);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_ExperienceCost)
	FGameplayAttributeData ExperienceCost;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, ExperienceCost);

	UFUNCTION()
	virtual void OnRep_ExperienceCost(const FGameplayAttributeData& OldExperienceCost);
	
	/*CHARACTERISRICS*/
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Strength);

	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Dexterity)
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Dexterity);

	UFUNCTION()
	virtual void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Intelligence);

	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);

	/*STRENGTH BONUSES*/
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, ArmorPenetration);

	UFUNCTION()
	virtual void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Letality)
	FGameplayAttributeData Letality;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Letality);

	UFUNCTION()
	virtual void OnRep_Letality(const FGameplayAttributeData& OldLetality);

	/*DEXTERITY BONUSES*/
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackSpeed)
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, AttackSpeed);

	UFUNCTION()
	virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_CritChance)
	FGameplayAttributeData CritChance;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CritChance);

	UFUNCTION()
	virtual void OnRep_CritChance(const FGameplayAttributeData& OldCritChance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_CritMultiplier)
	FGameplayAttributeData CritMultiplier;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CritMultiplier);

	UFUNCTION()
	virtual void OnRep_CritMultiplier(const FGameplayAttributeData& OldCritMultiplier);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Precision)
	FGameplayAttributeData Precision;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Precision);

	UFUNCTION()
	virtual void OnRep_Precision(const FGameplayAttributeData& OldPrecision); //Hit chance

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Evasion)
	FGameplayAttributeData Evasion;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Evasion);

	UFUNCTION()
	virtual void OnRep_Evasion(const FGameplayAttributeData& OldEvasion); //Chance to avoid hit

	/*Intelligence BONUSES*/
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_SkillPower)
	FGameplayAttributeData SkillPower;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, SkillPower);

	UFUNCTION()
	virtual void OnRep_SkillPower(const FGameplayAttributeData& OldSkillPower);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_EffectChance)
	FGameplayAttributeData EffectChance;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, EffectChance);

	UFUNCTION()
	virtual void OnRep_EffectChance(const FGameplayAttributeData& OldEffectChance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_CooldownReduction)
	FGameplayAttributeData CooldownReduction;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CooldownReduction);

	UFUNCTION()
	virtual void OnRep_CooldownReduction(const FGameplayAttributeData& OldCooldownReduction);

	/*BASED ON EQUIPMENT*/
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackRange)
	FGameplayAttributeData AttackRange;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, AttackRange);

	UFUNCTION()
	virtual void OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Armor);

	UFUNCTION()
		virtual void OnRep_Armor(const FGameplayAttributeData& OldArmor);

private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FGameplayAttribute> Attributes;

	TMap<FGameplayAttribute, float> DefaultAttributes;
	class ABaseCharacter* CharacterOwner;

};
