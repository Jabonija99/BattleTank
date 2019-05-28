// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;
	
private:
	//Begin moving barrel towards the angle needed to 
	//intersect the crosshair with the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector &HitLocation) const;
};
