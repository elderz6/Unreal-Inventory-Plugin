#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_GridTypes.cpp"

#include "Inv_InventoryGrid.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInv_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE EInv_ItemCategory GetItemCategory() const { return ItemCategory; }

protected:


private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
	EInv_ItemCategory ItemCategory;

	
};
