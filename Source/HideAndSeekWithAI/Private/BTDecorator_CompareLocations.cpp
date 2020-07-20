// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CompareLocations.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIController.h"
#include "Math/Vector.h"

UBTDecorator_CompareLocations::UBTDecorator_CompareLocations()
{
	NodeName = TEXT("CompareLocations");
	bNotifyTick = true;
	FlowAbortMode = EBTFlowAbortMode::None;

	// Filter what type of value a user can select for a FBlackboardKeySelector
	LocationA.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_CompareLocations, LocationA));
	LocationA.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_CompareLocations, LocationA), UObject::StaticClass());
	LocationB.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_CompareLocations, LocationB));
	LocationB.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_CompareLocations, LocationB), UObject::StaticClass());
	
}

bool UBTDecorator_CompareLocations::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	return CompareLocations(OwnerComp);
}

void UBTDecorator_CompareLocations::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const bool IsEqual = CompareLocations(OwnerComp);

	if (IsEqual)
	{
		OwnerComp.RequestExecution(this);
	}
}

bool UBTDecorator_CompareLocations::CompareLocations(UBehaviorTreeComponent& OwnerComp) const
{
	FVector ComparingLocationA;
	FVector ComparingLocationB;
	const float Tolerance = 95.0f;
	
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		UObject* CompareObjectA = BlackboardComp->GetValueAsObject(LocationA.SelectedKeyName);
		if (CompareObjectA)
		{
			AActor* CompareActorALocation = Cast<AActor>(CompareObjectA);
			if (CompareActorALocation)
			{
				ComparingLocationA = CompareActorALocation->GetActorLocation();
			}
		}

		else
		{
			ComparingLocationA = BlackboardComp->GetValueAsVector(LocationA.SelectedKeyName);
		}

		UObject* CompareObjectB = BlackboardComp->GetValueAsObject(LocationB.SelectedKeyName);
		if (CompareObjectB)
		{
			AActor* CompareActorBLocation = Cast<AActor>(CompareObjectB);
			if (CompareActorBLocation)
			{
				ComparingLocationB = CompareActorBLocation->GetActorLocation();
			}
		}

		else
		{
			ComparingLocationB = BlackboardComp->GetValueAsVector(LocationB.SelectedKeyName);
		}

		if (LocationsComparisionOp == ELocationsComparisionOperator::EqualTo)
		{
			
			return ComparingLocationA.Equals(ComparingLocationB, Tolerance);
		}
		else
		{			
			return !ComparingLocationA.Equals(ComparingLocationB, Tolerance);
		}
	}

	return false;
}

void UBTDecorator_CompareLocations::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		LocationA.ResolveSelectedKey(*BBAsset);
		LocationB.ResolveSelectedKey(*BBAsset);
	}
}

EBlackboardNotificationResult UBTDecorator_CompareLocations::OnBlackboardKeyValueChange(
	const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID)
{
	UBehaviorTreeComponent* BehaviorComp = static_cast<UBehaviorTreeComponent*>(Blackboard.GetBrainComponent());
	if (BehaviorComp == nullptr)
	{
		return EBlackboardNotificationResult::RemoveObserver;
	}
	else if (LocationA.GetSelectedKeyID() == ChangedKeyID || LocationB.GetSelectedKeyID() == ChangedKeyID)
	{
		BehaviorComp->RequestExecution(this);
	}

	return EBlackboardNotificationResult::ContinueObserving;
}

void UBTDecorator_CompareLocations::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		BlackboardComp->RegisterObserver(LocationA.GetSelectedKeyID(), this, FOnBlackboardChangeNotification::CreateUObject(this, &UBTDecorator_CompareLocations::OnBlackboardKeyValueChange));
		BlackboardComp->RegisterObserver(LocationB.GetSelectedKeyID(), this, FOnBlackboardChangeNotification::CreateUObject(this, &UBTDecorator_CompareLocations::OnBlackboardKeyValueChange));
	}
}

void UBTDecorator_CompareLocations::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		BlackboardComp->UnregisterObserversFrom(this);
	}
}
