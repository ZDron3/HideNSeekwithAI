// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFunctionLibrary.h"
#include "EnemyCharacter.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

uint8 UGameFunctionLibrary::JoinGameTeam(const ETeam Team)
{
	switch (Team)
	{
	case  ETeam::AIEnemies:
		
		return 0;
		
	case  ETeam::Players:

		return 1;
	}

	return 255; // No Team by default. 255 is a value for No Team specified by UE4
}

void UGameFunctionLibrary::StopGame(UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);

		if (PlayerController)
		{
		
			PlayerController->UnPossess();

			TArray<AActor*>AllEnemyActors;
			UGameplayStatics::GetAllActorsOfClass(WorldContextObject, AEnemyCharacter::StaticClass(), AllEnemyActors);

			for (AActor* EnemyActor : AllEnemyActors)
			{
				AAIController* EnemyAIController = UAIBlueprintHelperLibrary::GetAIController(EnemyActor);

				if (EnemyAIController)
				{
					EnemyAIController->UnPossess();
				}
			}

		UGameplayStatics::OpenLevel(WorldContextObject, FName(*UGameplayStatics::GetCurrentLevelName(WorldContextObject)));
			

		}
	}	
}
