// Fill out your copyright notice in the Description page of Project Settings.


#include "Wieldable.h"
#include "Components/SkeletalMeshComponent.h"
#include "MineCraftUnrealCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
AWieldable::AWieldable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupTrigger"));
	RootComponent = PickupTrigger;

	WieldableMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WieldableMesh"));
	WieldableMesh->SetupAttachment(GetRootComponent());

	PickupTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWieldable::OnOverlapBegin);
	PickupTrigger->OnComponentEndOverlap.AddDynamic(this, &AWieldable::OnOverlapEnd);

	MaterialType = EMaterial::None;
	ToolType = ETool::Unarmed;

	bIsActive = true;

}

// Called when the game starts or when spawned
void AWieldable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWieldable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotation = PickupTrigger->GetComponentRotation();
	rotation.Yaw += 1.f;
	PickupTrigger->SetRelativeRotation(rotation);

}

void AWieldable::OnPickedUp()
{
	WieldableMesh->SetVisibility(false);
	bIsActive = false;
}

void AWieldable::OnUsed()
{
	Destroy();
}

void AWieldable::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AMineCraftUnrealCharacter* Character = Cast<AMineCraftUnrealCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		Character->FP_WieldedItem->SetSkeletalMesh(WieldableMesh->SkeletalMesh);
		Character->AddItemToInventory(this);

		OnPickedUp();

	}
}

void AWieldable::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}