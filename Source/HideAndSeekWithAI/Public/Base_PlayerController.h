// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "Base_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEKWITHAI_API ABase_PlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	
	ABase_PlayerController();

protected:

	virtual void BeginPlay() override;	
};
