// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Base_AIController.generated.h"

class ABase_GameCharacter;
class AEnemyCharacter;
class APlayerCharacter;

UENUM(BlueprintType)
enum class EPerceptionType : uint8
{
	SightPerception    UMETA(DisplayName = "SightPerception"),
	HearingPerception  UMETA(DisplayName = "HearingPerception"),
};

UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API ABase_AIController : public AAIController
{
	GENERATED_BODY()	

public:

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetDetectionByAffiliation(EPerceptionType Perception, bool DetectEnemies, bool DetectNeutrals, bool DetectFriendlies) const;

protected:

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	UBehaviorTree* DefaultBehaviorTree = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	UBlackboardData* DefaultBBAsset = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	UAIPerceptionComponent* SightPerception = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	UAIPerceptionComponent* HearingPerception = nullptr;	

	UPROPERTY()
	FAISenseAffiliationFilter DefaultAffilationFilter;

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig = nullptr;

	UPROPERTY()
	UAISenseConfig_Hearing* HearingConfig = nullptr;

public:
	bool IsPlayerInSafeDistance() const;

	bool IsPlayerInSight() const;	
};
