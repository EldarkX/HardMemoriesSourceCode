// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"
#include "Items/DA_BaseItem.h"
#include "Items/Components/ItemWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Core/HMBlueprintFunctionsLibrary.h"
#include "Player/HardMemoriesPlayerController.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	Collision->SetSphereRadius(120.);
	SetRootComponent(Collision);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	StaticMesh->SetupAttachment(GetRootComponent());

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	SkeletalMesh->SetupAttachment(GetRootComponent());
	
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetCollisionResponseToAllChannels(ECR_Ignore);
	Widget->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
	Widget->SetRelativeLocation(FVector(0, 0, 40));
	Widget->SetupAttachment(GetRootComponent());
}

void ABaseItem::OnEquip(AActor *NewOwner)
{
	SetOwner(NewOwner);
}

void ABaseItem::OnBeginOverlappWithHero(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	AHardMemoriesPlayerController* PC = Cast<AHardMemoriesPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC->GetPawn() == OtherActor && PC->ItemToPickUp == this)
	{
		PC->OnTryToPickUp(this);
	}
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseItem::SetItemInfo, 0.1f, false, 0.2f);
}

void ABaseItem::SetItemInfo()
{
	UDataTable *ItemsDT = UHMBlueprintFunctionsLibrary::GetItemsDataTable(this);
	if (ItemsDT)
	{
		FItemInfo *FoundItemInfo = ItemsDT->FindRow<FItemInfo>(ItemName, FString("ItemsDT"));
		if (FoundItemInfo)
		{
			ItemInfo = *FoundItemInfo;
			OnItemInfoSet();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BaseItem.cpp: can't find item info. Item name is %s"), *ItemName.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BaseItem.cpp: can't get ItemsDataTable"));
	}
}

void ABaseItem::OnItemInfoSet()
{
	Collision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABaseItem::OnBeginOverlappWithHero);
	
	Widget->SetWidgetClass(GetItemWidgetClass());
	ItemUserWidget = Cast<UItemWidget>(Widget->GetUserWidgetObject());
	if (ItemUserWidget)
	{
		ItemUserWidget->ItemObject = this;
		ItemUserWidget->UpdateAppearance();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Bad ItemWidger user widget class!"));	
	}
}

UClass *ABaseItem::GetItemWidgetClass()
{
	return UHMBlueprintFunctionsLibrary::GetBaseItemWidgetClass(this);
}
