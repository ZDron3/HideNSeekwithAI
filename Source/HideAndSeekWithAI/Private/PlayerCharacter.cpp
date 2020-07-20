// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameSpawnActor.h"
#include "GameFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Base_PlayerController.h" 
#include "GamePlayerController.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);

	SetGenericTeamId(FGenericTeamId(UGameFunctionLibrary::JoinGameTeam(ETeam::Players)));

}

void APlayerCharacter::SetCurrentThrowableItem(AGameSpawnActor* InteractingItemToSet)
{
	CurrentThrowableItem = InteractingItemToSet;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();	

	TArray<USceneComponent*> ChildrenComponents;
	CharacterVisual->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* Child : ChildrenComponents)
	{
		if (Child->DoesSocketExist("Head"))
		{
			Camera->AttachToComponent(Child, FAttachmentTransformRules::KeepRelativeTransform, "Head");
			break;
		}
	}	

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChargeThrowButtonDownTime = Cast<ABase_PlayerController>(GetController())->GetInputKeyTimeDown(ChargeThrowButton); 
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveBack", this, &APlayerCharacter::MoveBack);
		PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
		PlayerInputComponent->BindAxis("MoveLeft", this, &APlayerCharacter::MoveLeft);
		PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
		InputComponent->BindAction("LeftMouse", EInputEvent::IE_Pressed, this, &APlayerCharacter::OnLeftMousePressed);
		InputComponent->BindAction("LeftMouse", EInputEvent::IE_Released, this, &APlayerCharacter::OnLeftMouseReleased);
		
		
	}
	


}

void APlayerCharacter::MoveForward(float amount)
{
	AddMovementInput(GetActorForwardVector(), amount);
}

void APlayerCharacter::MoveBack(float amount)
{
	AddMovementInput(-GetActorForwardVector(), amount);
}

void APlayerCharacter::MoveRight(float amount)
{
	AddMovementInput(GetActorRightVector(), amount);
}

void APlayerCharacter::MoveLeft(float amount)
{
	AddMovementInput(-GetActorRightVector(), amount);
}

void APlayerCharacter::Turn(float amount)
{
	AddControllerYawInput(amount);	
}


void APlayerCharacter::OnLeftMousePressed()
{
	if (!GetCurrentItemInHand())
	{

		AGamePlayerController* PC = Cast<AGamePlayerController>(GetController());
		FHitResult HitResult;
		const bool IsHit = PC->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);

		if (IsHit)
		{
			const bool DoesImplementInterface = HitResult.Actor->IsA(AGameSpawnActor::StaticClass());

			if (DoesImplementInterface)
			{
				Cast<AGameSpawnActor>(HitResult.Actor)->PickUp(this);
			}
		}
	}

	else
	{
		IsChargingThrow = true;
	}
}

void APlayerCharacter::OnLeftMouseReleased()
{
	if (IsChargingThrow)
	{
		IsChargingThrow = false;
		AGameSpawnActor* ItemToThrow = GetCurrentItemInHand();
		const float ThrowDistance = UKismetMathLibrary::MapRangeClamped(ChargeThrowButtonDownTime, MinChargingThrowTime, MaxChargingThrowTime, MinThrowDistance, MaxThrowDistance);
		const FVector Velocity = FVector(1.0f, 0.0f, 0.5);

		AGameSpawnActor* ItemToThrowByControlledPawn = GetCurrentItemInHand();

		if (ItemToThrowByControlledPawn)
		{
			ItemToThrowByControlledPawn->Throw(this, ThrowDistance, TEXT("ItemFallen"));
		}

	}
}
