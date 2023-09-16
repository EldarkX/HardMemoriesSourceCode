// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "Core/DataTypes.h"

#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChanged, int32, Level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFightNotification, EFightNotificationType, FightNotificationType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, class ABaseCharacter *, DeadCharacter);

UCLASS()
class HARDMEMORIES_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{

	GENERATED_BODY()

public:

	ABaseCharacter();

	/*GAS*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	class UBaseAttributeSet *GetAttributes() const { return Attributes; }

	UPROPERTY(EditDefaultsOnly)
	class UCurveTable *StatTable;
	
	virtual void GiveAbilities();
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Gas")
	TSubclassOf<class UGameplayAbility> PrimaryAttack;
	FGameplayAbilitySpecHandle PrimaryAttackSpecHandle;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Gas")
	TSubclassOf<class UGameplayAbility> SecondaryAttack;
	FGameplayAbilitySpecHandle SecondaryAttackSpecHandle;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Gas")
	TSubclassOf<class UGameplayAbility> DeathAbility;
	FGameplayAbilitySpecHandle DeathAbilitySpecHandle;

	FGameplayAbilitySpecHandle GAEquipSpecHandle;

	/*GAMEPLAY INFO*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Name;

	/*LEVELING*/
	UFUNCTION()
	void InitLevel();

	UFUNCTION(BlueprintCallable)
	void LevelUp();

	UFUNCTION(BlueprintCallable)
	void SetLevel(int32 NewLevel);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetLevel() const { return Level; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxLevel = 10;

	UPROPERTY(BlueprintAssignable)
	FOnLevelChanged OnLevelChanged;

	/*COMBAT*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABaseCharacter	*GetTarget() const { return Target; }
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetTarget(ABaseCharacter *NewTarget);
	UFUNCTION()
	void OnTargetDeath(ABaseCharacter *DeadCharacter);

	UPROPERTY(BlueprintAssignable)
	FOnFightNotification OnFightNotification;

	/*HEATH*/
	UFUNCTION()
	void OnHealthChanged(float Health);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHPBar();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsAlive() const { return IsAlive; }

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	/*EQUIPMENT*/
	UPROPERTY(BlueprintReadOnly)
	TArray<class ABaseItem *> EquipedItems;

	UFUNCTION()
	void EquipItem(class ABaseItem *Item);

	float GetItemsBonusesForAttribute(const FGameplayAttribute& Attibute, EStatBonusType BonusType);

	UFUNCTION(BlueprintCallable)
	virtual float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth() const;

	//UFUNCTION(BlueprintCallable)
	//virtual float GetMana() const;

	//UFUNCTION(BlueprintCallable)
	//virtual float GetMaxMana() const;

	//UFUNCTION(BlueprintCallable)
	//virtual float GetHealth() const;

	//UFUNCTION(BlueprintCallable)
	//virtual float GetMaxHealth() const;

	//UFUNCTION(BlueprintCallable)
	//virtual float GetHealth() const;

	//UFUNCTION(BlueprintCallable)
	//virtual float GetMaxHealth() const;

	//UFUNCTION(BlueprintCallable)
	//virtual float GetHealth() const;

	//UFUNCTION(BlueprintCallable)
	//virtual float GetMaxHealth() const;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	/*GAS*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBaseAbilitySystemComponent *AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly)
	class UBaseAttributeSet *Attributes;
	
	void InitializeAttributes();

	/*LEVELING*/
	void OnLevelChangedCall();

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	int32 Level = 0;

	/*HEALTH*/
	bool IsAlive;

	/*COMBAT*/
	UPROPERTY()
	ABaseCharacter *Target;


};
