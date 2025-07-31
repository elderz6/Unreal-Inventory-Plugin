#include "Inv_PlayerController.h"
#include "InventorySystem.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Widgets/HUD/Inv_HUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Interaction/Inv_Highlightable.h"

AInv_PlayerController::AInv_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	ItemTraceChannel = ECC_GameTraceChannel1;
	TraceLength = 500.0;
}

void AInv_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceForItem();
}

void AInv_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogInventory, Log, TEXT("Begin Play"));

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(DefaultIMC, 0);
	}

	InventoryComponent = FindComponentByClass<UInv_InventoryComponent>();

	CreateHUDWidget();;

}

void AInv_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(PrimaryInteractAction, ETriggerEvent::Started, this, &ThisClass::PrimaryInteract);
	EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &ThisClass::ToggleInventory);
}

void AInv_PlayerController::PrimaryInteract()
{
	//UE_LOG(LogTemp, Log, TEXT("Primary Interact"))
	if (!CurrentActor.IsValid()) return;
	UInv_ItemComponent* ItemComp = CurrentActor->GetComponentByClass<UInv_ItemComponent>();
	
	if (!IsValid(ItemComp) || !InventoryComponent.IsValid()) return;
	InventoryComponent->TryAddItem(ItemComp);
}

void AInv_PlayerController::ToggleInventory()
{
	if (!InventoryComponent.IsValid()) return;
	InventoryComponent->ToggleInventoryMenu();
}


void AInv_PlayerController::CreateHUDWidget()
{
	if (!IsLocalController()) return;

	HUDWidget = CreateWidget<UInv_HUDWidget>(this, HUDWidgetClass);

	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}

void AInv_PlayerController::TraceForItem()
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport)) return;

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize / 2;
	FVector TraceStart;
	FVector Forward;

	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward)) return;

	const FVector TraceEnd = TraceStart + Forward * TraceLength;
	FHitResult HitResult;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ItemTraceChannel);

	LastActor = CurrentActor;
	CurrentActor = HitResult.GetActor();

	if (!CurrentActor.IsValid())
	{
		if (IsValid(HUDWidget)) HUDWidget->HidePickupMessage();
	}

	if(CurrentActor == LastActor) return;
	if (CurrentActor.IsValid())
	{
		UActorComponent* Highlightable = CurrentActor->FindComponentByInterface(UInv_Highlightable::StaticClass());
		if (IsValid(Highlightable))
		{
			IInv_Highlightable::Execute_Highlight(Highlightable);
		}


		UInv_ItemComponent* ItemComponent = CurrentActor->FindComponentByClass<UInv_ItemComponent>();

		if (!IsValid(ItemComponent)) return;

		if (IsValid(HUDWidget)) HUDWidget->ShowPickupMessage(ItemComponent->GetPickupMessage());
	}


	if (LastActor.IsValid())
	{
		UActorComponent* Highlightable = LastActor->FindComponentByInterface(UInv_Highlightable::StaticClass());
		if (IsValid(Highlightable))
		{
			IInv_Highlightable::Execute_UnHighlight(Highlightable);
		}
	}
}
