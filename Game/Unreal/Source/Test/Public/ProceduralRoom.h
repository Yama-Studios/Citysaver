// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralRoom.generated.h"

UCLASS()
class TEST_API AProceduralRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralRoom();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Var
	int
		gridX,
		gridY;
	float
		squareWidth,
		gridHeight = 1,
		roomLength,
		roomWidth,
		radius;
	FVector
		topLeft,
		bottomRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* floorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		TArray<TSubclassOf<AActor>> items;
	

	void SpawnItems(UClass* spawnItem);

	void drawGrid();
	
	void PlacePointsOnGrid();

	FVector GetRandompointsInSquare(const FVector& upperLeft, const FVector& lowerRight);

};
