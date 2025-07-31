// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "Inv_InventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInv_InventoryItem : public UObject
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	void SetItemManifest(const FInv_ItemManifest& Manifest);
protected:

private:
	UPROPERTY(VisibleAnywhere, meta=(BaseStruct = "/Script/InventorySystem.Inv_ItemManifest"), Replicated, Category="Inventory")
	FInstancedStruct ItemManifest;
};
