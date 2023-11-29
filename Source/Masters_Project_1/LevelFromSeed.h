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
	void LoadLevelFromSeed();
	
	UPROPERTY(EditAnywhere, Category = "Seed")
	FString Seed;
	
	TArray<AActor*> Cellref;
	
	UFUNCTION(BlueprintCallable)
	void DeleteGrid();
    	
	
    	
	int m_LastCellPos;
    
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
