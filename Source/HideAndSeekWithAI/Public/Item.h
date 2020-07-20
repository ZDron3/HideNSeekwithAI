// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSpawnActor.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API AItem : public AGameSpawnActor
{
	GENERATED_BODY()

public:
	
	void PickUp_Implementation(APawn* PawnInstigator);

	void Throw_Implementation(APawn* PawnInstigator, float DistanceToThrow, FName NoiseTag);	

	void GetSpawnLocation_Implementation(FVector& OutSpawnLocation) const;

	bool IsThrowableAvailable_Implementation() const;

protected:

	virtual void BeginPlay() override;
	
	
	
};
