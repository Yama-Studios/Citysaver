#include "Floor.h"
#include "FloorNode.h"
//#include "DrawDebugerHelper.h"

Floor::Floor()
{
	floorGridSizeX = 400;
	floorGridSizeY = 400;
	roomMinX = 3;
	roomMinY = 5;
	unitLength = 100;
	splitChange = .5f;
}

Floor::~Floor()
{

}

void Floor::Partition()
{
	FCornerCoordinates cornerCoordinatesA = { 0,0, floorGridSizeX, floorGridSizeY};
	floorNodeStack.Push(TSharedPtr<FloorNode>(new FloorNode(cornerCoordinatesA)));

	while (floorNodeStack.Num() > 0)
	{
		TSharedPtr<FloorNode> A = floorNodeStack.Pop();

		bool bNodeWasSplit = SplitAttempt(A);
		if (!bNodeWasSplit)
		{
			partitionedFloor.Push(A);
		}
	}
}


int32 Floor::CoinFlip()
{
	return FMath::FRandRange(0, 1);
}

bool Floor::ShouldSpiltNode(TSharedPtr<FloorNode> inNode, ESplitOrientation splitOrientation)
{
	FCornerCoordinates cornerCoordinates = inNode->GetCornerCoordinates();
	if (splitOrientation == ESplitOrientation::ESO_Horizontal)
	{
		int32 floorLength = cornerCoordinates.lowerRightY - cornerCoordinates.upperLeftY;
		float percentChanceOfSplit = (float)floorLength / (float)floorGridSizeY;
		percentChanceOfSplit *= splitChange;
		float diceRoll = FMath::FRandRange(0, 1);

		if (diceRoll > percentChanceOfSplit)
		{
			return false;
		}

		if (floorLength >= 2 * roomMinY)
		{
			return true;
		}
	}
	else if (splitOrientation == ESplitOrientation::ESO_Vertical)
	{
		int32 floorWidth = cornerCoordinates.lowerRightX - cornerCoordinates.upperLeftX;
		float percentChanceOfSplit = (float)floorWidth/ (float)floorGridSizeX;
		percentChanceOfSplit *= splitChange;
		float diceRoll = FMath::FRandRange(0, 1);
		if (diceRoll > percentChanceOfSplit)
		{
			return false;
		}


		if (floorWidth >= 2 * roomMinX)
		{
			return true;
		}
	}
	return false;
}

bool Floor::SplitAttempt(TSharedPtr<FloorNode> inNode)
{
	int32 horizontalOrvertical = CoinFlip();
	if (horizontalOrvertical == 0)
	{
		//Try to splitHorizontal
		if (ShouldSpiltNode(inNode, ESplitOrientation::ESO_Horizontal))
		{
			TSharedPtr<FloorNode> B(new FloorNode());
			TSharedPtr<FloorNode> C(new FloorNode());

			SplitHorizontal(inNode, B, C);
			return true;

		}
		else if (ShouldSpiltNode(inNode, ESplitOrientation::ESO_Vertical))
		{
			TSharedPtr<FloorNode> B(new FloorNode());
			TSharedPtr<FloorNode> C(new FloorNode());

			SplitVertical(inNode, B, C);
			return true;
		}
	}
	else
	{
		// try SplitVertical
		if (ShouldSpiltNode(inNode, ESplitOrientation::ESO_Vertical))
		{
			TSharedPtr<FloorNode> B(new FloorNode());
			TSharedPtr<FloorNode> C(new FloorNode());

			SplitVertical(inNode, B, C);
			return true;
		}
		else if (ShouldSpiltNode(inNode, ESplitOrientation::ESO_Horizontal))
		{
			TSharedPtr<FloorNode> B(new FloorNode());
			TSharedPtr<FloorNode> C(new FloorNode());

			SplitHorizontal(inNode, B, C);
			return true;
		}
	}

	return false;
}

void Floor::SplitHorizontal(TSharedPtr<FloorNode> inA, TSharedPtr<FloorNode> inB, TSharedPtr<FloorNode> inC)
{
	int32 splitPointY = FMath::FRandRange(inA->GetCornerCoordinates().upperLeftY + roomMinY, inA->GetCornerCoordinates().lowerRightY - roomMinY);
	
	FCornerCoordinates cornerCoordinatesB;
	cornerCoordinatesB.upperLeftX = inA->GetCornerCoordinates().upperLeftX;
	cornerCoordinatesB.upperLeftY = inA->GetCornerCoordinates().upperLeftY;
	cornerCoordinatesB.lowerRightY = splitPointY;
	cornerCoordinatesB.lowerRightX = inA->GetCornerCoordinates().lowerRightX;

	inB->SetCornerCoordinates(cornerCoordinatesB);
	floorNodeStack.Push(inB);

	FCornerCoordinates cornerCoordinatesC;
	cornerCoordinatesC.upperLeftX = inA->GetCornerCoordinates().upperLeftX;
	cornerCoordinatesC.upperLeftY = splitPointY;
	cornerCoordinatesC.lowerRightX = inA->GetCornerCoordinates().lowerRightX;
	cornerCoordinatesC.lowerRightY = inA->GetCornerCoordinates().lowerRightY;

	inC->SetCornerCoordinates(cornerCoordinatesC);
	floorNodeStack.Push(inC);
}

