// Develloped by R. Berk Sozgen for GAD2006.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TilePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ATilePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	class ATileGameManager* GameManager;
	
};
