// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ObjectSpawnDimensions.h"
#include "GameSpawnActor.h"
#include "Base_GameCharacter.h"
#include "LevelManager.generated.h"




UCLASS()
class HIDEANDSEEKWITHAI_API ALevelManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnElements(const AObjectSpawnDimensions* SpawnDimension, UClass* ClassRef, int NumofElements);

	void SpawnAI(const AObjectSpawnDimensions* SpawnDimension, UClass* ClassRef, int NumofElements);

	const AObjectSpawnDimensions* FindSpawnDimensions()const;

	UPROPERTY(EditAnywhere, Category = "Level Components")
		AObjectSpawnDimensions* SpawnDimensions;

	UPROPERTY(EditAnywhere, Category = "Level Components")
		TSubclassOf<class AGameSpawnActor> ObstacleRef;

	UPROPERTY(EditAnywhere, Category = "Level Components")
		TSubclassOf<class AGameSpawnActor> PickUpRef;

	UPROPERTY(EditAnywhere, Category = "Level Components")
		TSubclassOf<class ABase_GameCharacter> AICharacterRef;

	
private:
	static constexpr uint8 MAX_RETRIES = 100;

	int ObstacleNum;

	int PickUpNum;

	int AI_Characater_Num;
	
};
