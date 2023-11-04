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
	static ConstructorHelpers::FClassFinder<AActor> CellClass1Asset(TEXT("/Game/Path/To/YourCellClass1"));
	if (CellClass1Asset.Succeeded())
	{
		CellClasses.Add(CellClass1Asset.Class);
	}

	static ConstructorHelpers::FClassFinder<AActor> CellClass2Asset(TEXT("/Game/Path/To/YourCellClass2"));
	if (CellClass2Asset.Succeeded())
	{
		CellClasses.Add(CellClass2Asset.Class);
	}

	static ConstructorHelpers::FClassFinder<AActor> CellClass3Asset(TEXT("/Game/Path/To/YourCellClass3"));
	if (CellClass3Asset.Succeeded())
	{
		CellClasses.Add(CellClass3Asset.Class);
	}
}

// Called when the game starts or when spawned
void AGridActor::BeginPlay()
{
	Super::BeginPlay();

	if (CellClasses.Num() > 0)
	{
		for (int32 X = 0; X < GridSizeX; X++)
		{
			for (int32 Z = 0; Z < GridSizeZ; Z++)
			{
				FVector SpawnLocation = FVector(X * 100, 0, Z * 100); // Adjust the spacing as needed.

				// Choose a random actor class from CellClasses
				int32 RandomIndex = FMath::RandRange(0, CellClasses.Num() - 1);
				TSubclassOf<AActor> ChosenCellClass = CellClasses[RandomIndex];

				// Spawn the selected actor class at the SpawnLocation
				AActor* NewCell = GetWorld()->SpawnActor<AActor>(ChosenCellClass, SpawnLocation, FRotator::ZeroRotator);
			}
		}
	}
	
}

// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

