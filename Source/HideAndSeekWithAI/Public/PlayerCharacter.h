// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_GameCharacter.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

class AGameSpawnActor;
class AGamePlayerController;

UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API APlayerCharacter : public ABase_GameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// getters
	FORCEINLINE AGameSpawnActor* GetCurrentThrowableItem() const
	{
		return CurrentThrowableItem;
	}

	// setters
	void SetCurrentThrowableItem(AGameSpawnActor* InteractingItemToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter")
	UCameraComponent* Camera = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Control
	void MoveForward(float amount);
	void MoveBack(float amount);
	void MoveRight(float amount);
	void MoveLeft(float amount);
	void Turn(float amount);
	void OnLeftMousePressed();
	void OnLeftMouseReleased();

private:

	
	AGameSpawnActor* CurrentThrowableItem = nullptr;	
	const float BaseTurnRate = 45.0f;

   	const FKey ChargeThrowButton = EKeys::LeftMouseButton;

	bool IsChargingThrow = false;
	float ChargeThrowButtonDownTime = 0.0f;
	float MinChargingThrowTime = 0.0f; // in seconds
	float MaxChargingThrowTime = 2.0f; // in seconds

};
	
