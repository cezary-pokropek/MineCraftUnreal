// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MineCraftUnrealGameMode.generated.h"


UENUM(BlueprintType)
enum class EHUDState : uint8
{
	HS_Ingame		UMETA(DisplayName = "InGame"),
	HS_Inventory	UMETA(DisplayName = "Inventory"),
	HS_Craft_Menu	UMETA(DisplayName = "CraftMenu"),

	MAX				UMETA(DisplayName = "DefaultMax")
};

UCLASS(minimalapi)
class AMineCraftUnrealGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	AMineCraftUnrealGameMode();

	/*Checks the hud state, and then calls applyhud to apply whatever hud we're using*/
	void ApplyHUDChanges();

	/*Gets the hud state*/
	uint8 GetHUDState();

	/*Setter function for hudstate, applies the new state and then calls applyhudchanges*/
	UFUNCTION(BlueprintCallable, Category = "HUD Functions")
	void ChangeHUDState(uint8 NewState);

	/*Applies a hud to the screen, returns true if succesful, false otherwise*/
	bool ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool ShowMouseCursor, bool EnableClickEvents);

protected:

	/*The current hudstate*/
	uint8 HUDState;

	/*The hud to be shown ingame*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprint Widgets", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> IngameHUDClass;

	/*The hud to be shown in the inventory*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprint Widgets", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> InventoryHUDClass;

	/*The hud to be shown in the crafting menu*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprint Widgets", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> CraftMenuHUDClass;

	/*The current hud being displayed on the screen*/
	class UUserWidget* CurrentWidget;


};
