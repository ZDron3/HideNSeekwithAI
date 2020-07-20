// Fill out your copyright notice in the Description page of Project Settings.


#include "HideNSeek_GameMode.h"
#include "Engine/World.h"
#include "LevelManager.h"
#include "Kismet/GameplayStatics.h"

void AHideNSeek_GameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// Spawn a LevelManager which will control an execution sequence of all spawners

	UWorld* World = this->GetWorld();

	if (World)
	{
		if (!UGameplayStatics::GetActorOfClass(World, ALevelManager::StaticClass()))
		{
			World->SpawnActor<ALevelManager>(ALevelManager::StaticClass(), FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);
		}
	}	
}

