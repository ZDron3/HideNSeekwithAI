// Fill out your copyright notice in the Description page of Project Settings.


#include "HideNSeekGameInstance.h"
#include <Kismet/GameplayStatics.h>


UHideNSeekGameInstance::UHideNSeekGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UHideNSeekGameInstance::RestartCurrentLevel()
{
	LoadLevel(FName(*(GetWorld()->GetName())), true);
}

void UHideNSeekGameInstance::LoadLevel(	const FName& Name,	bool bAbsolute, FString Options)
{
	UGameplayStatics::OpenLevel((UObject*)this, Name,
		bAbsolute, Options);
}