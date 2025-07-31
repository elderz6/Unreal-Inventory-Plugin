#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManagement/FastArray/Inv_FastArray.h"
#include "Inv_InventoryComponent.generated.h"

class UInv_ItemComponent;
class UInv_InventoryItem;
class UInv_InventoryBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemChange, UInv_InventoryItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoRoomInInventory);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORYSYSTEM_API UInv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInv_InventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	void ToggleInventoryMenu();

	UFUNCTION(Server, Reliable)
	void Server_AddNewItem(UInv_ItemComponent* ItemComponent, int32 StackCount);
	
	UFUNCTION(Server, Reliable)
	void Server_AddStacksToItem(UInv_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Inventory")
	void TryAddItem(UInv_ItemComponent* ItemComponent);

	void AddRepSubObj(UObject* SubObject);

	FInventoryItemChange OnItemAdded;
	FInventoryItemChange OnItemRemoved;
	FNoRoomInInventory NoRoomInInventory;
	
protected:
	virtual void BeginPlay() override;

private:	

	TWeakObjectPtr<APlayerController> OwningController;

	UPROPERTY()
	TObjectPtr<UInv_InventoryBase> InventoryMenu;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UInv_InventoryBase> InventoryMenuClass;

	UPROPERTY(Replicated)
	FInv_InventoryFastArray InventoryList;
	
	bool bInventoryOpen;

	void OpenInventoryMenu();

	void CloseInventoryMenu();

	void ConstructInventory();



};
