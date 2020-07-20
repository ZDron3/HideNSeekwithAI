// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "AIRecognizable.h"
#include "GenericTeamAgentInterface.h"
#include "Engine/DataTable.h"
#include "Base_PlayerController.h"
#include "Base_AIController.h"
#include "Base_GameCharacter.generated.h"

class AGameSpawnActor;


UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API ABase_GameCharacter : public ACharacter, public IGenericTeamAgentInterface, public IAIRecognizable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABase_GameCharacter();
	
    USceneComponent* GetCharacterVisual() const; 

    FName GetHandSocketName() const;

	UFUNCTION(BlueprintCallable, Category = "AIRecognizable")
		AGameSpawnActor* GetCurrentItemInHand() const;
	

	// interfaces
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AIRecognizable")
	EAITeam GetAITeam();
	EAITeam GetAITeam_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable,  Category = "AIRecognizable")
	void SetAITeam(const EAITeam AITeamToSet);
	void SetAITeam_Implementation(const EAITeam AITeamToSet);
	
	void SetCurrentItemInHand(AGameSpawnActor* ItemToSet);
	FTransform GetHandTransform() const;	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnOverlappingHappened(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Character Components")
	USceneComponent* CharacterVisual = nullptr;
	
	const FName HandSocketName = TEXT("Hand");	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Components")
	EAITeam Team = EAITeam::AIEnemies;	


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Components")
	    int TotalAICharacters = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Components")
		float DefaultWalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Components")
		float MinDistanceToPickUItems = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Components")
		float MinThrowDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Components")
		float MaxThrowDistance = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Components")
		float ThrowChargeTime = 2.0f;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Character Components")
		AGameSpawnActor* CurrentItemInHand = nullptr;

};
