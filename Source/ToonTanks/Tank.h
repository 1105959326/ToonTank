// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetPlayerController();

	bool bAlive = true;
protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 200.f;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 10.f;

	void Move(float Value);

	void Turn(float Value);

	APlayerController* TankPlayerController;
};
