// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"
//Depends on movement component via pathfinding system


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//Subscribe our local method to tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	auto PossessedTank = GetPawn();
	if (!ensure(PossessedTank)) { return; }
	PossessedTank->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!(PlayerTank && AimingComponent && ControlledTank)) { return; }

	//Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm

	//Aim towards the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// if aiming or locked
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		AimingComponent->Fire(); //TODO limit firing rate
	}
	
}

