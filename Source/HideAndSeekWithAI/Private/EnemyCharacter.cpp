// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();			
}

void AEnemyCharacter::OnOverlappingHappened(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}
