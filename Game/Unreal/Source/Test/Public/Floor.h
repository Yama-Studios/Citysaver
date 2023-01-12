#pragma once
#include "FloorNode.h"

enum class ESplitOrientation
{
	ESO_Horizontal,
	ESO_Vertical

};



class UWorld;
class FloorNode;

class Floor
{
public:
	Floor();
	~Floor();



	//functions
	void
		Partition(), // calls when we want to split the floor
		SplitHorizontal(TSharedPtr<FloorNode> inA, TSharedPtr<FloorNode> inB, TSharedPtr<FloorNode> inC),
		SplitVertical(TSharedPtr<FloorNode> inA, TSharedPtr<FloorNode> inB, TSharedPtr<FloorNode> inC),
		DrawFloorNodes(UWorld* World),
		DrawFloorNode(UWorld* World, FCornerCoordinates Coordinates),
		PlacePoints(UWorld* World);

	FVector
		GetRandomPointsInSide(FCornerCoordinates Coordinates);


	int32
		CoinFlip(); //need to return 0 or 1 randomlly
	
	
	bool
		ShouldSpiltNode(TSharedPtr<FloorNode> inNode, ESplitOrientation splitOrientation),
		SplitAttempt(TSharedPtr<FloorNode> inNode);



	//Getters
	FORCEINLINE TArray<TSharedPtr<FloorNode>> GetPartitionedFloor() const { return partitionedFloor; }


private:

	TArray<TSharedPtr<FloorNode>> floorNodeStack;
	TArray<TSharedPtr<FloorNode>> partitionedFloor;

	//Var
	int32
		floorGridSizeX,		// taking BottomRight Coordinates
		floorGridSizeY,		// taking BottomRight Coordinates
		roomMinX,			//least size or room (1 * 1 Square)
		roomMinY;			//least size or room (1 * 1 Square)

	float
		unitLength,
		splitChange;
};
