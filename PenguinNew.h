#pragma once
#include "Common.h"
#include "IceCube.h"
#include "PathFinder.h"
#include "IceCubeNew.h"

class PenguinNew
{
public:

	enum mPenguinStrategicState {
		eStrategyDefault,
		eStrategyDead,
		eStategyExplore
	};

	enum mPenguinMovementState {
		ePenguinMoveNone,
		ePenguinMoveUp,
		ePenguinMoveDown,
		ePenguinMoveRight,
		ePenguinMoveLeft,
	};

	enum mPenguinMovementStyleState {
		ePenguinWalk,
		ePenguinRun
	};

	Vec2f mPenguinPos; 
	float mPenguinMoveSpeed; 
	mPenguinMovementState mMovementState;
	mPenguinMovementStyleState mMovementStyleState;
	CustomLevel* mCustomLevel;
	std::pair<int, int> mPreviousCell;
	Path mCurrentPath;
	Path mCurrentExplorePath;
	std::vector<IceCubeNew> mIceCubes; 
	mPenguinStrategicState mStrategy;

	PenguinNew(CustomLevel* TempLevel);
	~PenguinNew();

	void RenderPenguin();
	void UpdatePenguinMovement();
	void UpdateLevel();
	void MyPenguinController();
	void SetPenguinPosition(int, int);
	void UpdateIceCubes();
	std::pair<int, int> GetPenguinRowColumn();
	int GetBlockInDirection(int x, int y);
	void FollowPath();
	void FollowExplorePath();
	Path PathAStarFromMe(int destRow, int destCol);
	Vec2f GetCentreOfCell(int row, int col);
	void PushCube(int rowDir, int colDir);
	void starSet(int destRow, int destCol);
	void beliefs();
	int stars[3][2];
	std::vector<std::pair<int, int>> starsPos;
	void checkForBess();
	void checkUpBee();
	void checkDownBee();
	void checkLeftBee();
	void checkRightBee();
	void starDirection();

	bool safeLeft();
	bool safeRight();
	bool safeUp();
	bool safeDown();
	
	bool all = false;
	std::vector<std::pair<int, int>>beesPos;
	void beessPos();
};

