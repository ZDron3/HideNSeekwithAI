// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Perception/AIPerceptionSystem.h"
#include "AIRecognizable.generated.h"

class UAISense_Sight;

UENUM(BlueprintType)
enum class EAITeam : uint8
{
	Players   UMETA(DisplayName = "Players"),
	AIEnemies UMETA(DisplayName = "AIEnemies"),
	Neutrals  UMETA(DisplayName = "Neutrals"),
	
};


// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable)
class UAIRecognizable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HIDEANDSEEKWITHAI_API IAIRecognizable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AIRecognizable")
		void SetAITeam(const EAITeam AITeamToSet);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AIRecognizable")
		EAITeam GetAITeam();

	FGenericTeamId GetAITeamId() const
	{
		return AITeamId;
	}

protected:
	
	FGenericTeamId AITeamId;	
};
