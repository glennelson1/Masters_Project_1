// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelFromSeed.generated.h"

UCLASS()
class MASTERS_PROJECT_1_API ALevelFromSeed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelFromSeed();

protected:
	int32 RandomInt;

	int32 m_Index;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Grid")
	TArray<TSubclassOf<AActor>> CellClasses;
	
	void GenerateLevelFromChoices(const TArray<int32>& Choices);
	UFUNCTION(BlueprintCallable)
	void LoadLevelFromSeed(const FString& Seed);
    	
	TArray<AActor*> Cellref;

	UFUNCTION(BlueprintCallable)
	void DeleteGrid();
    	
	UFUNCTION(BlueprintCallable)
	void SpawnGrid();
    	
	int m_LastCellPos;
    
	//Level elements
	void SpawnFloor(int loc,const TArray<int32>& Choices, int32 Int);
	void SpawnBricks(int loc, const TArray<int32>& Choices, int32 ChoiceIndex);
	void SpawnOb(int loc,const TArray<int32>& Choices, int32 ChoiceIndex);
	void SpawnPlatforms(int loc,const TArray<int32>& Choices, int32 ChoiceIndex);
    
    	
	FString GenerateSeed();
    	
	void SaveSeedToFile(const FString& Seed);
	void DebugPrintSeed();
    	
    
	UPROPERTY(EditAnywhere, Category = "Seed")
	TArray<int32> RandomChoices;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
