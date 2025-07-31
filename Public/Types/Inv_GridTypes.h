#pragma once

#include "CoreMinimal.h"
#include "Inv_GridTypes.generated.h"

class UInv_InventoryItem;

UENUM(BlueprintType)
enum class EInv_ItemCategory : uint8
{
	Equippable,
	Consumable,
	Craftable,
	None
};

USTRUCT()
struct FInv_SlotAvailability
{
	GENERATED_BODY()
	FInv_SlotAvailability() {}
	FInv_SlotAvailability(int32 ItemIndex, int32 Room, bool HasItem) : Index(ItemIndex), AmountToFill(Room), bItemAtIndex(HasItem) {}

	int32 Index{INDEX_NONE};
	int32 AmountToFill{0};
	bool bItemAtIndex{false};
};

USTRUCT(BlueprintType)
struct FInv_SlotAvailabilityResult
{
	GENERATED_BODY()
	FInv_SlotAvailabilityResult() {}

	TWeakObjectPtr<UInv_InventoryItem> Item;
	TArray<FInv_SlotAvailability> SlotAvailabilities;
	bool bIsStackable{false};
	int32 TotalRoomToFill{0};
	int32 Remainder{0};
};