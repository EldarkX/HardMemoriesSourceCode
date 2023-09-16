// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Hero/BaseHero.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/BaseAttributeSet.h"

ABaseHero::ABaseHero()
{
    	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true; 

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
}

void ABaseHero::OnExperienceChanged(float NewExperience)
{
	UpdateExperienceBar();
	if (NewExperience >= GetAttributes()->GetNecessaryExperience())
	{
		LevelUp();
	}
}

float ABaseHero::GetExperience() const
{
	if (!Attributes)
		return 1.f;

	return Attributes->GetExperience();
}

int32 ABaseHero::GetNecessaryExperience() const
{
	return GetAttributes()->GetNecessaryExperience();
}

void ABaseHero::AttackTarget(ABaseCharacter* NewTarget)
{
	SetTarget(NewTarget);
	GetAbilitySystemComponent()->TryActivateAbility(PrimaryAttackSpecHandle);
}

void ABaseHero::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (AbilitySystemComponent)
	{
		Attributes->OnExperienceChanged.AddDynamic(this, &ABaseHero::OnExperienceChanged);
	}
}

