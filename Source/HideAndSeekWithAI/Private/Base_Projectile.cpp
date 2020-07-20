// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameSpawnActor.h"
#include "Perception/AISense_Hearing.h"

ABase_Projectile::ABase_Projectile()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;	
	CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));	
	CollisionComponent->SetWorldScale3D(DEFAULT_SCALE);
	

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));	
	Projectile->bShouldBounce = true;
	Projectile->Bounciness = 0.3f;
}

void ABase_Projectile::BeginPlay()
{
	Super::BeginPlay();

	if (Projectile)
	{
		Projectile->OnProjectileStop.AddDynamic(this, &ABase_Projectile::OnProjectileStopBouncing);
		FVector TargetProjectileVelocity;
		UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, TargetProjectileVelocity, ProjectileStartLocation, ProjectileEndLocation);
		Projectile->Velocity = TargetProjectileVelocity;
	}
}

void ABase_Projectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AttachedActor)
	{
		UAISense_Hearing::ReportNoiseEvent(this, AttachedActor->GetActorLocation(), 1.0f, GetOwner(), NOISE_RANGE, NoiseTag);
	}
}

void ABase_Projectile::SetNoiseTag(FName const NoiseTagToSet)
{
	NoiseTag = NoiseTagToSet;
}

void ABase_Projectile::SetAttachedActor(AGameSpawnActor* const AttachedActorToSet)
{
	AttachedActor = AttachedActorToSet;
}

void ABase_Projectile::SetProjectileStartLocation(FVector ProjectileStartLocationToSet)
{
	ProjectileStartLocation = ProjectileStartLocationToSet;
}

void ABase_Projectile::SetProjectileEndLocation(FVector ProjectileEndLocationToSet)
{
	ProjectileEndLocation = ProjectileEndLocationToSet;
}

void ABase_Projectile::OnProjectileStopBouncing(const FHitResult& ImpactResult)
{
	Destroy();
}

