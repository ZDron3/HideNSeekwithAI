// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Base_Projectile.generated.h"

// forward declaration to avoid circular dependencies
class AGameSpawnActor;

UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API ABase_Projectile : public AActor
{
	GENERATED_BODY()

public:
	ABase_Projectile();

	// getters
	FORCEINLINE AGameSpawnActor* GetAttachedActor() const
	{
		return AttachedActor;
	}

	// getters
	FORCEINLINE FName GetNoiseTag() const
	{
		return  NoiseTag;
	}
	

	// setters
	void SetAttachedActor(AGameSpawnActor* const AttachedActorToSet);
	void SetNoiseTag(FName const NoiseTagToSet);
	void SetProjectileStartLocation(FVector ProjectileStartLocationToSet);
	void SetProjectileEndLocation(FVector ProjectileEndLocationToSet);

	UFUNCTION()
	void OnProjectileStopBouncing(const FHitResult& ImpactResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	UBoxComponent* CollisionComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	UProjectileMovementComponent* Projectile = nullptr;

	UPROPERTY()
	AGameSpawnActor* AttachedActor = nullptr;

	const float NOISE_RANGE = 2000.0f;

private:

	FName NoiseTag;
	FVector ProjectileStartLocation;
	FVector ProjectileEndLocation;	

	const FVector DEFAULT_SCALE = FVector(0.2f, 0.2f, 0.2f);	
};


