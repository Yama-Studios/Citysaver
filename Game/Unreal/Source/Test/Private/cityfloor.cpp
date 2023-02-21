// Fill out your copyright notice in the Description page of Project Settings.


#include "CityFloor.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ACityFloor::ACityFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	numOfRoads = 5;
	cityWidth = 9;
	cityLength = 33;
	upperLeft = FVector(0);


	floorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	SetRootComponent(floorMesh);
	
}


// Called when the game starts or when spawned
void ACityFloor::BeginPlay()
{
	Super::BeginPlay();
	CreateCityArea();
	RoadSpawner();
}

// Called every frame
void ACityFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACityFloor::CreateCityArea()
{

	floorMesh->SetRelativeLocation(upperLeft);
	floorMesh->SetRelativeScale3D(FVector(cityWidth, cityLength, 1));

	float BRX = upperLeft.X + (cityWidth * 400);
	float BRY = upperLeft.Y + (cityLength * 400);
	lowerRight = FVector(BRX, BRY, 1);
	upperRight = FVector(upperLeft.X + cityWidth * 400, 0, 0);
	lowerLeft = FVector(0, upperLeft.Y + cityLength * 400, 0);
	
	float randomPointTopX = FMath::FRandRange(upperLeft.X, upperRight.X);
	float randomPointTopY = FMath::FRandRange(upperLeft.Y, upperRight.Y);
	float randomPointBottomX = FMath::FRandRange(lowerLeft.X, lowerRight.X);
	float randomPointBottomY = FMath::FRandRange(lowerLeft.Y, lowerRight.Y);
	float randomPointLeftY = FMath::FRandRange(upperLeft.Y, lowerLeft.Y);
	float randomPointLeftX = FMath::FRandRange(upperLeft.X, lowerLeft.X);
	float randomPointRightY = FMath::FRandRange(upperRight.Y, lowerRight.Y);
	float randomPointRightX = FMath::FRandRange(upperRight.X, lowerRight.X);

	randPointTop = FVector(randomPointTopX, randomPointTopY, 0);
	randPointBottom = FVector(randomPointBottomX, randomPointBottomY, 0);
	randPointLeft = FVector(randomPointLeftX, randomPointLeftY, 0);
	randPointRight = FVector(randomPointRightX, randomPointRightY, 0);

	//UKismetMathLibrary::RandomPointInBoundingBox(const FVector & Origin, const FVector & BoxExtent);
	//UKismetMathLibrary::RandomPointInBoundingBox()

}

void ACityFloor::RoadSpawner()
{

	for (int i = 0; i < numOfRoads; i++)
	{
		float randomPointTopX = FMath::FRandRange(upperLeft.X, upperRight.X);
		float randomPointTopY = FMath::FRandRange(upperLeft.Y, upperRight.Y);
		float randomPointBottomX = FMath::FRandRange(lowerLeft.X, lowerRight.X);
		float randomPointBottomY = FMath::FRandRange(lowerLeft.Y, lowerRight.Y);
		float randomPointLeftY = FMath::FRandRange(upperLeft.Y, lowerLeft.Y);
		float randomPointLeftX = FMath::FRandRange(upperLeft.X, lowerLeft.X);
		float randomPointRightY = FMath::FRandRange(upperRight.Y, lowerRight.Y);
		float randomPointRightX = FMath::FRandRange(upperRight.X, lowerRight.X);

		randPointTop = FVector(randomPointTopX, randomPointTopY, 0);
		randPointBottom = FVector(randomPointBottomX, randomPointBottomY, 0);
		randPointLeft = FVector(randomPointLeftX, randomPointLeftY, 0);
		randPointRight = FVector(randomPointRightX, randomPointRightY, 0);

		DrawDebugLine(GetWorld(), randPointTop, randPointBottom, FColor::Yellow, true, -1, 0, 1);
		DrawDebugLine(GetWorld(), randPointLeft, randPointRight, FColor::Yellow, true, -1, 0, 1);

		GetWorld()->SpawnActor<AActor>(spawnActor);
		//can do spawn Road from Here


	}
}


