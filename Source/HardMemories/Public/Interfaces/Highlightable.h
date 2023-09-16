// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Interface.h"
#include "Highlightable.generated.h"


UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UHighlightableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
	
};

class HARDMEMORIES_API IHighlightableInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual void Highlight() = 0;
	virtual void Unhighlight() = 0;

	virtual void Interact() = 0;

};

