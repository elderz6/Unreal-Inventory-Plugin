#pragma once
#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "Inv_FastArray.generated.h"

class UInv_InventoryComponent;
class UInv_InventoryItem;
class UInv_ItemComponent;
//Single entry in the inventory
USTRUCT(BlueprintType)
struct FInv_InventoryEntry : public FFastArraySerializerItem
{
	GENERATED_BODY();

	FInv_InventoryEntry() {	}
	
private:
	friend struct FInv_InventoryFastArray;
	friend UInv_InventoryComponent;
	
	UPROPERTY()
	TObjectPtr<UInv_InventoryItem> Item = nullptr;
};

//List of inventory items
USTRUCT()
struct FInv_InventoryFastArray : public FFastArraySerializer
{
	GENERATED_BODY()

	FInv_InventoryFastArray() : OwnerComponent(nullptr) {}
	FInv_InventoryFastArray(UActorComponent* InOwnerComponent) : OwnerComponent(InOwnerComponent) {}

	TArray<UInv_InventoryItem*> GetAllItems() const;

	//FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FastArrayDeltaSerialize<FInv_InventoryEntry, FInv_InventoryFastArray>(Entries, DeltaParams, *this);
	};

	UInv_InventoryItem* AddEntry(UInv_InventoryItem* Item);
	UInv_InventoryItem* AddEntry(UInv_ItemComponent* ItemComponent);
	void RemoveEntry(UInv_InventoryItem* Item);
	
private:
	friend UInv_InventoryComponent;
	
	UPROPERTY()
	TArray<FInv_InventoryEntry> Entries;
	
	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
	
};

template<>
struct TStructOpsTypeTraits<FInv_InventoryFastArray> : TStructOpsTypeTraitsBase2<FInv_InventoryFastArray>
{
	enum { WithNetDeltaSerializer = true };
};