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
	//DrawDebugLine(GetWorld(),CellLocation,CellLocation + FVector(100, 0, 0), FColor::Orange, false, 10.0f );
	FVector CellLocation = cellLoc;
	// Define the relative offsets for neighboring cells
	FHitResult HitResultLeft, HitResultRight, HitResultUp,HitResultDown;
	FCollisionQueryParams CollisionParams;
	//CollisionParams.AddIgnoredActor(this);

	bool bHitLeft = GetWorld()->LineTraceSingleByChannel(HitResultLeft, CellLocation, CellLocation + FVector(-100, 0, 0), ECC_Visibility, CollisionParams);
	bool bHitDown = GetWorld()->LineTraceSingleByChannel(HitResultDown, CellLocation, CellLocation + FVector(0, 0, -100), ECC_Visibility, CollisionParams);
	bool bhitLeftAndDown =  GetWorld()->LineTraceSingleByChannel(HitResultLeft, CellLocation, CellLocation + FVector(-100, 0, 0), ECC_Visibility, CollisionParams) && GetWorld()->LineTraceSingleByChannel(HitResultDown, CellLocation, CellLocation + FVector(0, 0, -100), ECC_Visibility, CollisionParams);
	NeighbourLeft = HitResultLeft.GetActor();
	NeighbourRight = HitResultRight.GetActor();
	NeighbourUp =HitResultUp.GetActor();
	NeighbourDown = HitResultDown.GetActor();

	if(bHitLeft && bHitDown)
	{
		bHitDown = false;
		bHitLeft = false;
	}

	
	if(bHitLeft)
	{
		if(HitResultLeft.GetActor()->IsA(CellClasses[0]))
		{
			UE_LOG(LogTemp, Warning, TEXT("0 Left"));
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1]))
		{
			UE_LOG(LogTemp, Warning, TEXT("1 Left"));
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[2]))
		{
			UE_LOG(LogTemp, Warning, TEXT("2 Left"));
		}
	}
	if(bHitDown)
	{
		if(HitResultDown.GetActor()->IsA(CellClasses[0]))
		{
			UE_LOG(LogTemp, Warning, TEXT("0 Down"));
		}
		if(HitResultDown.GetActor()->IsA(CellClasses[1]))
		{
			UE_LOG(LogTemp, Warning, TEXT("1 Down"));
		}
		if(HitResultDown.GetActor()->IsA(CellClasses[2]))
		{
			UE_LOG(LogTemp, Warning, TEXT("2 Down"));
		}
	}
	if(bhitLeftAndDown)
	{
		if(HitResultLeft.GetActor()->IsA(CellClasses[0]) && HitResultDown.GetActor()->IsA(CellClasses[0]))
		{
			UE_LOG(LogTemp, Warning, TEXT("0 Left and 0 down"));
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1]) && HitResultDown.GetActor()->IsA(CellClasses[0]))
		{
			UE_LOG(LogTemp, Warning, TEXT("1 Left and 0 down"));
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[2]) && HitResultDown.GetActor()->IsA(CellClasses[0]))
		{
			UE_LOG(LogTemp, Warning, TEXT("2 Left and 0 down"));
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[0])&& HitResultDown.GetActor()->IsA(CellClasses[1]))
		{
			UE_LOG(LogTemp, Warning, TEXT("0 Left and 1 down"));
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1]) && HitResultDown.GetActor()->IsA(CellClasses[1]))
		{
			UE_LOG(LogTemp, Warning, TEXT("1 Left and 1 down"));
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[2]) && HitResultDown.GetActor()->IsA(CellClasses[1]))
		{
			UE_LOG(LogTemp, Warning, TEXT("2 Left and 1 down"));
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[0])&& HitResultDown.GetActor()->IsA(CellClasses[2]))
		{
			UE_LOG(LogTemp, Warning, TEXT("0 Left and 2 down"));
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1])&& HitResultDown.GetActor()->IsA(CellClasses[2]))
		{
			UE_LOG(LogTemp, Warning, TEXT("1 Left and 2 down"));
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[2])&& HitResultDown.GetActor()->IsA(CellClasses[2]))
		{
			UE_LOG(LogTemp, Warning, TEXT("2 Left and 2 down"));
		}
	}
	
	
	
	/*if (bHitLeft) {
		if(HitResultLeft.GetActor()->IsA(CellClasses[0]))
		{
			UE_LOG(LogTemp, Warning, TEXT("0 Left"));
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[1]))
		{
			UE_LOG(LogTemp, Warning, TEXT("1 Left"));
		}
		if(HitResultLeft.GetActor()->IsA(CellClasses[2]))
		{
			UE_LOG(LogTemp, Warning, TEXT("2 Left"));
		}
	}
	if (bHitDown) {
		if(HitResultDown.GetActor()->IsA(CellClasses[0]))
		{
			UE_LOG(LogTemp, Warning, TEXT("0 Down"));
		}
		if(HitResultDown.GetActor()->IsA(CellClasses[1]))
		{
			UE_LOG(LogTemp, Warning, TEXT("1 Down"));
		}
		if(HitResultDown.GetActor()->IsA(CellClasses[2]))
		{
			UE_LOG(LogTemp, Warning, TEXT("2 Down"));
		}
		UE_LOG(LogTemp, Warning, TEXT("Break"));
	}*/
	
	/*if (bHitRight)
	{
		if(HitResultRight.GetActor()->IsA(CellClasses[0]))
		{
			UE_LOG(LogTemp, Warning, TEXT("0 Right"));
		}
		if(HitResultRight.GetActor()->IsA(CellClasses[1]))
		{
			UE_LOG(LogTemp, Warning, TEXT("1 Right"));
		}
		if(HitResultRight.GetActor()->IsA(CellClasses[2]))
		{
			UE_LOG(LogTemp, Warning, TEXT("2 Right"));
		}
	}

	if (bHitUp) {
		if(HitResultUp.GetActor()->IsA(CellClasses[0]))
		{
				UE_LOG(LogTemp, Warning, TEXT("0 Up"));
		}
		if(HitResultUp.GetActor()->IsA(CellClasses[1]))
		{
			UE_LOG(LogTemp, Warning, TEXT("1 Up"));
		}
		if(HitResultUp.GetActor()->IsA(CellClasses[2]))
		{
			UE_LOG(LogTemp, Warning, TEXT("2 Up"));
		}
	} */

	
	
	
	
	//CollisionParams.AddIgnoredActor(); // Ignore the current cell
	
	/*if (GetWorld()->LineTraceSingleByChannel(HitResultLeft, Start,End , ECC_Visibility, CollisionParams) )
	{
		DrawDebugLine(GetWorld(),Start,End, FColor::Orange, false, 10.0f );
		NeighbourLeft = HitResultLeft.GetActor();
		
		NeighbourRight = HitResultRight.GetActor();

		
		NeighbourUp =HitResultUp.GetActor();
		NeighbourDown = HitResultDown.GetActor();
		if (NeighbourLeft->IsA(CellClasses[0]))
		{
			UE_LOG(LogTemp, Warning, TEXT("0 Right"));
		}
		if (NeighbourLeft->IsA(CellClasses[1]))
		{
			UE_LOG(LogTemp, Warning, TEXT("1 Right"));
		}
		if (NeighbourLeft->IsA(CellClasses[2]))
		{
			UE_LOG(LogTemp, Warning, TEXT("2 Right"));
		}
		
	}*/
	
}

// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

}

