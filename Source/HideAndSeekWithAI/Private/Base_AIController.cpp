// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_AIController.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"

void ABase_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABase_AIController::SetDetectionByAffiliation(EPerceptionType Perception, bool DetectEnemies, bool DetectNeutrals, bool DetectFriendlies) const
{
	switch (Perception)
	{
	case EPerceptionType::SightPerception:

		if (SightConfig && SightPerception)
		{
			SightConfig->DetectionByAffiliation.bDetectEnemies = DetectEnemies;
			SightConfig->DetectionByAffiliation.bDetectNeutrals = DetectNeutrals;
			SightConfig->DetectionByAffiliation.bDetectFriendlies = DetectFriendlies;
			SightPerception->RequestStimuliListenerUpdate();
		}
		break;

	case EPerceptionType::HearingPerception:
		
		if (HearingConfig && HearingPerception)
		{
			HearingConfig->DetectionByAffiliation.bDetectEnemies = DetectEnemies;
			HearingConfig->DetectionByAffiliation.bDetectNeutrals = DetectNeutrals;
			HearingConfig->DetectionByAffiliation.bDetectFriendlies = DetectFriendlies;
			HearingPerception->RequestStimuliListenerUpdate();
		}		
		break;		
	}	
}


bool ABase_AIController::IsPlayerInSafeDistance() const
{
	APlayerCharacter* PlayerCharacter =
		Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!PlayerCharacter)
	{
		return false;
	}

	AEnemyCharacter* AICharacter = Cast<AEnemyCharacter>(GetCharacter());
	checkf(AICharacter, TEXT("FATAL: not HideAndSeekWithAI's AI character!"));

	const float MaxSightDistance = SightConfig->SightRadius;
	const FVector ViewLocation(AICharacter->GetPawnViewLocation());
	const FVector PlayerLocation(PlayerCharacter->GetActorLocation());
	const FVector PlayerDirection(PlayerLocation - ViewLocation);
	const float PlayerDistance = PlayerDirection.Size();

	return (PlayerDistance > MaxSightDistance);
}


bool ABase_AIController::IsPlayerInSight() const
{

	APlayerCharacter* PlayerCharacter =	Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	checkf(PlayerCharacter, TEXT("FATAL: not HideAndSeekWithAI's player character!"));

	AEnemyCharacter* AICharacter = Cast<AEnemyCharacter>(GetCharacter());
	checkf(AICharacter, TEXT("FATAL: not HideAndSeekWithAI's AI character!"));

	const float MaxSightDistance = SightConfig->SightRadius;
	const FVector ViewLocation(AICharacter->GetPawnViewLocation());
	const FVector PlayerLocation(PlayerCharacter->GetActorLocation());
	const FVector PlayerDirection(PlayerLocation - ViewLocation);
	const float PlayerDistance = PlayerDirection.Size();

	if (PlayerDistance > MaxSightDistance)
	{
		return false;
	}

	const FVector ViewDirection(AICharacter->GetViewRotation().Vector());
	const FVector ViewDirectionNormal(ViewDirection.GetSafeNormal());
	const FVector PlayerDirectionNormal = PlayerDirection.GetSafeNormal();

	const float DotProduct =
		FVector::DotProduct(ViewDirectionNormal, PlayerDirectionNormal);
	bool bLookingAtPlayerDirection = DotProduct > 0.0f;

	if (!bLookingAtPlayerDirection)
	{
		return false;
	}

	const float PeripheralVisionAngle = SightConfig->PeripheralVisionAngleDegrees;
	float MinViewingAngle = 90.0f - PeripheralVisionAngle;
	float MaxViewingAngle = 90.0f + PeripheralVisionAngle;

	const float CurrentViewingAngle = FMath::RadiansToDegrees(
		FMath::Acos(
			FVector::DotProduct(ViewDirectionNormal,
				PlayerDirectionNormal)
		)
	);

	if (CurrentViewingAngle <= MinViewingAngle
		&& CurrentViewingAngle >= MaxViewingAngle) {
		return false;
	}

	FCollisionQueryParams TraceParams(TEXT("PlayerTrace"), true, this);
	TraceParams.bIgnoreTouches = false;
	TraceParams.bReturnPhysicalMaterial = false;

	FHitResult HitResult(ForceInit);
	GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, PlayerLocation,
		ECollisionChannel::ECC_Visibility, TraceParams);

	if (!Cast<APawn>(HitResult.Actor))
	{
		return false;
	}

	return true;
}
