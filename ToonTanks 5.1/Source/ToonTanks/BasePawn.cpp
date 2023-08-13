// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"


// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider")); //constructed a capsule component
	RootComponent = CapsuleComp; //made capsule component as root component

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMeshComp->SetupAttachment(CapsuleComp); //attach base mesh to capsule comp

	TurretMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMeshComp->SetupAttachment(BaseMeshComp);//attach turret mesh to base mesh comp

	ProjectileSPComp = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSPComp->SetupAttachment(TurretMeshComp);

}

void ABasePawn::HandleDestruction() {
	// todo: visual/SFX 
	if (DeathParticle) {
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			DeathParticle,
			GetActorLocation(),
			GetActorRotation()
		);

		if (DeathSound) {
			UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
		}
		if (DeathCameraShakeClass) {
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
		}
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget) {
	FVector ToTarget = LookAtTarget - TurretMeshComp->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	TurretMeshComp->SetWorldRotation(
		FMath::RInterpTo(
			TurretMeshComp->GetComponentRotation(),
			LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this),
			5.f)
	);
}

void ABasePawn::Fire() {
	FVector ProjectileSPLocation = ProjectileSPComp->GetComponentLocation();
	FRotator ProjectileSPRotation = ProjectileSPComp->GetComponentRotation();

	//auto allows the compile to figure out the thype to assign
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSPLocation, ProjectileSPRotation);
	Projectile->SetOwner(this);

}



