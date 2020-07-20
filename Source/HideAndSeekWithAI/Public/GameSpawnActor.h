// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameSpawnActor.generated.h"

UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API AGameSpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameSpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GameActor")
	USceneComponent* DefaultSceneRoot = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GameActor")
	USceneComponent* GameActorVisual = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Throwable")
		void PickUp(APawn* PawnInstigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Throwable")
		void Throw(APawn* PawnInstigator, float DistanceToThrow, FName NoiseTag);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Throwable")
		void GetSpawnLocation(FVector& OutSpawnLocation) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Throwable")
		bool IsThrowableAvailable() const;



protected:
	FVector SpawnLocation;

	bool IsAvailable = false;

public:
	UPROPERTY(EditAnywhere, Category = "ObjectDetails")
		uint32 NumberToSpawn;

	UPROPERTY(EditAnywhere, Category = "ObjectDetails")
		bool RandomRotation = false;



};
