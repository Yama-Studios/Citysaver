// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralRoom.h"
#include "FloorNode.h"
#include "Floor.h"


// Sets default values
AProceduralRoom::AProceduralRoom():gridX(4),gridY(4),squareWidth(100),roomLength(400),roomWidth(400),radius(25)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	floorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	SetRootComponent(floorMesh);

	topLeft = FVector(0);
	bottomRight = FVector(1000, 1000, 0);
}

// Called when the game starts or when spawned
void AProceduralRoom::BeginPlay()
{
	Super::BeginPlay();
	//PlacePointsOnGrid();
	TSharedPtr<Floor> theFloor(new Floor());
	theFloor->Partition();

	theFloor->DrawFloorNodes(GetWorld());
	theFloor->PlacePoints(GetWorld());

	UE_LOG(LogTemp, Warning, TEXT("No.of Nodes : %d"), theFloor->GetPartitionedFloor().Num());
}


// Called every frame
void AProceduralRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AProceduralRoom::SpawnItems(UClass* spawnItem)
{
	for (int i = 0; i < 10; i++)
	{
		float xCoordinastions = FMath::FRandRange(0, 400);
	 	float yCoordinastions = FMath::FRandRange(0, 400);
		float yRotator = FMath::FRandRange(0, 360);

		FVector location(xCoordinastions, yCoordinastions, 0);
		FRotator rotator(0, yRotator, 0);

		GetWorld()->SpawnActor<AActor>(spawnItem, location, rotator);
		//GetWorld()->SpawnActor<AActor>()
	}
}

// DrawGrid()
/*
void AProceduralRoom::drawGrid()
{
	for (int32 i = 0; i < gridX + 1; i++)
	{
		FVector start = topLeft + FVector(i * squareWidth, 0, gridHeight);
		FVector end = start + FVector(0, roomLength, gridHeight);
		DrawDebugLine(GetWorld(), start, end, FColor::Red, true);
	}
	for (int i = 0; i < gridY + 1; i++)
	{
		FVector start = topLeft + FVector(0, i * squareWidth, gridHeight);
		FVector end = start + FVector(roomWidth, 0, gridHeight);
		DrawDebugLine(GetWorld(), start, end, FColor::Red, true);
	}
}
*/ 

FVector AProceduralRoom::GetRandompointsInSquare(const FVector& upperLeft, const FVector& lowerRight)
{
	float randX = FMath::FRandRange(upperLeft.X, lowerRight.X);
	float randY = FMath::FRandRange(upperLeft.Y, lowerRight.Y);
	return FVector(randX, randY, 0);
}

void AProceduralRoom::PlacePointsOnGrid()
{
	for (int i = 0; i < gridX; i++)
	{
		for (int j = 0; j < gridY; j++)
		{
			FVector upperLeft(i * squareWidth + radius, j * squareWidth + radius, gridHeight);
			FVector lowerRight(i * squareWidth + squareWidth - radius, j * squareWidth + squareWidth - radius, gridHeight);
			FVector randPointinsquare = GetRandompointsInSquare(upperLeft, lowerRight);
			float randY = FMath::FRandRange(0, 360);
			DrawDebugPoint(GetWorld(), randPointinsquare, 5, FColor::Green, true);
			int randItem = FMath::FRandRange(0, items.Num());
			GetWorld()->SpawnActor<AActor>(items[randItem], randPointinsquare, FRotator(0,randY,0));
		}
	}
}

