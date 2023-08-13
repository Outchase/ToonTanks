// Fill out your copyright notice in the Description page of Project Settings.

#pragma once //iclude guards, prevent from being included multiple times in a single file

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:

	void RotateTurret(FVector LookAtTarget); //tower and tank can rotate

	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CapsuleComp; //foward declaration only create pointer

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMeshComp; //UStaticMeshComponent is included by default bcs actors. Pawns are actors

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSPComp;

	//visible anywhere, read only
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Amogus is real", meta = (AllowPrivateAccess = "true"))
		int32 VisibleAnywhere = 12;

	//visible anywhere, read/write It's just to learn so I did not add it to UML
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Amogus is real", meta = (AllowPrivateAccess = "true"))
		int32 EditAnywhere = 22;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
		class UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
		class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
		TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

};
