#pragma once
#include <Common.h>
class IceCubeNew
{
public:

	enum mIceDirection {
		eIceMoveDown,
		eIceMoveUp,
		eIceMoveRight,
		eIceMoveLeft
	};

	IceCubeNew(int startRow, int startCol, mIceDirection dir, int blockType);
	~IceCubeNew();

	void Draw();
	void Update();
	void SetCustomLevel(CustomLevel* level);
	void Finish(); 
	
	CustomLevel* mCustomLevel;
	int mTextureID[2];
	int mBlockType;
	Vec2f mPosition;
	mIceDirection mDirection;
	float mVelocity;
	std::pair<int, int> GetCurrentCell();
	Vec2f GetCentreOfCell(int row, int col);
	std::pair<int, int> mPreviousCell;
	bool mPendingDelete;
};

