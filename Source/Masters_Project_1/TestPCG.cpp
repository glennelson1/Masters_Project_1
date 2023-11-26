// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPCG.h"

// Sets default values
ATestPCG::ATestPCG()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridSizeX = 50;
	GridSizeZ = 5;
}

// Called when the game starts or when spawned
void ATestPCG::BeginPlay()
{
	Super::BeginPlay();
	SpawnGround();
	SpawnOb();
	
}

void ATestPCG::SpawnGround()
{
	for (int32 X = 0; X < GridSizeX; X++)
	{
		int32 RandomIndex = FMath::RandRange(0, CellClasses.Num()-1);
		FVector SpawnLocation = FVector(X * 100, 0, 0); // Adjust the spacing as needed.
		AActor* NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[0], SpawnLocation, FRotator::ZeroRotator);
	}
}

void ATestPCG::SpawnOb()
{
	      
	for (int32 X = 0; X < GridSizeX; X++)
	{
		int32 RandomIndex = FMath::RandRange(0, 10);
		FVector SpawnLocation = FVector(X * 100, 0, 300); // Adjust the spacing as needed.
		if(RandomIndex <= 8)
		{
			AActor* NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[1], SpawnLocation, FRotator::ZeroRotator);
		}
		else
		{
			AActor* NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[0], SpawnLocation, FRotator::ZeroRotator);
		}
		
	}
}

// Called every frame
void ATestPCG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

