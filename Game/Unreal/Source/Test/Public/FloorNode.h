#pragma once

struct FCornerCoordinates
{
	int
		upperLeftX,
		upperLeftY,
		lowerRightX,
		lowerRightY;
};



class FloorNode
{
public:
	FloorNode(const FCornerCoordinates& coordinates);
	FloorNode();
	~FloorNode();

	//Setters & Getters
	FORCEINLINE FCornerCoordinates GetCornerCoordinates() const {return cornerCoordinates;}
	FORCEINLINE void SetCornerCoordinates(FCornerCoordinates Coordinates) {	cornerCoordinates = Coordinates; }
	FORCEINLINE static int32 GetNodeCount() { return floorNodeCount; }



protected:

private:
	FCornerCoordinates cornerCoordinates;

	static int32 floorNodeCount;

};
