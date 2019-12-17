// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wieldable.generated.h"

UENUM(BlueprintType)
enum class ETool : uint8
{
	Unarmed			UMETA(DisplayName = "Unarmed"),
	PickAxe			UMETA(DisplayName = "PickAxe"),
	Axe				UMETA(DisplayName = "Axe"),
	Shovel			UMETA(DisplayName = "Shovel"),
	Sword			UMETA(DisplayName = "Sword"),

	MAX				UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EMaterial : uint8
{
	None	= 1		UMETA(DisplayName = "None"),
	Wooden	= 2		UMETA(DisplayName = "Wooden"),
	Stone	= 4		UMETA(DisplayName = "Stone"),
	Iron	= 6		UMETA(DisplayName = "Iron"),
	Diamond	= 8		UMETA(DisplayName = "Diamond"),
	Golden	= 12	UMETA(DisplayName = "Golden"),

	MAX				UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class MINECRAFTUNREAL_API AWieldable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWieldable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool")
	ETool ToolType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	EMaterial MaterialType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
	USkeletalMeshComponent* WieldableMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimitiveComponent")
	UPrimitiveComponent* PickupTrigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PrimitiveComponent")
	UTexture2D* PickupThumbnail;

	bool bIsActive;

	void Hide(bool bVis);

	void OnUsed();

	// declare overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
