// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishGameTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "GameFunctionLibrary.h"

// Sets default values
AFinishGameTrigger::AFinishGameTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AFinishGameTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinishGameTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinishGameTrigger::OnOverlappingHappened(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	UGameFunctionLibrary::StopGame(this);	
}

