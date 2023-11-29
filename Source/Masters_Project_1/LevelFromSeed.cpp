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
void ALevelFromSeed::LoadLevelFromSeed()
{
	UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %s"), *Seed);
	TArray<FString> SeedValues;
	Seed.ParseIntoArray(SeedValues, TEXT(","), true);
	m_Index = 0;
	TArray<int32> DecodedChoices;
	for (const FString& Value : SeedValues)
	{
		if (Value.Len() > 0)
		{
			DecodedChoices.Add(FCString::Atoi(*Value));
		}
	}

	GenerateLevelFromChoices(DecodedChoices);
}
void ALevelFromSeed::GenerateLevelFromChoices(const TArray<int32>& Choices)
{
	DeleteGrid(); // Clear existing level

	int32 ChoiceIndex;

	for (int i = 0; i < 150; i += 10)
	{
		
		
		ChoiceIndex = m_Index;
		RandomInt = Choices[ChoiceIndex++];
		m_Index = ChoiceIndex;
		

		if (RandomInt <= 7)
		{
			for (int32 X = i + 2; X <= (i + 2) + 10; X++)
			{
				for (int32 Y = 0; Y < 3; Y++)
				{
					FVector SpawnLocation = FVector(X * 100, 0,Y * -100);
					AActor* NewCell;
					NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[0], SpawnLocation, FRotator::ZeroRotator);
					Cellref.Add(NewCell);
			
				}
			}
		}
		if (RandomInt >= 8)
		{
			for (int32 X = i; X <= i + 10; X++)
			{
				for (int32 Y = 0; Y < 3; Y++)
				{
					FVector SpawnLocation = FVector(X * 100, 0,Y * -100);
					AActor* NewCell;
					NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[0], SpawnLocation, FRotator::ZeroRotator);
					Cellref.Add(NewCell);
			
				}
			}
		}
		///////bricks
		RandomInt = Choices[ChoiceIndex++];
		m_Index = ChoiceIndex;

		if(RandomInt <= 10)
		{
			///Obsticles
			RandomInt = Choices[ChoiceIndex++];
			m_Index = ChoiceIndex;
			
			if(RandomInt >= 11 && RandomInt <= 15)//spawns pipes
				{
		
				FVector SpawnLocation = FVector((i + 3) * 100, 0, 100);
				FVector SpawnLocation2 = FVector((i + 9) * 100, 0, 100);
				AActor* NewCell;
		
				NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[1], SpawnLocation, FRotator::ZeroRotator);
				Cellref.Add(NewCell);
		
				NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[2], SpawnLocation2, FRotator::ZeroRotator);
				Cellref.Add(NewCell);
				m_Index = ChoiceIndex;
				}
			else if(RandomInt >= 16) //spawns stairs
				{
				FVector SpawnLocation = FVector((i + 6) * 100, 0,100); 
				AActor* NewCell;
				NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[3], SpawnLocation, FRotator::ZeroRotator);
				Cellref.Add(NewCell);
				m_Index = ChoiceIndex;
				}
		
		}
		else if(RandomInt >= 11 && RandomInt <= 15)//spawns single block
			{
		
			FVector SpawnLocation = FVector((i + 6) * 100, 0,400); 
			AActor* NewCell;
			NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[5], SpawnLocation, FRotator::ZeroRotator);
			Cellref.Add(NewCell);
			}
		else if(RandomInt >= 16 && RandomInt <= 20)// spawns a platform of blocks
			{
		
			for (int32 X = i; X < i + 3; X++)
			{
				FVector SpawnLocation = FVector((X + 5) * 100, 0,400); 
				AActor* NewCell;
				NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[4], SpawnLocation, FRotator::ZeroRotator);
				Cellref.Add(NewCell);
			}
			////platform
			RandomInt = Choices[ChoiceIndex++];
			m_Index = ChoiceIndex;
			
			if (RandomInt <= 50)
			{
				if(RandomInt <=30)
				{
					for (int32 X = i; X < i + 3; X++)
					{
						FVector SpawnLocation = FVector((X + 10) * 100, 0,800); 
						AActor* NewCell;
						NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[4], SpawnLocation, FRotator::ZeroRotator);
						Cellref.Add(NewCell);
					}
			
				}
				if(RandomInt >=31)
				{
					for (int32 X = i; X < i + 6; X++)
					{
						FVector SpawnLocation = FVector((X + 10) * 100, 0,800); 
						AActor* NewCell;
						NewCell = GetWorld()->SpawnActor<AActor>(CellClasses[4], SpawnLocation, FRotator::ZeroRotator);
						Cellref.Add(NewCell);
					}
			
				}
			}
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

// Called every frame
void ALevelFromSeed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

