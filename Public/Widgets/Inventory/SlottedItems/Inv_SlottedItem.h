#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_SlottedItem.generated.h"


class UInv_InventoryItem;
class UImage;

UCLASS()
class INVENTORYSYSTEM_API UInv_SlottedItem : public UUserWidget
{
	GENERATED_BODY()

public:

	bool GetIsStackable() const { return bIsStackable;}
	void SetIsStackable(bool Stackable) { bIsStackable = Stackable; }
	int32 GetGridIndex() const { return GridIndex; }
	void SetGridIndex(int32 Index) { GridIndex = Index; }
	FIntPoint GetGridDimensions() const { return GridDimensions; }
	void SetGridDimensions(FIntPoint Dimensions) { GridDimensions = Dimensions; }
	UInv_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }
	void SetInventoryItem(UInv_InventoryItem* Item);
	UImage* GetImageIcon() const { return Image_Icon; }
	void SetImageBrush(const FSlateBrush& Brush) const;
	
protected:

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;

	int32 GridIndex;
	FIntPoint GridDimensions;
	bool bIsStackable{false};
};
