// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridActor.generated.h"

UCLASS()
class MASTERS_PROJECT_1_API AGridActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Grid Settings")
	int32 GridSizeX;

	UPROPERTY(EditAnywhere, Category = "Grid Settings")
	int32 GridSizeZ;

	

	UPROPERTY(EditAnywhere, Category = "Grid")
	TArray<TSubclassOf<AActor>> CellClasses;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
