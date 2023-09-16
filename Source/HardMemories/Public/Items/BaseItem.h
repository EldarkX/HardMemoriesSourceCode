// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/DataTypes.h"

#include "BaseItem.generated.h"

UCLASS()
class HARDMEMORIES_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

	/*Equiping*/

	UFUNCTION()
	void OnEquip(AActor *NewOwner);

	/*META*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FItemInfo ItemInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent *Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent *StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent *SkeletalMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent *Widget;

	UFUNCTION()
	void OnBeginOverlappWithHero(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual UClass *GetItemWidgetClass();
	
protected:

	virtual void BeginPlay() override; // fall animation or equipping

private:

	UPROPERTY()
	class UItemWidget *ItemUserWidget;

	UFUNCTION()
	void SetItemInfo();

	void OnItemInfoSet();
	
};
