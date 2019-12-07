// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class MINECRAFTUNREAL_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

	/*Base shape collision*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Block | Collision")
	class UBoxComponent* CollisionVolume;

	/*Base Mesh Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Block | Mesh")
	class UStaticMeshComponent* SM_Block;

	uint8 MinimumMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Block | Resistance")
	float Resistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Block | BreakingStage")
	float BreakingStage;

	/*Called every time we want to break the block down further*/

	void Break();

	void ResetBlock();

	/*Called once the block has hit the final breaking stage*/
	void OnBroken(bool HasRequiredPickaxe);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




};
