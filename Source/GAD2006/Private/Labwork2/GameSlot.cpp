// Fill out your copyright notice in the Description page of Project Settings.


#include "Labwork2/GameSlot.h"

// Sets default values
AGameSlot::AGameSlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);
	Box->SetBoxExtent(FVector(50.f,50.f,2.f));
	Box->SetCollisionResponseToAllChannels(ECR_Block);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultSlotMesh(TEXT("Engine/BasicShapes/Plane"));

	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	Plane->SetupAttachment(RootComponent);
	Plane->SetStaticMesh(DefaultSlotMesh.Object);
}

// Called when the game starts or when spawned
void AGameSlot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameSlot::SetState(EGridState NewState)
{
	GridState = NewState;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		DefaultSlotMaterial(TEXT("/Game/Labwork2/Materials/MAT_GridSlot"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		DefaultSlotMaterial_H(TEXT("/Game/Labwork2/Materials/MAT_GridSlot_Highlighted"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		DefaultSlotMaterial_O(TEXT("/Game/Labwork2/Materials/MAT_GridSlot_Offensive"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		DefaultSlotMaterial_S(TEXT("/Game/Labwork2/Materials/MAT_GridSlot_Supportive"));

	switch (GridState)
	{
	case GS_Default:
		Plane->SetMaterial(0, DefaultSlotMaterial.Object);
		break;
	case GS_Highlighted:
		Plane->SetMaterial(0, DefaultSlotMaterial_H.Object);
		break;
	case GS_Offensive:
		Plane->SetMaterial(0, DefaultSlotMaterial_O.Object);
		break;
	case GS_Supportive:
		Plane->SetMaterial(0, DefaultSlotMaterial_S.Object);
		break;
	}
}

void AGameSlot::SpawnUnitHere(TSubclassOf<AUnitBase>& UnitClass)
{
	FVector Location = GetActorLocation();
	AUnitBase* NewUnit = Cast<AUnitBase>(GWorld->SpawnActor(UnitClass, &Location));
	if (NewUnit) NewUnit->AssignToSlot(this);
}

