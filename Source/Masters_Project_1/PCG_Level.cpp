// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Level.h"

#include <string>

#include "GenericPlatform/GenericPlatformCrashContext.h"

// Sets default values
APCG_Level::APCG_Level()
{
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void APCG_Level::BeginPlay()
{
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
	RandomChoices.Empty();
	
	for(int i = 0; i < 150; i += 10)
	{
		int32 RandomInt= FMath::RandRange(0, 10);
		RandomChoices.Add(RandomInt);
		if(RandomInt <= 7)
		{
			SpawnFloor(i + 2);
		}
		if(RandomInt >= 8) // puts a gap in the floor
		{
			SpawnFloor(i);
		}
		
	}
	GenerateSeed();
	SaveSeedToFile(GenerateSeed());
	//DebugPrintSeed();
}

void APCG_Level::SpawnFloor(int loc)
{
	
	for (int32 X = loc; X <= loc + 10; X++)
	{
		for (int32 Y = 0; Y < 3; Y++)
		{
			FVector SpawnLocation = FVector(X * 100, 0,Y * -100);
			AActor* NewCell;
			NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[0], SpawnLocation, FRotator::ZeroRotator);
			Cellref.Add(NewCell);
			
		}
	}
	
	SpawnBricks(loc);
}

void APCG_Level::SpawnBricks(int loc)
{
	int32 RandomInt= FMath::RandRange(0, 20);
	RandomChoices.Add(RandomInt);
	if(RandomInt <= 10)
	{
		SpawnOb(loc);
	}
	else if(RandomInt >= 11 && RandomInt <= 15)//spawns single block
	{
		
		FVector SpawnLocation = FVector((loc + 6) * 100, 0,400); 
		AActor* NewCell;
		NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[5], SpawnLocation, FRotator::ZeroRotator);
		Cellref.Add(NewCell);
	}
	else if(RandomInt >= 16)// spawns a platform of blocks
	{
		for (int32 X = loc; X < loc + 3; X++)
		{
			FVector SpawnLocation = FVector((X + 5) * 100, 0,400); 
			AActor* NewCell;
			NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[4], SpawnLocation, FRotator::ZeroRotator);
			Cellref.Add(NewCell);
		}
		SpawnPlatforms(loc);
	}
}

void APCG_Level::SpawnOb(int loc)
{
	int32 RandomInt= FMath::RandRange(0, 20);
	RandomChoices.Add(RandomInt);
	if(RandomInt >= 11 && RandomInt <= 15)//spawns pipes
	{
		
		FVector SpawnLocation = FVector((loc + 3) * 100, 0, 100);
		FVector SpawnLocation2 = FVector((loc + 9) * 100, 0, 100);
		AActor* NewCell;
		
		NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[1], SpawnLocation, FRotator::ZeroRotator);
		Cellref.Add(NewCell);
		
		NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[2], SpawnLocation2, FRotator::ZeroRotator);
		Cellref.Add(NewCell);
		
	}
	else if(RandomInt >= 16 && RandomInt <= 20) //spawns stairs
	{
		FVector SpawnLocation = FVector((loc + 6) * 100, 0,100); 
		AActor* NewCell;
		NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[3], SpawnLocation, FRotator::ZeroRotator);
		Cellref.Add(NewCell);
	}
}

void APCG_Level::SpawnPlatforms(int loc) 
{
	int32 RandomInt= FMath::RandRange(0, 100);
	RandomChoices.Add(RandomInt);
	if (RandomInt <= 50)
	{
		if(RandomInt <=30)
		{
			for (int32 X = loc; X < loc + 3; X++)
			{
				FVector SpawnLocation = FVector((X + 10) * 100, 0,800); 
				AActor* NewCell;
				NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[4], SpawnLocation, FRotator::ZeroRotator);
				Cellref.Add(NewCell);
			}
		}
		if(RandomInt >=31)
		{
			for (int32 X = loc; X < loc + 6; X++)
			{
				FVector SpawnLocation = FVector((X + 10) * 100, 0,800); 
				AActor* NewCell;
				NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[4], SpawnLocation, FRotator::ZeroRotator);
				Cellref.Add(NewCell);
			}
		}
	}
	
}

FString APCG_Level::GenerateSeed()
{
	FString Seed;
	for (int32 Choice : RandomChoices)
	{
		Seed += FString::Printf(TEXT("%d,"), Choice);
	}
	return Seed;
}

void APCG_Level::SaveSeedToFile(const FString& Seed)
{
	FString SavePath = FPaths::ProjectSavedDir() + TEXT("LevelSeeds.txt");
	FFileHelper::SaveStringToFile(Seed + TEXT("\n"), *SavePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);

}
void APCG_Level::DebugPrintSeed()
{
	FString GeneratedSeed = GenerateSeed();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Level Seed: ") + GeneratedSeed);
}

void APCG_Level::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

