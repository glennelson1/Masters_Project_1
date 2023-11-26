// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAICharacter.h"

// Sets default values
AMyAICharacter::AMyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	if (Controller)
	{
		// Set initial movement in the positive X direction
		Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		const FVector Direction = FVector(1.0f, 0.0f, 0.0f);
		
	}
}

// Called every frame
void AMyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

