// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Level.h"

#include <string>

#include "GenericPlatform/GenericPlatformCrashContext.h"

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
	
	
	
	
}

void APCG_Level::DeleteGrid()
{
	for (AActor* actor : Cellref)
	{
		actor->Destroy();
		
	}
	Cellref.Empty();
}

void APCG_Level::SpawnGrid()
{
	DeleteGrid();
	
	for(int i = 0; i < 150; i += 10)
	{
		int32 RandomInt= FMath::RandRange(0, 100);
		if(RandomInt <= 70)
		{
			SpawnFloor(i + 2);
		}
		if(RandomInt >= 71)
		{
			SpawnFloor(i );
		}
		
	}
}

void APCG_Level::SpawnFloor(int loc)
{
	int32 RandomInt= FMath::RandRange(0, 10);
	
	for (int32 X = loc; X <= loc + 10; X++)
	{
		for (int32 Y = 0; Y < 3; Y++)
		{
			FVector SpawnLocation = FVector(X * 100, 0,Y * -100); // Adjust the spacing as needed.
			AActor* NewCell;
			NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[0], SpawnLocation, FRotator::ZeroRotator);
			Cellref.Add(NewCell);
			
		}
	}
	/*for (int32 X = loc; X <= loc + RandomInt; X++)
	{
		
		FVector SpawnLocation = FVector(X * 100, 0,800); // Adjust the spacing as needed.
		AActor* NewCell;
		NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[0], SpawnLocation, FRotator::ZeroRotator);
		Cellref.Add(NewCell);
	}*/
	SpawnBricks(loc);
}

void APCG_Level::SpawnBricks(int loc)
{
	int32 RandomInt= FMath::RandRange(0, 20);
	
	if(RandomInt <= 10)
	{
		SpawnOb(loc);
	}
	else if(RandomInt >= 11 && RandomInt <= 15)
	{
		
		FVector SpawnLocation = FVector((loc + 6) * 100, 0,400); 
		AActor* NewCell;
		NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[5], SpawnLocation, FRotator::ZeroRotator);
		Cellref.Add(NewCell);
	}
	else if(RandomInt >= 16 && RandomInt <= 20)
	{
		for (int32 X = loc; X < loc + 4; X++)
		{
			FVector SpawnLocation = FVector((X + 5) * 100, 0,400); 
			AActor* NewCell;
			NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[4], SpawnLocation, FRotator::ZeroRotator);
			Cellref.Add(NewCell);
		}
	}
}

void APCG_Level::SpawnOb(int loc)
{
	int32 RandomInt= FMath::RandRange(0, 20);
	if(RandomInt <= 10)
	{
		
	}
	else if(RandomInt >= 11 && RandomInt <= 15)
	{
		
		FVector SpawnLocation = FVector((loc + 3) * 100, 0, 100);
		FVector SpawnLocation2 = FVector((loc + 9) * 100, 0, 100);// Adjust the spacing as needed.
		AActor* NewCell;
		
		NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[1], SpawnLocation, FRotator::ZeroRotator);
		Cellref.Add(NewCell);
		
		NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[2], SpawnLocation2, FRotator::ZeroRotator);
		Cellref.Add(NewCell);
		
	}
	else if(RandomInt >= 16 && RandomInt <= 20)
	{
		
		FVector SpawnLocation = FVector((loc + 6) * 100, 0,100); // Adjust the spacing as needed.
		AActor* NewCell;
		NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[3], SpawnLocation, FRotator::ZeroRotator);
		Cellref.Add(NewCell);
		
	}
}

// Called every frame
void APCG_Level::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

