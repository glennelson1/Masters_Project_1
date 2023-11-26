// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelFromSeed.h"

#include <string>

// Sets default values
ALevelFromSeed::ALevelFromSeed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelFromSeed::LoadLevelFromSeed(const FString& Seed)
{
	UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %s"), *Seed);
	TArray<FString> SeedValues;

	
	
	Seed.ParseIntoArray(SeedValues, TEXT(","), true);

	TArray<int32> DecodedChoices;
	
	DecodedChoices.Add(SeedValues.Num());
	

	GenerateLevelFromChoices(DecodedChoices);
}
void ALevelFromSeed::GenerateLevelFromChoices(const TArray<int32>& Choices)
{
	DeleteGrid(); // Clear existing level

	int32 ChoiceIndex = 0;

	for (int i = 0; i < 150; i += 10)
	{
		if (ChoiceIndex >= Choices.Num())
		{
			break; // Prevent out-of-bounds access if the seed is shorter than expected
		}

		int32 RandomInt = Choices[ChoiceIndex++];
		UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), RandomInt);

		if (RandomInt <= 7)
		{
			SpawnFloor(i + 2,  Choices, RandomInt);
		}
		if (RandomInt >= 8)
		{
			SpawnFloor(i,Choices, RandomInt);
		}
	}
	
}
// Called when the game starts or when spawned
void ALevelFromSeed::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelFromSeed::DeleteGrid()
{
	for (AActor* actor : Cellref)
	{
		actor->Destroy();
		
	}
	Cellref.Empty();
}

void ALevelFromSeed::SpawnGrid()
{
	
	/*DeleteGrid();
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
	DebugPrintSeed();*/
}

void ALevelFromSeed::SpawnFloor(int loc,const TArray<int32>& Choices, int32 RandomInt)
{
	//int32 RandomInt= FMath::RandRange(0, 10);
	//RandomInt = ChoiceIndex++;
	
	
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
	
	SpawnBricks(loc, Choices, RandomInt);
}

void ALevelFromSeed::SpawnBricks(int loc, const TArray<int32>& Choices, int32 ChoiceIndex)
{
	//int32 RandomInt= FMath::RandRange(0, 20);
	if (ChoiceIndex >= Choices.Num())
	{
		// Handle error or end of choices
		return;
	}

	// Use the current choice
	int32 RandomInt = Choices[ChoiceIndex++];
	
	if(RandomInt <= 10)
	{
		SpawnOb(loc,Choices, RandomInt);
	}
	else if(RandomInt >= 11 && RandomInt <= 15)//spawns single block
	{
		
		FVector SpawnLocation = FVector((loc + 6) * 100, 0,400); 
		AActor* NewCell;
		NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[5], SpawnLocation, FRotator::ZeroRotator);
		Cellref.Add(NewCell);
	}
	else if(RandomInt >= 16 && RandomInt <= 20)// spawns a platform of blocks
	{
		for (int32 X = loc; X < loc + 3; X++)
		{
			FVector SpawnLocation = FVector((X + 5) * 100, 0,400); 
			AActor* NewCell;
			NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[4], SpawnLocation, FRotator::ZeroRotator);
			Cellref.Add(NewCell);
		}
		SpawnPlatforms(loc,Choices, RandomInt);
	}
	ChoiceIndex++;
}

void ALevelFromSeed::SpawnOb(int loc,const TArray<int32>& Choices, int32 ChoiceIndex)
{
	//int32 RandomInt= FMath::RandRange(0, 20);
	if (ChoiceIndex >= Choices.Num())
	{
		// Handle error or end of choices
		return;
	}

	// Use the current choice
	int32 RandomInt = Choices[ChoiceIndex++];
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

void ALevelFromSeed::SpawnPlatforms(int loc,const TArray<int32>& Choices, int32 ChoiceIndex) 
{
	//int32 RandomInt= FMath::RandRange(0, 100);
	if (ChoiceIndex >= Choices.Num())
	{
		// Handle error or end of choices
		return;
	}

	// Use the current choice
	int32 RandomInt = Choices[ChoiceIndex++];
	
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

FString ALevelFromSeed::GenerateSeed()
{
	FString Seed;
	for (int32 Choice : RandomChoices)
	{
		Seed += FString::Printf(TEXT("%d,"), Choice);
	}
	return Seed;
}

void ALevelFromSeed::SaveSeedToFile(const FString& Seed)
{
	FString SavePath = FPaths::ProjectSavedDir() + TEXT("LevelSeeds.txt");
	FFileHelper::SaveStringToFile(Seed + TEXT("\n"), *SavePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);

}
void ALevelFromSeed::DebugPrintSeed()
{
	FString GeneratedSeed = GenerateSeed();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Level Seed: ") + GeneratedSeed);
}

// Called every frame
void ALevelFromSeed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

