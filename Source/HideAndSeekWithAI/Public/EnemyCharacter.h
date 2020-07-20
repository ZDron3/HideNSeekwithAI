// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_GameCharacter.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class HIDEANDSEEKWITHAI_API AEnemyCharacter : public ABase_GameCharacter
{
	GENERATED_BODY()

public:
	

protected:	

	virtual void BeginPlay() override;	
	virtual void OnOverlappingHappened(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
