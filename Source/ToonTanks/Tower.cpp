// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"


void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
	CheckFireCondition();

}
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank)
	{
		if (InFIreRange()) RotateTurrent(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition()
{
	if (Tank == nullptr) 
	{
		return;
	}

	if (InFIreRange() && Tank->bAlive) Fire();
}

bool ATower::InFIreRange()
{
	float Dist = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

	if (Tank && Dist < FireRange)
	{
		return true;
	}
	return false;
}