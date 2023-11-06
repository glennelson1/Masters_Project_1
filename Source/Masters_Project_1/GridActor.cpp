// Fill out your copyright notice in the Description page of Project Settings.


#include "GridActor.h"

// Sets default values
AGridActor::AGridActor()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = false;

	
	GridSizeX = 5;
	GridSizeZ = 5;

	
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

}


void AGridActor::DeleteGrid()
{
	for (AActor* actor : Cellref)
	{
		actor->Destroy();
		
	}
	Cellref.Empty();
}

void AGridActor::SpawnGrid()
{
	DeleteGrid();
	if (CellClasses.Num() > 0)
	{
		for (int32 X = 0; X < GridSizeX; X++)
		{
			for (int32 Z = 0; Z < GridSizeZ; Z++)
			{
				FVector SpawnLocation = FVector(X * 100, 0, Z * 100); // Adjust the spacing as needed.
				AActor* NewCell = GetWorld()->SpawnActor<AActor>(PickGrid(1,1), SpawnLocation, FRotator::ZeroRotator);
				Cellref.Add(NewCell);
			}
		}
	}
}

TSubclassOf<AActor> AGridActor::PickGrid(int32 X, int32 Z)
{
	
	int32 RandomIndex = FMath::RandRange(0, CellClasses.Num() - 1);
	return CellClasses[RandomIndex];
	
}




// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

}

