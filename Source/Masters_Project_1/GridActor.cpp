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
				AActor* NewCell;
				FindNeigbours(SpawnLocation);
				NewCell = GetWorld()->SpawnActor<AActor>(PickGrid(1,1), SpawnLocation, FRotator::ZeroRotator);
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

void AGridActor::FindNeigbours(FVector cellLoc)
{
	
	FVector CellLocation = cellLoc;
	AActor* NeighbourLeft = nullptr;
	AActor* NeighbourRight = nullptr;
	AActor* NeighbourUp = nullptr;
	AActor* NeighbourDown = nullptr;
		// Define the relative offsets for neighboring cells
	FVector NeighbourOffsets[] = {
		FVector(100, 0, 0),   // Right
		FVector(-100, 0, 0),  // Left
		FVector(0, 100, 0),   // Forward
		FVector(0, -100, 0)   // Backward
			// Add more offsets for other directions if needed
	};
	FHitResult HitResultLeft, HitResultRight, HitResultUp,HitResultDown;
	FCollisionQueryParams CollisionParams;
	//CollisionParams.AddIgnoredActor(); // Ignore the current cell

	if (GetWorld()->LineTraceSingleByChannel(HitResultLeft, CellLocation,CellLocation + FVector(-100, 0, 0) , ECC_Visibility, CollisionParams) || GetWorld()->LineTraceSingleByChannel(HitResultRight, CellLocation,CellLocation + FVector(100, 0, 0) , ECC_Visibility, CollisionParams) || GetWorld()->LineTraceSingleByChannel(HitResultUp, CellLocation,CellLocation + FVector(0, 100, 0) , ECC_Visibility, CollisionParams) || GetWorld()->LineTraceSingleByChannel(HitResultDown, CellLocation,CellLocation + FVector(0, -100, 0) , ECC_Visibility, CollisionParams))
	{
		NeighbourLeft = HitResultLeft.GetActor();
		NeighbourRight = HitResultRight.GetActor();
		NeighbourUp =HitResultUp.GetActor();
		NeighbourDown = HitResultDown.GetActor();
		if (NeighbourLeft->IsA(CellClasses[0]))
		{
			UE_LOG(LogTemp, Warning, TEXT("0 Left"));
		}
		if (NeighbourLeft->IsA(CellClasses[1]))
		{
			UE_LOG(LogTemp, Warning, TEXT("1 Left"));
		}
		if (NeighbourLeft->IsA(CellClasses[2]))
		{
			UE_LOG(LogTemp, Warning, TEXT("2 Left"));
		}
		if (NeighbourRight->IsA(CellClasses[0]))
		{
			UE_LOG(LogTemp, Warning, TEXT("0 Right"));
		}
		if (NeighbourRight->IsA(CellClasses[1]))
		{
			UE_LOG(LogTemp, Warning, TEXT("1 Left"));
		}
		if (NeighbourRight->IsA(CellClasses[2]))
		{
			UE_LOG(LogTemp, Warning, TEXT("2 Left"));
		}
	}
	

}


// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

}

