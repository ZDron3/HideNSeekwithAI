// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Base_GameTrigger.generated.h"

UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API ABase_GameTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_GameTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	// virtual function for overriding in subclasses
	UFUNCTION()
	virtual void OnOverlappingHappened(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Trigger")
	USceneComponent* DefaultSceneRoot = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Trigger")
	UBoxComponent* Box = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Trigger")
	UStaticMeshComponent* StaticMesh = nullptr;	

};

