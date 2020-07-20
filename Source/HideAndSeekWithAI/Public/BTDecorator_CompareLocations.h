// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CompareLocations.generated.h"

UENUM(BlueprintType)
enum class ELocationsComparisionOperator : uint8
{
	EqualTo 	UMETA(DisplayName = "EqualTo"),
	NotEqualTo 	UMETA(DisplayName = "NotEqualTo"),	
};

UCLASS()
class HIDEANDSEEKWITHAI_API UBTDecorator_CompareLocations : public UBTDecorator
{
	GENERATED_BODY()

public:

	UBTDecorator_CompareLocations();
	
protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	bool CompareLocations(UBehaviorTreeComponent& OwnerComp) const;

	UPROPERTY(EditAnywhere, Category = "Data")
	ELocationsComparisionOperator LocationsComparisionOp = ELocationsComparisionOperator::EqualTo;

	UPROPERTY(EditAnywhere, Category = "Data")
	FBlackboardKeySelector LocationA;

	UPROPERTY(EditAnywhere, Category = "Data")
	FBlackboardKeySelector LocationB;
	
};


