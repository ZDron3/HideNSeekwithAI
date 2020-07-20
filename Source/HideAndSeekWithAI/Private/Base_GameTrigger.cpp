// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_GameTrigger.h"

// Sets default values
ABase_GameTrigger::ABase_GameTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);	
	Box->SetCollisionProfileName(TEXT("PlayerTrigger"));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);	
	StaticMesh->SetCollisionProfileName(TEXT("BlockAll"));
}

// Called when the game starts or when spawned
void ABase_GameTrigger::BeginPlay()
{
	Super::BeginPlay();

	// Bind to overlapping events
	Box->OnComponentBeginOverlap.AddDynamic(this, &ABase_GameTrigger::OnOverlappingHappened);
	
}

// Called every frame
void ABase_GameTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABase_GameTrigger::OnOverlappingHappened(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

