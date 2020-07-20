// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSpawnActor.h"

// Sets default values
AGameSpawnActor::AGameSpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	GameActorVisual = CreateDefaultSubobject<USceneComponent>("GameActorVisual");
	GameActorVisual->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);	
}

// Called when the game starts or when spawned
void AGameSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameSpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void  AGameSpawnActor::PickUp_Implementation(APawn* PawnInstigator)
{

}

void  AGameSpawnActor::Throw_Implementation(APawn* PawnInstigator, float DistanceToThrow, FName NoiseTag)
{

}

void  AGameSpawnActor::GetSpawnLocation_Implementation(FVector& OutSpawnLocation) const
{

}

bool  AGameSpawnActor::IsThrowableAvailable_Implementation() const
{
	return false;
}

