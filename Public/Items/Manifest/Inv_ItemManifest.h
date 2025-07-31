#pragma once

#include "CoreMinimal.h"
#include "Types/Inv_GridTypes.h"
#include "StructUtils/InstancedStruct.h"
#include "GameplayTags.h"
#include "Inv_ItemManifest.generated.h"

struct FInv_ItemFragment;
class UInv_InventoryItem;
USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FInv_ItemManifest
{
	GENERATED_BODY()

public:

	UInv_InventoryItem* Manifest(UObject* NewOuter);
	EInv_ItemCategory GetItemCategory() const { return ItemCategory; };
	FGameplayTag GetItemType() const { return ItemType; };

protected:

private:

	UPROPERTY(EditAnywhere, Category= "Inventory", meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FInv_ItemFragment>> Fragments;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	EInv_ItemCategory ItemCategory{EInv_ItemCategory::None};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag ItemType;
};
