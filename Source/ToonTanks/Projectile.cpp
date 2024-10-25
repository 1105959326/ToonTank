// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

class USoundBase;

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = ProjectileMesh;

	TailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Tail"));
	TailParticle->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	
	
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;
}

// Called when the game starts or when spawned
void  AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("OnHit"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}

	AController* controller = MyOwner->GetInstigatorController();

	auto DamageType = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner) 
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, controller, this, DamageType);
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		if (HitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
		}
		Destroy();
	}

	
}

