// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HideNSeekGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEKWITHAI_API UHideNSeekGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

		UHideNSeekGameInstance(const FObjectInitializer& ObjectInitializer);
	 
     	void RestartCurrentLevel();

		void LoadLevel(const FName& Name, bool bAbsolute, FString Options = FString(TEXT("")));
};
