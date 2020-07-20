// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_AIController.h"
#include "EnemyAIController.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle 	    UMETA(DisplayName = "Idle"),
	Distracted 	UMETA(DisplayName = "Distracted"),
	Aggressive 	UMETA(DisplayName = "Aggressive"),
};

UENUM(BlueprintType)
enum class EAISubState : uint8
{
	Idle 	    UMETA(DisplayName = "Idle"),
	TargetLost 	UMETA(DisplayName = "TargetLost"),	
};

UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API AEnemyAIController : public ABase_AIController
{
	GENERATED_BODY()

		AEnemyAIController();

public:
	
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	UFUNCTION()
	void OnTargetSensedByEyes(AActor* SensedActor, FAIStimulus Stimulus);
	UFUNCTION()
	void OnTargetSensedByEars(AActor* SensedActor, FAIStimulus Stimulus);


protected:

	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;

private:

	float FOV = 70.0f;
	float SightDistance = 20;	
};
