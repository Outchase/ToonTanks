// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UStaticMeshComponent* ProjectileMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UProjectileMovementComponent* ProjectileMoveComp;

	UPROPERTY(VisibleAnywhere, Category="Combat")
	class UParticleSystemComponent* PaticleSystemComp;

	//callback funtion for the HitEvent
	//HitComp = projectile mesh component hitting things
	//OtherActor = the actor that got hit
	//Other Comp = the component that got hit
	//NormalImpulse = direction and magnitude of the impulse physics
	//Hit Result = contains more information about the Hit
	//Ufunction bcs we are binding this to a delegate
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category="Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
