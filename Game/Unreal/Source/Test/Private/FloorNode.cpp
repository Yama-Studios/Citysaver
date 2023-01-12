#include "FloorNode.h"

int32 FloorNode::floorNodeCount = 0;



FloorNode::FloorNode(const FCornerCoordinates& coordinates)
{
	++floorNodeCount;
	cornerCoordinates.upperLeftX = coordinates.upperLeftX;
	cornerCoordinates.upperLeftY = coordinates.upperLeftY;
	cornerCoordinates.lowerRightX = coordinates.lowerRightX;
	cornerCoordinates.lowerRightY = coordinates.lowerRightY;
	UE_LOG(LogTemp, Warning, TEXT("FloorNode Created"));
}

FloorNode::FloorNode()
{
	++floorNodeCount;
	UE_LOG(LogTemp, Warning, TEXT("FloorNode Created"));
}

FloorNode::~FloorNode()
{
	--floorNodeCount;
	UE_LOG(LogTemp, Warning, TEXT("FloorNode Destroyed"));
}
