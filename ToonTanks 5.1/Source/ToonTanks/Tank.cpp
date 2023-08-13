// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h" //add module to the build file (Projectname.Build.cs)
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank() {

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);


	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

}

//pass SetupPlayerInputComponent to UEnhancedInputComponent //new input enhance method
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire); // bind fire callback to fire action
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ATank::Movement); // bind Movement callback to Movement action
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::Turn); // bind Turn callback to Turn action
	}
}

void ATank::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (TankPlayerController) {
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);

		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction() {
	Super::HandleDestruction();
	SetActorHiddenInGame(true); //hide actor then destoy to have the camera
	SetActorTickEnabled(false);
	bAlive = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(TankMappingContext, 0);
		}
	}

	TankPlayerController = Cast<APlayerController>(GetController()); //pass the type to cast to "<>". Pass the pointer to cast into "()"


}

/*void ATank::Fire(const FInputActionValue& Value) {
	const bool CurrentValue = Value.Get<bool>();
	if (CurrentValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Fire triggered"));
	}
}*/

void ATank::Movement(const FInputActionValue& Value) {
	const float DirectionValue = Value.Get<float>();

	if (Controller && (DirectionValue != 0.f))
	{

		FVector DeltaLocation = FVector::ZeroVector;
		// X = Value * DeltaTime * Speed
		DeltaLocation.X = DirectionValue * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);

		AddActorLocalOffset(DeltaLocation, true);

		//FVector Forward = GetActorForwardVector();
		//AddMovementInput(Forward, DirectionValue);

		//UE_LOG(LogTemp, Warning, TEXT("IA_Movement triggered %f"), DirectionValue);
	}
}

void ATank::Turn(const FInputActionValue& Value) {
	const float RotationValue = Value.Get<float>();

	if (Controller && (RotationValue != 0.f)) {
		FRotator DeltaRotation = FRotator::ZeroRotator;
		// Yaw = Value * DeltaTime * TurnRate
		DeltaRotation.Yaw = RotationValue * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);

		AddActorLocalRotation(DeltaRotation, true);
	}

}
