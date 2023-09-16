// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "GAS/BaseAbilitySystemComponent.h"
#include "GAS/BaseAttributeSet.h"
#include "Engine/CurveTable.h"
#include <GameplayAbilitySpec.h>
#include "Items/BaseItem.h"
#include "Core/HMBlueprintFunctionsLibrary.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("Attributes"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	IsAlive = true;
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		Attributes->Init();
		Attributes->OnHealthChanged.AddDynamic(this, &ABaseCharacter::OnHealthChanged);
		//Attributes->OnManaChanged.AddDynamic(this, &ABaseCharacter::OnHealthChanged);

		FTimerHandle SetLevelTimer;
		GetWorld()->GetTimerManager().SetTimer(SetLevelTimer, this, &ABaseCharacter::InitLevel, 1.f, false, 0.01f);
		GiveAbilities();
	}
}

void ABaseCharacter::InitLevel()
{
	SetLevel(Level);
}

void ABaseCharacter::LevelUp()
{
	if (Level < MaxLevel)
	{
		++Level;
		OnLevelChangedCall();
	}
}

void ABaseCharacter::SetLevel(int32 NewLevel)
{
	Level = NewLevel < 1 ? 1 : NewLevel;
	Level = Level > MaxLevel ? MaxLevel : Level;
	OnLevelChangedCall();
}

void ABaseCharacter::OnLevelChangedCall()
{
	InitializeAttributes();
	OnLevelChanged.Broadcast(Level);
}

void ABaseCharacter::InitializeAttributes()
{
	if (AbilitySystemComponent && StatTable)
	{
		GetAttributes()->SetAttributesByLevel(StatTable, Level);
	}
}

void ABaseCharacter::SetTarget_Implementation(ABaseCharacter* NewTarget)
{
	if (!NewTarget)
	{
		Target = nullptr;
	}
	else if (NewTarget != Target)
	{
		if (Target)
			Target->OnDeath.RemoveAll(this);
		Target = NewTarget;
		Target->OnDeath.AddUniqueDynamic(this, &ABaseCharacter::OnTargetDeath);
	}
}

void ABaseCharacter::OnTargetDeath(ABaseCharacter* DeadCharacter)
{
	if (DeadCharacter == Target)
	{
		SetTarget(nullptr);
	}
}

void ABaseCharacter::OnHealthChanged(float Health)
{
	//UE_LOG(LogTemp, Error, TEXT("%s have applied modifications."), *GetName());
	//Show damage ?
	UpdateHPBar();
	if (Health <= 0.f && IsAlive)
	{
		OnDeath.Broadcast(this);
		IsAlive = false;
		GetAbilitySystemComponent()->TryActivateAbility(DeathAbilitySpecHandle);
	}
}

void ABaseCharacter::EquipItem(class ABaseItem* Item)
{
	Item->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale, Item->ItemInfo.AttachSocket);
	GetAbilitySystemComponent()->TryActivateAbility(GAEquipSpecHandle);
}

float ABaseCharacter::GetItemsBonusesForAttribute(const FGameplayAttribute& Attibute, EStatBonusType BonusType)
{
	float TotalBonusValue = BonusType == EStatBonusType::SBTE_Absolute ? 0 : 1;
	for (auto Item : EquipedItems)
	{
		for (auto Bonus : Item->ItemInfo.StatBonuses)
		{
			if (Bonus.StatBonusType == BonusType && Bonus.Stat.AttributeName == Attibute.AttributeName)
			{
				TotalBonusValue += Bonus.BonusValue;
			}
		}
	}
	return TotalBonusValue;
}

void ABaseCharacter::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		if (DeathAbility.Get())
			DeathAbilitySpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(DeathAbility, Level));
		if (PrimaryAttack.Get())
			PrimaryAttackSpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(PrimaryAttack, Level));
		if (SecondaryAttack.Get())
			SecondaryAttackSpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(SecondaryAttack, Level));
	}
}

float ABaseCharacter::GetHealth() const
{
	if (!Attributes)
		return 1.f;

	return Attributes->GetHealth();
}

float ABaseCharacter::GetMaxHealth() const
{
	if (!Attributes)
		return 1.f;

	return Attributes->GetMaxHealth();
}
