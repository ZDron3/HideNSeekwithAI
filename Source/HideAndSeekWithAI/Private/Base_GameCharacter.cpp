// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_GameCharacter.h"
#include "Perception/AISense_Sight.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABase_GameCharacter::ABase_GameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CharacterVisual = CreateDefaultSubobject<USceneComponent>("CharacterRepresentation");
	CharacterVisual->SetupAttachment(RootComponent);

}

EAITeam ABase_GameCharacter::GetAITeam_Implementation()
{
	switch (GetAITeamId())
	{
	case 0:
		return EAITeam::Players;
		break;

	case 1:
		return EAITeam::AIEnemies;
		break;

	case 255:
		return EAITeam::Neutrals;
		break;	
	}
	
	return EAITeam();
}

void ABase_GameCharacter::SetAITeam_Implementation(const EAITeam AITeamToSet)
{	
	switch (AITeamToSet)
	{
	case EAITeam::Players:
		AITeamId = FGenericTeamId(0);		
		break;

	case EAITeam::AIEnemies:
		AITeamId = FGenericTeamId(1);
		break;

	case EAITeam::Neutrals:		 
		AITeamId = FGenericTeamId(255);; // 255 is neutral per ue
		break;
	}
	
	UAIPerceptionSystem* MyPerceptionSystem = UAIPerceptionSystem::GetCurrent(this);
	if (MyPerceptionSystem)
	{
		MyPerceptionSystem->UnregisterSource(*this);
		MyPerceptionSystem->RegisterSource<UAISense_Sight>(*this);
	}
	
}

void ABase_GameCharacter::SetCurrentItemInHand(AGameSpawnActor* ItemToSet)
{
	CurrentItemInHand = ItemToSet;	
}

FTransform ABase_GameCharacter::GetHandTransform() const
{
	TArray<USceneComponent*> ChildrenComponents;
	CharacterVisual->GetChildrenComponents(true, ChildrenComponents);

	for (USceneComponent* Child : ChildrenComponents)
	{
		if (Child->DoesSocketExist(HandSocketName))
		{
			return Child->GetSocketTransform(HandSocketName);
		}
	}

	return FTransform();
}

// Called when the game starts or when spawned
void ABase_GameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;	
	TArray<USceneComponent*> ChildrenComponents;
	CharacterVisual->GetChildrenComponents(true, ChildrenComponents);

	for (USceneComponent* Child : ChildrenComponents)
	{
		if (UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Child))
		{
			StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABase_GameCharacter::OnOverlappingHappened);
		}
	}
	
	
}

// Called every frame
void ABase_GameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABase_GameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABase_GameCharacter::OnOverlappingHappened(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

AGameSpawnActor* ABase_GameCharacter::GetCurrentItemInHand() const
{
	return  CurrentItemInHand;
}

 USceneComponent*  ABase_GameCharacter::GetCharacterVisual() const
{
	return CharacterVisual;
}

FName  ABase_GameCharacter::GetHandSocketName() const
{
	return  HandSocketName;
}