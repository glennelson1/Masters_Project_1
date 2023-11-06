// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSpawner.h"

// Sets default values
ALevelSpawner::ALevelSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LevelSize = 5;

}

// Called when the game starts or when spawned
void ALevelSpawner::BeginPlay()
{
	Super::BeginPlay();
    
	// Check that you have Level Segment Blueprints assigned to the array
	if (LevelSegments.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Level Segments assigned to the spawner."));
		return;
	}
    
	// Initialize the starting location
	FVector SpawnLocation = GetActorLocation();
    
	// Specify the offset between segments
	FVector SegmentOffset = FVector(300.0f, 0.0f, 0.0f);  // Adjust as needed
    
	for (int32 i = 0; i < LevelSize; i++)
	{
		int32 RandomIndex = FMath::RandRange(0, LevelSegments.Num() - 1);
        
		if (LevelSegments[RandomIndex])
		{
			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				AActor* NewSegment = World->SpawnActor<AActor>(LevelSegments[RandomIndex], SpawnLocation, GetActorRotation(), SpawnParams);
                
				// Update the SpawnLocation for the next segment
				SpawnLocation += SegmentOffset;
			}
		}
	}
}

// Called every frame
void ALevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



