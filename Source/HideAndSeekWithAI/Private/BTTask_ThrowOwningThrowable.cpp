// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ThrowOwningThrowable.h"
#include "GameSpawnActor.h"
#include "Base_GameCharacter.h"
#include "GameSpawnActor.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIController.h"

UBTTask_ThrowOwningThrowable::UBTTask_ThrowOwningThrowable()
{
	NodeName = TEXT("ThrowOwningThrowable");
}

EBTNodeResult::Type UBTTask_ThrowOwningThrowable::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABase_GameCharacter* TaskCharacter = Cast<ABase_GameCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (TaskCharacter)
	{
		AGameSpawnActor* ObjectToThrow = TaskCharacter->GetCurrentItemInHand();

		if (ObjectToThrow && ObjectToThrow->IsA(AGameSpawnActor::StaticClass()))
		{
			ObjectToThrow->Throw(OwnerComp.GetAIOwner()->GetPawn(), 0.0f, FName(TEXT("None")));
		}
	}
	
	return EBTNodeResult::Succeeded;
}

