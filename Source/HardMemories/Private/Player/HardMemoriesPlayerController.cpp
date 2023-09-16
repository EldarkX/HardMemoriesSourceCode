// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/HardMemoriesPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GAS/BaseAbilitySystemComponent.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Character/Hero/BaseHero.h"
#include "Items/BaseItem.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/Components/InventoryComponent.h"
#include "Core/HMBlueprintFunctionsLibrary.h"
#include <Components/SphereComponent.h>
#include <Components/CapsuleComponent.h>
#include "Player/HMCheatManager.h"

AHardMemoriesPlayerController::AHardMemoriesPlayerController()
{
	bShowMouseCursor = true;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");

	CheatClass = UHMCheatManager::StaticClass();
}

void AHardMemoriesPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	Hero = Cast<ABaseHero>(aPawn);
	if (!Hero)
	{
		UHMBlueprintFunctionsLibrary::ExitWithErrorWindow(this, TEXT("AHardMemoriesPlayerController: bad pawn. Has to be inherited from ABaseHero."));
	}
	InventoryComponent->OnEquipItem.AddDynamic(this, &AHardMemoriesPlayerController::OnEquipItemHandle);
}

void AHardMemoriesPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CheckHighlightable();
	 if (bMousePressed)
	 {
	 	ItemToPickUp = nullptr;
	 	if (HighlightableObject)
	 	{
	 		AActor *Actor = Cast<AActor>(HighlightableObject->_getUObject());
	 		if (Actor && FVector::Dist2D(GetCharacter()->GetActorLocation(), Actor->GetActorLocation()) < 250)
	 		{
	 			HighlightableObject->Interact();
	 		}
	 		else if (Actor)
	 		{
	 			SetNewMoveDestination(Actor->GetActorLocation());
	 		}
	 	}
	 	else if (!Hero->GetAbilitySystemComponent()->GetAnimatingAbility())
	 	{
	 		FHitResult Hit;
	 		GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit);
	 		if (Hit.bBlockingHit)
	 		{
	 			SetNewMoveDestination(Hit.ImpactPoint);
	 		}
	 	}
	 }
}

void AHardMemoriesPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AHardMemoriesPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AHardMemoriesPlayerController::OnSetDestinationReleased);
}

void AHardMemoriesPlayerController::CheckHighlightable()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_GameTraceChannel2, true, Hit);

	if (Hit.bBlockingHit)
	{
		IHighlightableInterface *NewHighlightableObject = Cast<IHighlightableInterface>(Hit.Actor);
		if (!HighlightableObject)
		{
			HighlightableObject = NewHighlightableObject;
			HighlightableObject->Highlight();
		}
		else if (HighlightableObject && NewHighlightableObject != HighlightableObject)
		{
			HighlightableObject->Unhighlight();
			HighlightableObject = NewHighlightableObject;
			HighlightableObject->Highlight();
		}
	}
	else if (HighlightableObject)
	{
		HighlightableObject->Unhighlight();
		HighlightableObject = nullptr;
	}
}

void AHardMemoriesPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	if (Hero)
	{
		float const Distance = FVector::Dist(DestLocation, Hero->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AHardMemoriesPlayerController::OnTryToPickUp(ABaseItem* PickedUpItem)
{
	float Distance = FVector::Dist2D(Hero->GetActorLocation(), PickedUpItem->GetActorLocation());
	float RadiusDistance = PickedUpItem->Collision->GetScaledSphereRadius() + Hero->GetCapsuleComponent()->GetScaledCapsuleRadius();

	if (Distance < RadiusDistance)
	{
		InventoryComponent->AddItem(PickedUpItem, 1);
		ItemToPickUp = nullptr;
	}
	else
	{
		ItemToPickUp = PickedUpItem;
		SetNewMoveDestination(PickedUpItem->GetActorLocation());
	}
}

ABaseHero* AHardMemoriesPlayerController::GetHero() const
{
	return Hero;
}

void AHardMemoriesPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMousePressed = true;
}

void AHardMemoriesPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMousePressed = false;
}

void AHardMemoriesPlayerController::OnEquipItemHandle(class ABaseItem* EquipedItem)
{
	EquipedItem->OnEquip(Hero);
}
