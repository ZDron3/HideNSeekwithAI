// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"
#include "Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "HideNSeekGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>


ALevelManager::ALevelManager()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint>ObstacleClass(TEXT("Blueprint'/Game/HideAndSeekWithAI/GameEntities/Obstacle_BP.Obstacle_BP'"));
	if (ObstacleClass.Succeeded() && ObstacleClass.Object)
	{
		ObstacleRef = (UClass*)ObstacleClass.Object->GeneratedClass;
		ObstacleNum = (Cast<AGameSpawnActor>(ObstacleClass.Object->GeneratedClass->ClassDefaultObject))->NumberToSpawn;
		UE_LOG(LogTemp, Warning, TEXT("No is , %d "), ObstacleNum);
	}


	static ConstructorHelpers::FObjectFinder<UBlueprint>PickUpClass(TEXT("Blueprint'/Game/HideAndSeekWithAI/GameEntities/PickUp_BP.PickUp_BP'"));
	if (PickUpClass.Succeeded() && PickUpClass.Object)
	{
		PickUpRef = (UClass*)PickUpClass.Object->GeneratedClass;
		PickUpNum = (Cast<AGameSpawnActor>(PickUpClass.Object->GeneratedClass->ClassDefaultObject))->NumberToSpawn;
		UE_LOG(LogTemp, Warning, TEXT("No is , %d "), PickUpNum);
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint>AICharacter(TEXT("Blueprint'/Game/HideAndSeekWithAI/Characters/BP_AI_bot.BP_AI_bot'"));
	if (PickUpClass.Succeeded() && PickUpClass.Object)
	{
		AICharacterRef = (UClass*)AICharacter.Object->GeneratedClass;
		AI_Characater_Num = (Cast<ABase_GameCharacter>(AICharacter.Object->GeneratedClass->ClassDefaultObject))->TotalAICharacters;
		UE_LOG(LogTemp, Warning, TEXT("No is , %d "), AI_Characater_Num);
	}


	const UWorld* World = this->GetWorld();
	if (World)
	{
		SpawnDimensions = (AObjectSpawnDimensions*)UGameplayStatics::GetActorOfClass(World, AObjectSpawnDimensions::StaticClass());
	}
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	const AObjectSpawnDimensions* Dimension = FindSpawnDimensions();
	if (Dimension)
	{

		SpawnElements(Dimension, ObstacleRef, ObstacleNum);

		SpawnElements(Dimension, PickUpRef, PickUpNum);

		SpawnAI(Dimension, AICharacterRef, AI_Characater_Num);	
	}
}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

const AObjectSpawnDimensions* ALevelManager::FindSpawnDimensions() const
{
	for (TActorIterator<AObjectSpawnDimensions> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		const AObjectSpawnDimensions* SpawnDimensionRef = Cast<AObjectSpawnDimensions>(*ActorItr);
		if (SpawnDimensionRef)
		{
			return SpawnDimensionRef;
		}
	}
	return nullptr;
}


void  ALevelManager::SpawnElements(const AObjectSpawnDimensions* SpawnDimension, UClass* ClassRef, int NumofElements)
{
	uint8 Count = 0;
	uint8 Attempts = 0;
	FActorSpawnParameters SpawnInfo;
	FVector Origin(SpawnDimension->GetActorLocation());
	FVector SpawnBounds(SpawnDimension->GetArea()->GetScaledBoxExtent());
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	while (Count < NumofElements)
	{
		const FVector SpawnLocation(UKismetMathLibrary::RandomPointInBoundingBox(Origin, SpawnBounds));
		const FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ClassRef, SpawnLocation, SpawnRotation, SpawnInfo);
		if (SpawnedActor)
		{
			++Count;
		}
		else
		{
			++Attempts;
			if (Attempts == MAX_RETRIES)
			{
				break;
			}
		}
	}

}

void ALevelManager::SpawnAI(const AObjectSpawnDimensions* SpawnDimension, UClass* ClassRef, int NumofElements)
{

	uint8 Count = 0;
	uint8 Attempts = 0;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	FVector Origin(SpawnDimension->GetActorLocation());
	FVector SpawnBounds(SpawnDimension->GetArea()->GetScaledBoxExtent());


	while (Count < NumofElements)
	{
		const FVector SpawnLocation(UKismetMathLibrary::RandomPointInBoundingBox(Origin, SpawnBounds));
		const FRotator SpawnRotation(0.0f, FMath::FRand() * 360.0f, 0.0f);
		ABase_GameCharacter* AI_Character = GetWorld()->SpawnActor<ABase_GameCharacter>(ClassRef, SpawnLocation, SpawnRotation, SpawnInfo);

		if (AI_Character)
		{
			AI_Character->SetActorLocation(SpawnLocation);
			AI_Character->SpawnDefaultController();
			ABase_AIController* Controller = Cast<ABase_AIController>(AI_Character->GetController());
			if (Controller)
			{
				if (!Controller->IsPlayerInSafeDistance() || Controller->IsPlayerInSight())
				{
					//restart level
					UHideNSeekGameInstance* GameInstance = Cast<UHideNSeekGameInstance>(UGameplayStatics::GetGameInstance(this));
					if (GameInstance)
					{
						GameInstance->RestartCurrentLevel();
					}
				}

				++Count;
			}
			else
			{
				++Attempts;
				if (Attempts == MAX_RETRIES)
				{
					break;
				}
			}
		}
	}
}




