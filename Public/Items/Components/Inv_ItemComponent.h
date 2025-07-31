#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "Inv_ItemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class INVENTORYSYSTEM_API UInv_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInv_ItemComponent();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	FString GetPickupMessage() const { return PickupMessage; };
	FInv_ItemManifest GetItemManifest() const { return ItemManifest; }

protected:

private:

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FString PickupMessage;

	UPROPERTY(EditAnywhere, Category = "Inventory", Replicated)
	FInv_ItemManifest ItemManifest;
		
};
