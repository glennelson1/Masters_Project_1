// Fill out your copyright notice in the Description page of Project Settings.


#include "GridActor.h"

// Sets default values
AGridActor::AGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = false;

	// Set default values for grid size.
	GridSizeX = 5;
	GridSizeZ = 5;

	// Set the default cell class.
	static ConstructorHelpers::FClassFinder<AActor> CellAsset(TEXT("/Game/Path/To/CellClass"));
	if (CellAsset.Succeeded())
	{
		CellClass = CellAsset.Class;
	}
}

// Called when the game starts or when spawned
void AGridActor::BeginPlay()
{
	Super::BeginPlay();

	if (CellClass)
	{
		for (int32 X = 0; X < GridSizeX; X++)
		{
			for (int32 Z = 0; Z < GridSizeZ; Z++)
			{
				FVector SpawnLocation = FVector(X * 100, 0, Z * 100); // Adjust the spacing as needed.
				AActor* NewCell = GetWorld()->SpawnActor<AActor>(CellClass, SpawnLocation, FRotator::ZeroRotator);
			}
		}
	}
	
}

// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

