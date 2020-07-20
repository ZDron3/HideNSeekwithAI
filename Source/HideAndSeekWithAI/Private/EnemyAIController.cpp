// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFunctionLibrary.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

AEnemyAIController::AEnemyAIController()
{
	SightPerception = CreateDefaultSubobject<UAIPerceptionComponent>("SightPerception");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	
	SightConfig->SightRadius = 2000;
	SightConfig->LoseSightRadius = 2000;
	SightConfig->PeripheralVisionAngleDegrees = 35.0f;
	SightPerception->ConfigureSense(*SightConfig);

	HearingPerception = CreateDefaultSubobject<UAIPerceptionComponent>("HearingPerception");
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>("HearingConfig");

	HearingConfig->HearingRange = 1500;
	HearingConfig->SetMaxAge(3.0f);
	HearingPerception->ConfigureSense(*HearingConfig);

	// Setting AI team Index
	SetGenericTeamId(FGenericTeamId(UGameFunctionLibrary::JoinGameTeam(ETeam::AIEnemies)));
	
	

	// Enemies will detect only a player 
	SetDetectionByAffiliation(EPerceptionType::SightPerception, true, false, false);
	
}

ETeamAttitude::Type AEnemyAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other)) 
	{
		// Checking if a controller of other pawn is "Teamable" and if so, we extract its TeamID
		// and compare with AI Controller's TeamID to detect if it is Enemies/Friends/Neutrals
		if (OtherPawn->GetController()->GetClass()->ImplementsInterface(UGenericTeamAgentInterface::StaticClass()))
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
	}

	// if a detected actor does not have UGenericTeamAgentInterface AI treats it as Neutral
	return ETeamAttitude::Neutral;
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);	

	// Launch Behavior Tree
	if (DefaultBBAsset && DefaultBehaviorTree)
	{
		UseBlackboard(DefaultBBAsset, Blackboard);
		RunBehaviorTree(DefaultBehaviorTree);
		Blackboard->SetValueAsVector(FName(TEXT("SpawnLocation")), GetPawn()->GetActorLocation());
		Blackboard->SetValueAsRotator(FName(TEXT("SpawnRotation")), GetPawn()->GetActorRotation());
		
		SightPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetSensedByEyes);
		HearingPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetSensedByEars);	
	}	
}

void AEnemyAIController::OnTargetSensedByEyes(AActor* SensedActor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		// If AI Sensed the player
		// Set Target Actor
		Blackboard->SetValueAsObject(FName(TEXT("TargetActor")), SensedActor);

		// Set AI SubState
		Blackboard->SetValueAsEnum(FName(TEXT("AISubState")), static_cast<uint8>(EAISubState::Idle));
		
		// Set AI State As Aggressive
		Blackboard->SetValueAsEnum(FName(TEXT("AIState")), static_cast<uint8>(EAIState::Aggressive));
	}

	else
	{
		// If AI lost the player		

		// Remember the last location of the lost player
		Blackboard->SetValueAsVector(FName(TEXT("MoveToLocation")), SensedActor->GetActorLocation());		

		// Clear Target Actor because AI doesn't have Target Actor anymore
		Blackboard->ClearValue(FName(TEXT("TargetActor")));

		// Set AI SubState to TargetLost to switch behavior
		Blackboard->SetValueAsEnum(FName(TEXT("AISubState")), static_cast<uint8>(EAISubState::TargetLost));
	}
	
}

void AEnemyAIController::OnTargetSensedByEars(AActor* SensedActor, FAIStimulus Stimulus)
{
	if (Stimulus.Tag == "ItemFallen")
	{
		// Set Stimulus Location to go to there
		Blackboard->SetValueAsVector(FName(TEXT("MoveToLocation")), Stimulus.StimulusLocation);

		// Set the source object (that was heard) into blackboard to use this data later
		Blackboard->SetValueAsObject(FName(TEXT("DistractingSource")), SensedActor);

		// Set AI State as Distracted
		Blackboard->SetValueAsEnum(FName(TEXT("AIState")), static_cast<uint8>(EAIState::Distracted));
	}
	
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APawn* ControlledPawn = GetPawn())
	{		

		const FVector HeightOffset = FVector(0.0f, 0.0f, 90.0f);		
		DrawDebugCone(ControlledPawn->GetWorld(),
			ControlledPawn->GetActorLocation() - HeightOffset,
			ControlledPawn->GetActorForwardVector(),
			SightConfig->SightRadius, FMath::DegreesToRadians(SightConfig->PeripheralVisionAngleDegrees), 0.0f, 20.0f,
			FColor::Red, false, 0.1f, 0, 10.0f);
	}	
	
}
