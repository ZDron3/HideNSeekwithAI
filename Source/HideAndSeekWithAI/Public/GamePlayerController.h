// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_PlayerController.h"
#include "GamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEKWITHAI_API AGamePlayerController : public ABase_PlayerController
{
	GENERATED_BODY()

public:

	AGamePlayerController();
	
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
	
};
