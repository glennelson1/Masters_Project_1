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
				
				NewCell = GetWorld()->SpawnActor<AActor>(FindNeigbours(SpawnLocation), SpawnLocation, FRotator::ZeroRotator);
				Cellref.Add(NewCell);
				
			}
		}
	}
}



TSubclassOf<AActor> AGridActor::FindNeigbours(FVector cellLoc)
{
	int32 RandomIndex = FMath::RandRange(0, CellClasses.Num()-1);
	int32 RandomIn1and2 = FMath::RandRange(1, 2);
	int32 RandomIn0and1 = FMath::RandRange(0, 20);
	//DrawDebugLine(GetWorld(),CellLocation,CellLocation + FVector(100, 0, 0), FColor::Orange, false, 10.0f );
	FVector CellLocation = cellLoc;
	// Define the relative offsets for neighboring cells
	FHitResult HitResultLeft, HitResultDown,HitResultDiagonal;
	FCollisionQueryParams CollisionParams;
	//CollisionParams.AddIgnoredActor(this);

	bool bHitLeft = GetWorld()->LineTraceSingleByChannel(HitResultLeft, CellLocation, CellLocation + FVector(-100, 0, 0), ECC_Visibility, CollisionParams);
	bool bHitDown = GetWorld()->LineTraceSingleByChannel(HitResultDown, CellLocation, CellLocation + FVector(0, 0, -100), ECC_Visibility, CollisionParams);
	
	FCollisionQueryParams CollisionParamsDiagonal;
	CollisionParamsDiagonal.AddIgnoredActor(this);
	CollisionParamsDiagonal.AddIgnoredActor(HitResultLeft.GetActor());
	CollisionParamsDiagonal.AddIgnoredActor(HitResultDown.GetActor());
	bool bHitDiagonal = GetWorld()->LineTraceSingleByChannel(HitResultDiagonal, CellLocation, CellLocation + FVector(-100, 0, -100), ECC_Visibility, CollisionParamsDiagonal);
	bool bhit =  GetWorld()->LineTraceSingleByChannel(HitResultLeft, CellLocation, CellLocation + FVector(-100, 0, 0), ECC_Visibility, CollisionParams) && GetWorld()->LineTraceSingleByChannel(HitResultDown, CellLocation, CellLocation + FVector(0, 0, -100), ECC_Visibility, CollisionParams) && GetWorld()->LineTraceSingleByChannel(HitResultDiagonal, CellLocation, CellLocation + FVector(-100, 0, -100), ECC_Visibility, CollisionParamsDiagonal);
	NeighbourLeft = HitResultLeft.GetActor();
	NeighbourDown = HitResultDown.GetActor();


	int TileType01, TileType02;
	if(RandomIn0and1 <= 15)
	{
		TileType01 = 1;
	}
	else TileType01 =2;
	if(RandomIn0and1 <= 15)
	{
		TileType02 = 0;
	}
	else TileType02 =1;
	
	if(bhit)
	{
		bHitDown = false;
		bHitLeft = false;
	}
	
	if(bHitLeft)
	{
		if(HitResultLeft.GetActor()->IsA(CellClasses[0]))
		{
			return CellClasses[TileType02];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1]))
		{
			return CellClasses[TileType02];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[2]))
		{
			return CellClasses[0];
		}
	}
	
	if(bHitDown)
	{
		if(HitResultDown.GetActor()->IsA(CellClasses[0]))
		{
			return CellClasses[1];
		}
		if(HitResultDown.GetActor()->IsA(CellClasses[1]))
		{
			return CellClasses[1];
		}
		if(HitResultDown.GetActor()->IsA(CellClasses[2]))
		{
			return CellClasses[1];
		}
	}

	
	if(bhit)
	{
		if(HitResultLeft.GetActor()->IsA(CellClasses[0]) && HitResultDown.GetActor()->IsA(CellClasses[0]) && HitResultDiagonal.GetActor()->IsA(CellClasses[0]))
		{
			return CellClasses[0];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1]) && HitResultDown.GetActor()->IsA(CellClasses[0]) && HitResultDiagonal.GetActor()->IsA(CellClasses[0]))
		{
			return CellClasses[1];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1]) && HitResultDown.GetActor()->IsA(CellClasses[1]) && HitResultDiagonal.GetActor()->IsA(CellClasses[1]))
		{
			return CellClasses[TileType01];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1]) && HitResultDown.GetActor()->IsA(CellClasses[1]) && HitResultDiagonal.GetActor()->IsA(CellClasses[0]))
		{
			return CellClasses[1];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1]) && HitResultDown.GetActor()->IsA(CellClasses[0]) && HitResultDiagonal.GetActor()->IsA(CellClasses[1]))
		{
			return CellClasses[1];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[2]) && HitResultDown.GetActor()->IsA(CellClasses[1]) && HitResultDiagonal.GetActor()->IsA(CellClasses[1]))
		{
			return CellClasses[TileType01];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1]) && HitResultDown.GetActor()->IsA(CellClasses[2]) && HitResultDiagonal.GetActor()->IsA(CellClasses[1]))
		{
			return CellClasses[1];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1]) && HitResultDown.GetActor()->IsA(CellClasses[1]) && HitResultDiagonal.GetActor()->IsA(CellClasses[2]))
		{
			return CellClasses[1];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[2]) && HitResultDown.GetActor()->IsA(CellClasses[1]) && HitResultDiagonal.GetActor()->IsA(CellClasses[0]))
		{
			return CellClasses[1];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[2]) && HitResultDown.GetActor()->IsA(CellClasses[0]) && HitResultDiagonal.GetActor()->IsA(CellClasses[1]))
		{
			return CellClasses[TileType01];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[2]) && HitResultDown.GetActor()->IsA(CellClasses[2]) && HitResultDiagonal.GetActor()->IsA(CellClasses[1]))
		{
			return CellClasses[1];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[2]) && HitResultDown.GetActor()->IsA(CellClasses[2]) && HitResultDiagonal.GetActor()->IsA(CellClasses[2]))
		{
			return CellClasses[1];
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1]) && HitResultDown.GetActor()->IsA(CellClasses[2]) && HitResultDiagonal.GetActor()->IsA(CellClasses[2]))
		{
			return CellClasses[1];
		}
	}
	
	return CellClasses[0];
}

// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

}

