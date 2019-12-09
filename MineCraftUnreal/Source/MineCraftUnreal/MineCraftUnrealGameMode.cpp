// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MineCraftUnrealGameMode.h"
#include "MineCraftUnrealHUD.h"
#include "MineCraftUnrealCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"


void AMineCraftUnrealGameMode::BeginPlay()
{
	Super::BeginPlay();

	ApplyHUDChanges();

}

AMineCraftUnrealGameMode::AMineCraftUnrealGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMineCraftUnrealHUD::StaticClass();

	HUDState = (uint8)EHUDState::HS_Ingame;

}

void AMineCraftUnrealGameMode::ApplyHUDChanges()
{
	/*Remove the previous hud, since we're applying a new one*/
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
	}

	/*Check the hudstate, and apply the hud correspondding to whatever hud should be open*/
	switch(HUDState)
	{
		case (uint8)EHUDState::HS_Ingame:
		{
			ApplyHUD(IngameHUDClass, false, false);
		}
		case (uint8)EHUDState::HS_Inventory:
		{
			ApplyHUD(InventoryHUDClass, true, true);
		}
		case (uint8)EHUDState::HS_Craft_Menu:
		{
			ApplyHUD(IngameHUDClass, true, true);
		}
		default:
		{
			ApplyHUD(IngameHUDClass, false, false);
		}
	}
}

uint8 AMineCraftUnrealGameMode::GetHUDState()
{
	return (uint8)HUDState;
}

void AMineCraftUnrealGameMode::ChangeHUDState(uint8 NewState)
{
	HUDState = NewState;
	ApplyHUDChanges();
}

bool AMineCraftUnrealGameMode::ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool ShowMouseCursor, bool EnableClickEvents)
{
	
	/*Get reference to the player, and the player controller*/
	AMineCraftUnrealCharacter* MyCharacter = Cast<AMineCraftUnrealCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	/*Nullcheck the widget before applying it*/
	if (WidgetToApply != nullptr)
	{
		/*Set mouse events and visibility according to the parameters taken by the function*/
		MyController->bShowMouseCursor = ShowMouseCursor;
		MyController->bEnableClickEvents = EnableClickEvents;

		/*Create the widget*/
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetToApply);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			return true;
		}
		else return false;
	}
	else return false;

}
