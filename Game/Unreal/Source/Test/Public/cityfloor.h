// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CityFloor.generated.h"



class UStaticMeshComponent;

UCLASS()
class TEST_API ACityFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACityFloor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor)
	UStaticMeshComponent* floorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor)
	TSubclassOf<AActor> spawnActor;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor)
	FVector upperLeft;
	FVector upperRight;
	FVector lowerLeft;
	FVector lowerRight;

	FVector randPointTop;
	FVector randPointBottom;
	FVector randPointLeft;
	FVector randPointRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor)
	float cityWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor)
	float cityLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor)
	float numOfRoads;

	FVector topLeft;
	FVector bottomRight;

	void CreateCityArea();
	void RoadSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	

};
