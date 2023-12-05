// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <cvt/wstring>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrammerApproach.generated.h"

UCLASS()
class MASTERS_PROJECT_1_API AGrammerApproach : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrammerApproach();
	

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Grid")
	TSubclassOf<AActor> G;
	UPROPERTY(EditAnywhere, Category = "Grid")
	TSubclassOf<AActor> Q;
	UPROPERTY(EditAnywhere, Category = "Grid")
	TSubclassOf<AActor> O;
	UPROPERTY(EditAnywhere, Category = "Grid")
	TSubclassOf<AActor> C;
	UPROPERTY(EditAnywhere, Category = "Grid")
	TSubclassOf<AActor> P;
	
	
	TArray<AActor*> Cellref;
	UPROPERTY(EditAnywhere, Category = "Grid")
	TArray<TSubclassOf<AActor>> CellClasses;
	UFUNCTION(BlueprintCallable)
	void DeleteGrid();
	UFUNCTION(BlueprintCallable)
	void GenerateLevel();

	TArray<FString> Grammer;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
