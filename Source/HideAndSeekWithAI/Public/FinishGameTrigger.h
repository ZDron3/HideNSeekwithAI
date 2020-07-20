// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_GameTrigger.h"
#include "FinishGameTrigger.generated.h"

UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API AFinishGameTrigger : public ABase_GameTrigger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinishGameTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlappingHappened(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
