// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetBaseCharacter.h"
#include "Engine/GameInstance.h"
#include "NetGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNetGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable) //BP's exposing referances as Out Params. It's Suck
	void HostGame(FString MapName, FSPlayerInfo PlayerInfo);

	UFUNCTION(BlueprintCallable)
	void JoinGame(FString Address, FSPlayerInfo PlayerInfo);

	UPROPERTY(BlueprintReadWrite)
	FSPlayerInfo PlayerInfo;
};
