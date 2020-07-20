// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectSpawnDimensions.generated.h"

class UBillboardComponent;
class UBoxComponent;

UCLASS()
class HIDEANDSEEKWITHAI_API AObjectSpawnDimensions : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectSpawnDimensions(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	/** The spawn area to spawn everything inside. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Area")
		UBoxComponent* Area;

	/** An editor only billboard for easy selection of this component. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Area")
		UBillboardComponent* Icon;

public:
	/** Returns the spawn area component. */
	FORCEINLINE const UBoxComponent* GetArea() const
	{
		return Area;
	}

};
