// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "BasePluralItem.generated.h"

/**
 * 
 */
UCLASS()
class HARDMEMORIES_API ABasePluralItem : public ABaseItem
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	int32 Amount = 1;

	virtual UClass* GetItemWidgetClass() override;
	
};
