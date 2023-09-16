// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Components/ItemWidget.h"

#include "Components/SphereComponent.h"
#include "Items/BaseItem.h"
#include "Player/HardMemoriesPlayerController.h"

void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	HighlightWidget();
}

void UItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	UnhighlightWidget();
}

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if (InMouseEvent.GetEffectingButton().GetFName() == "LeftMouseButton")
	{
		AHardMemoriesPlayerController *PC = Cast<AHardMemoriesPlayerController>(GetWorld()->GetFirstPlayerController());
		PC->OnTryToPickUp(ItemObject);
		return FReply::Handled();
	}
	return FReply::Unhandled();
}
