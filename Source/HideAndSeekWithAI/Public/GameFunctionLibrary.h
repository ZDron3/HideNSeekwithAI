// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	AIEnemies 	UMETA(DisplayName = "AIEnemies"),
	Players 	UMETA(DisplayName = "Players"),
};

UCLASS()
class HIDEANDSEEKWITHAI_API UGameFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static uint8 JoinGameTeam(const ETeam Team);

	static void StopGame(UObject* WorldContextObject);
	
};
