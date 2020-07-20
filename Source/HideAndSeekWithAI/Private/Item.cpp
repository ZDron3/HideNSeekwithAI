// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Base_Projectile.h"
#include "Base_GameCharacter.h"
#include "Kismet/GameplayStatics.h"

void AItem::BeginPlay()
{
	Super::BeginPlay();

	// if the game will implement Save/Load system, SpawnLocation will be read from a file on Load
	SpawnLocation = GetActorLocation();
}

void AItem::PickUp_Implementation(APawn* PawnInstigator)
{

	if (!IsThrowableAvailable()) // We can pick up if only no one has already picked it up
	{
		ABase_GameCharacter* Character = Cast<ABase_GameCharacter>(PawnInstigator);
		const bool IsAtAllowedDistance = Character->GetDistanceTo(this) <= Character->MinDistanceToPickUItems;

		if (IsAtAllowedDistance && Character)
		{
			SetActorEnableCollision(false);
			IsAvailable = true;
			SetActorLocationAndRotation(Character->GetHandTransform().GetLocation(), Character->GetHandTransform().GetRotation());
			AttachToComponent(Character->GetCharacterVisual(), FAttachmentTransformRules::KeepWorldTransform, Character->GetHandSocketName());
			Character->SetCurrentItemInHand(this);
		}
	}	
}

void AItem::Throw_Implementation(APawn* PawnInstigator, float DistanceToThrow, FName NoiseTag)
{
	ABase_GameCharacter* Character = Cast<ABase_GameCharacter>(PawnInstigator);

	if (AGameSpawnActor* CurrentItemInHand = Character->GetCurrentItemInHand())
	{
		CurrentItemInHand->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		UWorld* World = Character->GetWorld();
		if (World)
		{			
			ABase_Projectile* Projectile = World->SpawnActorDeferred<ABase_Projectile>(ABase_Projectile::StaticClass(), FTransform(CurrentItemInHand->GetActorLocation()), CurrentItemInHand, Character);

			if (Projectile)
			{
				// For projectile calculations we will use the location of the character (not the hand)
				// to minimize the error of the SuggestProjectileVelocity_CustomArc method
				Projectile->SetProjectileStartLocation(Character->GetActorLocation());
				Projectile->SetProjectileEndLocation((Character->GetActorForwardVector() * DistanceToThrow) + Character->GetActorLocation());
				Projectile->SetAttachedActor(this);
				Projectile->SetNoiseTag(NoiseTag);
				UGameplayStatics::FinishSpawningActor(Projectile, FTransform(CurrentItemInHand->GetActorRotation(), CurrentItemInHand->GetActorLocation()));
				CurrentItemInHand->AttachToActor(Projectile, FAttachmentTransformRules::KeepWorldTransform);
				Character->SetCurrentItemInHand(nullptr);
				SetActorEnableCollision(true);
				IsAvailable = false;
			}
		}
	}
}

void AItem::GetSpawnLocation_Implementation(FVector& OutSpawnLocation) const
{
	OutSpawnLocation = SpawnLocation;
}

 bool AItem::IsThrowableAvailable_Implementation() const
{
	return IsAvailable;
}

