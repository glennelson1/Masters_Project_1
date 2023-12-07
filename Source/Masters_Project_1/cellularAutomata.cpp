// Fill out your copyright notice in the Description page of Project Settings.


#include "cellularAutomata.h"

#include "Engine/StaticMeshActor.h"

// Sets default values
AcellularAutomata::AcellularAutomata()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AcellularAutomata::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AcellularAutomata::DeleteGrid()
{
	for (AActor* actor : Cellref)
	{
		actor->Destroy();
		
	}
	Cellref.Empty();
}

void AcellularAutomata::SpawnGrid()
{
	DeleteGrid();
	srand(time(nullptr)); 

	InitializeGrid();
	for (int i = 0; i < m_SmoothingSteps; ++i) {
		DoSimulationStep();
	}
	GenerateLevel();
}

void AcellularAutomata::InitializeGrid()
{
	Grid.Init(TArray<int>(), m_Height);
	for (int y = 0; y < m_Height; ++y) {
		Grid[y].Init(0, m_Width);
		for (int x = 0; x < m_Width; ++x) {
			Grid[y][x] = (rand() % 100) < m_FillProbability ? 1 : 0;
		}
	}
}

void AcellularAutomata::DoSimulationStep()
{
	TArray<TArray<int>> newGrid;
	newGrid.Init(TArray<int>(), m_Height);
	for (int y = 0; y < m_Height; ++y) {
		newGrid[y].Init(0, m_Width);
		for (int x = 0; x < m_Width; ++x) {
			int neighborWalls = GetNeighborWallCount(x, y);
			if (Grid[y][x] == 1) {
				newGrid[y][x] = neighborWalls >= 4 ? 1 : 0;
			} else {
				newGrid[y][x] = neighborWalls >= 5 ? 1 : 0;
			}
		}
	}
	Grid = newGrid;
}

int AcellularAutomata::GetNeighborWallCount(int x, int y)
{
	int count = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			int nx = x + i;
			int ny = y + j;
			if (nx < 0 || nx >= m_Width || ny < 0 || ny >= m_Height) {
				count++;
			} else if (Grid[ny][nx] == 1) {
				count++;
			}
		}
	}
	return count;
}

void AcellularAutomata::GenerateLevel()
{
	if (!Wall) {
		UE_LOG(LogTemp, Warning, TEXT("Platform mesh not found!"));
		return;
	}

	FVector Location;
	for (int y = 0; y < m_Height; ++y) {
		for (int x = 0; x < m_Width; ++x) {
			
			Location = FVector(x * 100.0f, 0.0f, y * -50.0f); 

			if (Grid[y][x] == 1) {
				// Spawn a platform
				SpawnMeshAtLocation(Wall, Location);
			}
			
		}
	}
	
}

void AcellularAutomata::SpawnMeshAtLocation(UStaticMesh* Mesh, FVector Location)
{
	if (!Mesh) {
		return;
	}

	FActorSpawnParameters SpawnParams;
	AStaticMeshActor* MeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(Location, FRotator::ZeroRotator, SpawnParams);
	Cellref.Add(MeshActor);
	if (MeshActor) {
		MeshActor->GetStaticMeshComponent()->SetStaticMesh(Mesh);
		MeshActor->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f)); 
	}
}

// Called every frame
void AcellularAutomata::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

