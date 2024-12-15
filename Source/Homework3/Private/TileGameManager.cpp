// Develloped by R. Berk Sozgen for GAD2006.


#include "TileGameManager.h"

#include "TilePlayerController.h"
#include "GameFramework/PlayerInput.h"

// Sets default values
ATileGameManager::ATileGameManager() :
	GridSize(100),
	GridOffset(0.f,0.f,.5f),
	MapExtendsInGrids(25)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	GridSelection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridMesh"));
	GridSelection->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		PlaneMesh(TEXT("Engine/BasicShapes/Plane"));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		GridMaterial(TEXT("/Game/UI/MAT_GridSlot"));

	GridSelection->SetStaticMesh(PlaneMesh.Object);
	GridSelection->SetMaterial(0, GridMaterial.Object);
	GridSelection->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ATileGameManager::BeginPlay()
{
	Super::BeginPlay();

	if (auto PlayerController =
			Cast<ATilePlayerController>(GWorld->GetFirstPlayerController()))
	{
		PlayerController->GameManager = this;
	}
	
}

// Called every frame
void ATileGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileGameManager::OnActorInteraction(AActor* HitActor, FVector& Location, bool bIsPressed)
{
	//No tile types?
	if (TileTypes.Num() <= 0) return;

	FVector GridLoc = GridOffset;
	GridLoc.X = FMath::GridSnap(Location.X, GridSize);
	GridLoc.Y = FMath::GridSnap(Location.Y, GridSize);
	GridLoc.Z = Location.Z;

	UPlayerInput* PlayerInput = GWorld->GetFirstPlayerController()->PlayerInput;

	if (PlayerInput->WasJustPressed(EKeys::LeftMouseButton))
	{
		int GridX = GridLoc.X / GridSize + MapExtendsInGrids;
		int GridY = GridLoc.Y / GridSize + MapExtendsInGrids;

		if (GridX < 0 || GridY < 0 || //Cannot place out of the grid
			GridX >= MapExtendsInGrids * 2 || GridY >= MapExtendsInGrids * 2) return;
		
		if(MAP[GridX][GridY] != nullptr) return; //Already a tile here?

		if(TileTypes.IsValidIndex(CurrentTileIndex))
		{
			ATileBase* SelectedTile = TileTypes[CurrentTileIndex];
			MAP[GridX][GridY] = SelectedTile;

			FTransform TileTransform(GridLoc + GridOffset);
			SelectedTile->InstancedMesh->AddInstance(
				SelectedTile->InstancedMesh->GetRelativeTransform() * TileTransform, true);
		}

		UE_LOG(LogTemp, Warning, TEXT("Hit: %s - %f,%f,%f"),
			HitActor ? *HitActor->GetActorLabel() : TEXT("None"),
			Location.X, Location.Y, Location.Z);
	}
	else if(PlayerInput->WasJustPressed(EKeys::RightMouseButton)) //TurnSelectedTileRight
	{
		FRotator TurnRight(.0f,90.f,.0f);

		int GridX = GridLoc.X / GridSize + MapExtendsInGrids;
		int GridY = GridLoc.Y / GridSize + MapExtendsInGrids;

		if (GridX < 0 || GridY < 0 || //Cannot rotate out of the grid
			GridX >= MapExtendsInGrids * 2 || GridY >= MapExtendsInGrids * 2) return;
		
		if(MAP[GridX][GridY] != nullptr) MAP[GridX][GridY]->SetActorRotation(TurnRight);
	}
	else if(PlayerInput->WasJustPressed(EKeys::MouseScrollDown))
	{
		CurrentTileIndex = (CurrentTileIndex + 1) % TileTypes.Num();
		UE_LOG(LogTemp, Warning, TEXT("Tile Type: %s"), *TileTypes[CurrentTileIndex]->GetActorLabel());
	}
	else if(PlayerInput->WasJustPressed(EKeys::MouseScrollUp))
	{
		CurrentTileIndex = (CurrentTileIndex - 1) % TileTypes.Num();
		UE_LOG(LogTemp, Warning, TEXT("Tile Type: %s"), *TileTypes[CurrentTileIndex]->GetActorLabel());
	}
	else GridSelection->SetWorldLocation(GridLoc + GridOffset);
}

