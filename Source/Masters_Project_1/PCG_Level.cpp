// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Level.h"

// Sets default values
APCG_Level::APCG_Level()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GridSizeX = 2;
	GridSizeZ = 5;
	m_LastCellPos = 0;
	
}

// Called when the game starts or when spawned
void APCG_Level::BeginPlay()
{
	int test = 0;
	Super::BeginPlay();
	for(int i = 0; i < 5; i++)
	{
		SpawnFloor(i * 15);
		//test = 10;
	}
	
}

void APCG_Level::SpawnFloor(int loc)
{
	for (int32 Z = loc; Z < loc + 10; Z++)
	{
		FVector SpawnLocation = FVector(Z * 100, 0, 0); // Adjust the spacing as needed.
		AActor* NewCell;
				
		NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[0], SpawnLocation, FRotator::ZeroRotator);
		//Cellref.Add(NewCell);
		
	}
	
}

// Called every frame
void APCG_Level::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

