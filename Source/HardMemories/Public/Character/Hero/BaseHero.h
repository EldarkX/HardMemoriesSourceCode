// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "BaseHero.generated.h"

/**
 * 
 */
UCLASS()
class HARDMEMORIES_API ABaseHero : public ABaseCharacter
{
	GENERATED_BODY()

public:
	
	ABaseHero();

	UFUNCTION(BlueprintCallable)
	void OnExperienceChanged(float NewExperience);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateExperienceBar();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetExperience() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetNecessaryExperience() const;

	void AttackTarget(ABaseCharacter *Target);
	
protected:

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	void PossessedBy(AController* NewController) override;

private:
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};
