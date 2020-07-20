// Fill out your copyright notice in the Description page of Project Settings.
#include "ObjectSpawnDimensions.h"
#include <Components/BillboardComponent.h>
#include <Components/BoxComponent.h>
#include <Engine/Texture2D.h>
#include <UObject/ConstructorHelpers.h>

// Sets default values

AObjectSpawnDimensions::AObjectSpawnDimensions(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	Area = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(
		this, TEXT("Area"));
	Area->SetBoxExtent(FVector(5995.0f, 1495.0f, 1.0f), true);
	Area->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Area->SetCollisionResponseToAllChannels(ECR_Ignore);
	Area->SetCanEverAffectNavigation(false);

	SetRootComponent(Area);

	Icon = ObjectInitializer.CreateDefaultSubobject<UBillboardComponent>(
		this, TEXT("Icon"));
	Icon->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AObjectSpawnDimensions::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectSpawnDimensions::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


