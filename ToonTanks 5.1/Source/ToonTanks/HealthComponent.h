// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) //BlueprintSpawnableComponent )allow to add this comp in blueprint
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		float MaxHealth = 100.f;
		float CurrentHealth = 0.f;


	//DamageActor = actor taking the damage
	//UDamageType= Unreal has a concept damage types
	//Instigator= responsible for the damage
	UFUNCTION() //create a callback function
	void DamageTaken(AActor* DamageActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);

	class AToonTanksGameMode* ToonTanksGameMode;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
