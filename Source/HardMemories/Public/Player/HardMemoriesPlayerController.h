// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/Highlightable.h"

#include "HardMemoriesPlayerController.generated.h"

UCLASS()
class AHardMemoriesPlayerController : public APlayerController
{
	
	GENERATED_BODY()
	
public:
	AHardMemoriesPlayerController();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTargetWidget(AActor *Target);

	UFUNCTION()
	void OnEquipItemHandle(class ABaseItem *EquipedItem);

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);
	
	UPROPERTY()
	class ABaseItem *ItemToPickUp;

	UFUNCTION()
	void OnTryToPickUp(class ABaseItem *PickedUpItem);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryComponent *InventoryComponent;

	class ABaseHero* GetHero() const;

	friend class UHMBlueprintFunctionsLibrary;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMousePressed : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void CheckHighlightable();

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	virtual void OnPossess(APawn* aPawn) override;
	
	IHighlightableInterface *HighlightableObject;

private:

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class ABaseHero* Hero;

	bool IsErrorTriggered = false;
};