void Floor::SplitVertical(TSharedPtr<FloorNode> inA, TSharedPtr<FloorNode> inB, TSharedPtr<FloorNode> inC)
{
	int32 splitPointX = FMath::FRandRange(inA->GetCornerCoordinates().upperLeftX + roomMinX, inA->GetCornerCoordinates().lowerRightX - roomMinX);
	

	FCornerCoordinates cornerCoordinatesB;
	cornerCoordinatesB.upperLeftX = inA->GetCornerCoordinates().upperLeftX;
	cornerCoordinatesB.upperLeftY = inA->GetCornerCoordinates().upperLeftY;
	cornerCoordinatesB.lowerRightY = inA->GetCornerCoordinates().lowerRightY;
	cornerCoordinatesB.lowerRightX = splitPointX;

	inB->SetCornerCoordinates(cornerCoordinatesB);
	floorNodeStack.Push(inB);

	FCornerCoordinates cornerCoordinatesC;
	cornerCoordinatesC.upperLeftX = splitPointX;
	cornerCoordinatesC.upperLeftY = inA->GetCornerCoordinates().upperLeftY;
	cornerCoordinatesC.lowerRightX = inA->GetCornerCoordinates().lowerRightX;
	cornerCoordinatesC.lowerRightY = inA->GetCornerCoordinates().lowerRightY;

	inC->SetCornerCoordinates(cornerCoordinatesC);
	floorNodeStack.Push(inC);

}

void Floor::DrawFloorNodes(UWorld* World)
{
	for (int32 i = 0; i < partitionedFloor.Num();i++)
	{
		FCornerCoordinates Coordinates = partitionedFloor[i]->GetCornerCoordinates();
		DrawFloorNode(World, Coordinates);
	}
}

void Floor::DrawFloorNode(UWorld* World, FCornerCoordinates Coordinates)
{
	const FVector UpperLeft(Coordinates.upperLeftX * unitLength, Coordinates.upperLeftY * unitLength, 0);
	const FVector UpperRight(Coordinates.lowerRightX * unitLength, Coordinates.upperLeftY * unitLength, 0);
	const FVector LowerLeft(Coordinates.upperLeftX * unitLength, Coordinates.lowerRightY * unitLength, 0);
	const FVector LowerRight(Coordinates.lowerRightX * unitLength, Coordinates.lowerRightY * unitLength, 0);

	DrawDebugLine(World, UpperLeft, UpperRight, FColor::Red, true, -1, 0, 1);
	DrawDebugLine(World, UpperLeft, LowerLeft, FColor::Red, true, -1, 0, 1);
	DrawDebugLine(World, LowerLeft, UpperRight, FColor::Red, true, -1, 0, 1);
	DrawDebugLine(World, UpperRight, LowerRight, FColor::Red, true, -1, 0, 1);
}

FVector Floor::GetRandomPointsInSide(const FVector UpperLeft, const FVector LowerRight)
{
	
	float randPointX = FMath::FRandRange(UpperLeft.X, LowerRight.X);
	float randPointY = FMath::FRandRange(UpperLeft.Y, LowerRight.Y);
	return FVector(randPointX, randPointY, 0);
}


void Floor::PlacePoints(UWorld* World)
{
	FCornerCoordinates Coordinates;
	Coordinates = FloorNode().GetCornerCoordinates();
	for (int32 i = 0; i < floorGridSizeX; i++)
	{
		for (int32 j = 0; j < floorGridSizeY; j++)
		{

			const FVector UpperLeft( Coordinates.upperLeftX  ,  Coordinates.upperLeftY  , 0);
			const FVector UpperRight( Coordinates.lowerRightX  ,  Coordinates.upperLeftY  , 0);
			const FVector LowerLeft(Coordinates.upperLeftX  ,  Coordinates.lowerRightY  , 0);
			const FVector LowerRight(Coordinates.lowerRightX  ,  Coordinates.lowerRightY  , 0);

			FVector newLeft = FVector(Coordinates.upperLeftX, Coordinates.upperLeftY, 0);
			FVector newRight = FVector(Coordinates.lowerRightX, Coordinates.lowerRightY, 0);

			FVector randPointinSquare = GetRandomPointsInSide(newLeft, newRight);
			DrawDebugPoint(World, randPointinSquare, 5, FColor::Green, true, -1, 100);
		}
	}
}


