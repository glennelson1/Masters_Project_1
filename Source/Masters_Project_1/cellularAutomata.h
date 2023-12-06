// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "cellularAutomata.generated.h"

UCLASS()
class MASTERS_PROJECT_1_API AcellularAutomata : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AcellularAutomata();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitializeGrid();
	void DoSimulationStep();
	int GetNeighborWallCount(int x, int y);
	void GenerateLevel();

	void SpawnMeshAtLocation(UStaticMesh* Mesh, FVector Location);


	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* Ground;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* Wall;
	
	TArray<TArray<int>> Grid;

	
	const int m_Width = 100;
	const int m_Height = 50;
	const int m_FillProbability = 45;
	const int m_SmoothingSteps = 5;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
