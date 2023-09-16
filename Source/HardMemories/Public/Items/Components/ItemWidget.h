// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Items/DA_BaseItem.h"

#include "ItemWidget.generated.h"
 
UCLASS()
class HARDMEMORIES_API UItemWidget : public UUserWidget
{
	
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAppearance();
	
	UFUNCTION(BlueprintImplementableEvent)
	void HighlightWidget();

	UFUNCTION(BlueprintImplementableEvent)
    void UnhighlightWidget();

	UPROPERTY(BlueprintReadOnly)
	class ABaseItem *ItemObject;

protected:
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
};
