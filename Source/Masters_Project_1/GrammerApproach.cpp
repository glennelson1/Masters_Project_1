// Fill out your copyright notice in the Description page of Project Settings.


#include "GrammerApproach.h"

// Sets default values
AGrammerApproach::AGrammerApproach()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrammerApproach::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGrammerApproach::DeleteGrid()
{
	for (AActor* actor : Cellref)
	{
		actor->Destroy();
		
	}
	Cellref.Empty();
}

void AGrammerApproach::GenerateLevel()
{
	DeleteGrid();
	
	
	for(int x = 0; x < 20; x++)
	{
		int32 RandomIndex = FMath::RandRange(0, 4);
		AActor* NewCell;
		int loc = x *3;
		switch (RandomIndex)
		{
		case 0:
			NewCell = GetWorld()->SpawnActor<AActor>(G, FVector(loc * 100, 0, 0), FRotator::ZeroRotator);
			Cellref.Add(NewCell);
			Grammer.Add("G");
			break;
		case 1:
			NewCell = GetWorld()->SpawnActor<AActor>(Q, FVector(loc * 100, 0, 0), FRotator::ZeroRotator);
			Cellref.Add(NewCell);
			Grammer.Add("Q");
			break;
		case 2:
			NewCell = GetWorld()->SpawnActor<AActor>(O, FVector(loc *100, 0, 0), FRotator::ZeroRotator);
			Cellref.Add(NewCell);
			Grammer.Add("O");
			break;
		case 3:
			NewCell = GetWorld()->SpawnActor<AActor>(C, FVector( loc *100, 0, 0), FRotator::ZeroRotator);
			Cellref.Add(NewCell);
			Grammer.Add("C");
			break;
		case 4:
			NewCell = GetWorld()->SpawnActor<AActor>(P, FVector(loc *100, 0,  0), FRotator::ZeroRotator);
			Cellref.Add(NewCell);
			Grammer.Add("P");
			break;
		}
	}
	for (auto Element : Grammer)
	{
		UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %s"), *Element);
	}
}

// Called every frame
void AGrammerApproach::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

