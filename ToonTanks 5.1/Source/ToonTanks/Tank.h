// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h" //must be included in the header file
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") //create input enhanced component
		class UInputMappingContext* TankMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") //create input action components
		class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		class UInputAction* TurnAction;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float Speed = 250.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float TurnRate = 50.f;

	//void Fire(const FInputActionValue& Value);

	void Movement(const FInputActionValue& Value);

	void Turn(const FInputActionValue& Value);

	APlayerController* TankPlayerController;

};
