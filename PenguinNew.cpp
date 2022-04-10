#include "PenguinNew.h"
#include <iostream>
#include "PathFinder.h"
#include "Penguin.h"

PenguinNew::PenguinNew(CustomLevel* TempLevel)
{
	mMovementState = ePenguinMoveNone;
	mMovementStyleState = ePenguinWalk;
	mStrategy = eStrategyDefault;
	mPenguinMoveSpeed = 2.0f;
	mCustomLevel = TempLevel;
	int Counter = 0;
	int RandVal = rand() % 70; // why [0..69]? grid is 10 by 14

	for (int j = 0; j < RowCount; j++)
	{
		for (int i = 0; i < ColCount; i++)
		{
			if (mCustomLevel->LevelDesign[j][i] == FREE)
			{
				if (Counter == RandVal)
				{
					mPenguinPos.x = ((m_fRectSize + 1) * (i)+(m_fRectSize / 2));
					mPenguinPos.y = ((m_fRectSize + 1) * (j)+(m_fRectSize / 2));
					Counter++;
					break;
				}
				else
				{
					Counter++;
				}
			}
		}
	}
	mPreviousCell = GetPenguinRowColumn();
	//mOnStartCell = true;
	mCustomLevel->LevelDesign[mPreviousCell.first][mPreviousCell.second] = PENGUIN;
	//mCurrentPath = PathAStarFromMe(13, 0);
}

PenguinNew::~PenguinNew()
{
}

void PenguinNew::RenderPenguin() // Render penguin, but also run AI and subsequent movement. Essentially per frame updating of penguin. 
{
	float size = (m_fRectSize / 2);
	glPushMatrix();
	glTranslatef(mPenguinPos.x, mPenguinPos.y, 0);
	glBegin(GL_QUADS);						// Draw A Quad
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-size, -size, -2.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(size, -size, -2.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(size, size, -2.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-size, size, -2.0);
	glEnd();							// Done Drawing The Quad

	glPopMatrix();

	//Call AI and movement functions
	UpdateIceCubes();
	UpdateLevel(); //Remove blocks if penguin is on top of them, same as original does it
	MyPenguinController();
	UpdatePenguinMovement();
	//auto cell = GetPenguinRowColumn();
	//std::cout << "Penguin Row: " << cell.first << std::endl << "Penguin Col: " << cell.second << std::endl;

}

void PenguinNew::UpdatePenguinMovement() //Simply move penguin according to directional state 
{
	auto cell = GetPenguinRowColumn();
	auto centre = GetCentreOfCell(cell.first, cell.second);
	int speed = mPenguinMoveSpeed;

	if (mMovementStyleState == ePenguinRun) {
		speed = 2.0f * mPenguinMoveSpeed;
	}

	float thresh = speed;

	switch (mMovementState) {
	case(ePenguinMoveNone):
		//Don't move at all!
		break;

	case(ePenguinMoveUp):
		if (centre.x - mPenguinPos.x > thresh) {
			mPenguinPos.x += speed;
		}
		else if (centre.x - mPenguinPos.x < thresh) {
			mPenguinPos.x -= speed;
		}
		else {
			//mPenguinPos.x = centre.x;
			mPenguinPos.y += speed;
			if (mPenguinPos.y > MAX_HEIGHT - m_fRectSize / 2 - 18) { // Fixes penguin going off screen vertically. Shouldn't intefere with movement on that row.
				mPenguinPos.y = MAX_HEIGHT - m_fRectSize / 2 - 18;
			}
		}
		break;

	case(ePenguinMoveDown):
		if (centre.x - mPenguinPos.x > thresh) {
			mPenguinPos.x += speed;
		}
		else if (centre.x - mPenguinPos.x < thresh) {
			mPenguinPos.x -= speed;
		}
		else {
			//mPenguinPos.x = centre.x;
			mPenguinPos.y -= speed;
			if (mPenguinPos.y < m_fRectSize / 2) {
				mPenguinPos.y = m_fRectSize / 2;
			}
		}
		break;

	case(ePenguinMoveLeft):
		if (centre.y - mPenguinPos.y > thresh) {
			mPenguinPos.y += speed;
		}
		else if (centre.y - mPenguinPos.y < thresh) {
			mPenguinPos.y -= speed;
		}

		else {
			//mPenguinPos.y = centre.y;
			mPenguinPos.x -= speed;
			if (mPenguinPos.x < m_fRectSize / 2) {
				mPenguinPos.x = m_fRectSize / 2;
			}
		}

		break;

	case(ePenguinMoveRight):
		if (centre.y - mPenguinPos.y > thresh) {
			mPenguinPos.y += speed;
		}
		else if (centre.y - mPenguinPos.y < thresh) {
			mPenguinPos.y -= speed;
		}
		else {
			//mPenguinPos.y = centre.y;
			mPenguinPos.x += speed;
			if (mPenguinPos.x > MAX_WIDTH - m_fRectSize / 2 - 18) { // Fixes penguin going off screen horizontally. Shouldn't intefere with movement on that column.
				mPenguinPos.x = MAX_WIDTH - m_fRectSize / 2 - 18;
			}
		}

		break;
	}
}

void PenguinNew::UpdateLevel()
{
	auto cell = GetPenguinRowColumn();

	if (cell.first != mPreviousCell.first || cell.second != mPreviousCell.second) { // Change in cell
		//std::cout << "Change in cell!" << std::endl;
		mCustomLevel->LevelDesign[cell.first][cell.second] = PENGUIN;
		mCustomLevel->LevelDesign[mPreviousCell.first][mPreviousCell.second] = FREE; //Apply change in blocks the same way as original code. 
		mPreviousCell = cell;
	}

}

void PenguinNew::MyPenguinController()
{
	if (!all)
		beliefs();

	mStrategy = eStategyExplore;
	auto curPos = GetPenguinRowColumn();
	if (mStrategy == eStategyExplore)
	{
		checkForBess();


		std::pair<int, int>corners[4];
		corners[0] = std::make_pair(1, 0);
		corners[1] = std::make_pair(0, ColCount - 1);
		corners[2] = std::make_pair(RowCount - 1, 0);
		corners[3] = std::make_pair(RowCount - 2, ColCount - 1);
		int max = 0;
		int index = 0;
		for (int i = 0; i < 4;i++)
		{
			int rowDiff = abs(curPos.first - corners[i].first);
			int colDiff = abs(curPos.second - corners[i].second);

			if (rowDiff + colDiff > max)
			{
				max = rowDiff + colDiff;
				index = i;

			}
		}
		if (mCurrentExplorePath.empty())
		{
			mCurrentExplorePath = PathAStarFromMe(corners[index].first, corners[index].second);
			FollowExplorePath();
		}
		else
		{
			if (mCustomLevel->LevelDesign[mCurrentExplorePath.begin()->first][mCurrentExplorePath.begin()->second] == KILLER_BEE)
			{
				mCurrentExplorePath.clear();
				mCurrentExplorePath = PathAStarFromMe(corners[index].first, corners[index].second);
			}
			FollowExplorePath();
		}

	}

}

void PenguinNew::checkForBess()
{
	checkDownBee();
	checkLeftBee();
	checkUpBee();
	checkRightBee();
}
void PenguinNew::checkUpBee()
{
	auto x = GetPenguinRowColumn();
	int ice = 0;
	int z, y;
	for (int i = 1;i <= 5;i++)
	{
		if (mCustomLevel->LevelDesign[x.first + i][x.second] == KILLER_BEE)
		{
			for (int j = x.first + i;(j >= 0) && (j != x.first);j--)
			{
				if (mCustomLevel->LevelDesign[j - 1][x.second] == ICE_BLOCK || mCustomLevel->LevelDesign[j - 1][x.second] == DIAMOND_BLOCK)
				{
					z = 1;
					ice++;

				}
			}
		}


	}

	if (ice == 1)
	{
		PushCube(z, 0);
	}

}
void PenguinNew::checkLeftBee()
{
	auto x = GetPenguinRowColumn();
	int ice = 0;
	int z, y;
	for (int i = 1;i <= 5;i++)
	{
		if (mCustomLevel->LevelDesign[x.first][x.second - i] == KILLER_BEE)
		{

			for (int j = x.second - i;(j >= 0) && (j != x.second);j++)
			{
				if (mCustomLevel->LevelDesign[x.first][j + 1] == ICE_BLOCK || mCustomLevel->LevelDesign[x.first][j + 1] == DIAMOND_BLOCK)
				{
					z = -1;
					ice++;
				}
			}
		}


	}
	if (ice == 1)
	{
		PushCube(0, z);
	}
}
void PenguinNew::checkRightBee()
{
	auto x = GetPenguinRowColumn();
	int ice = 0;
	int z, y;
	for (int i = 1;i <= 5;i++)
	{
		if (mCustomLevel->LevelDesign[x.first][x.second + i] == KILLER_BEE)
		{

			for (int j = x.second + i;(j >= 0) && (j < x.second);j--)
			{
				if (mCustomLevel->LevelDesign[x.first][j - 1] == ICE_BLOCK || mCustomLevel->LevelDesign[x.first][j - 1] == DIAMOND_BLOCK)

				{
					z = 1;
					ice++;
				}
			}
		}


	}

	if (ice == 1)
	{
		PushCube(0, z);
	}
}

void PenguinNew::checkDownBee()
{
	auto x = GetPenguinRowColumn();
	int ice = 0;
	int z, y;
	for (int i = 1;i <= 5;i++)
	{
		if (mCustomLevel->LevelDesign[x.first - i][x.second] == KILLER_BEE)
		{
			for (int j = x.first - i;(j >= 0) && (j != x.first);j++)
			{
				if (mCustomLevel->LevelDesign[j + 1][x.second] == ICE_BLOCK || mCustomLevel->LevelDesign[j + 1][x.second] == DIAMOND_BLOCK)
				{
					z = -1;
					ice++;
				}
			}
		}
	}
	if (ice == 1)
	{
		PushCube(z, 0);
	}
}




void PenguinNew::starDirection()
{
	int	 mag1 = 0;
	std::pair<int, int> fu;

	for (auto it = starsPos.begin(); it != starsPos.end();++it)
	{
		for (auto i = starsPos.begin(); i != starsPos.end(); ++i)
		{
			int d = it->first - i->first;
			if (d > mag1)
			{
				fu.first = it->first;
				fu.second = it->second;
				mag1 = d;
			}
		}
	}

}

void PenguinNew::starSet(int destRow, int destCol)
{
	if (starsPos.empty())
	{
		starsPos.push_back(std::make_pair(destRow, destCol));
		return;
	}
	for (auto it = starsPos.begin();it != starsPos.end();++it)
	{
		if (it->first == destRow && it->second == destCol)
		{
			return;
		}
	}
	starsPos.push_back(std::make_pair(destRow, destCol));

}
void PenguinNew::beliefs()
{
	int destRow = 0;
	int destCol = 0;
	auto increX = 0;
	auto x = GetPenguinRowColumn();

	for (auto i = -5; i <= 5; i++)
	{
		for (auto h = -5; h <= 5; h++)
		{
			destRow = x.first - i;
			destCol = x.second + h;
			if (destRow < 0 || destCol < 0 || destRow >= RowCount || destCol >= ColCount)
				continue;
			if (mCustomLevel->LevelDesign[x.first - i][x.second + h] == DIAMOND_BLOCK)
			{
				starSet(destRow, destCol);
				increX++;
			}

		}
	}
}



void PenguinNew::SetPenguinPosition(int x, int y) //column row, actually
{
	mPenguinPos.x = ((m_fRectSize + 1) * (x)+(m_fRectSize / 2));
	mPenguinPos.y = ((m_fRectSize + 1) * (y)+(m_fRectSize / 2));
}

void PenguinNew::UpdateIceCubes()
{
	for (auto it = mIceCubes.begin(); it != mIceCubes.end();) {
		it->Update();
		if (it->mPendingDelete) {
			it = mIceCubes.erase(it);
		}
		else {
			++it;
		}
	}
}

std::pair<int, int> PenguinNew::GetPenguinRowColumn()
{
	int row = 0;
	int col = 0;

	int cumulative = 46;
	while (mPenguinPos.y > cumulative) {
		row++;
		cumulative += 46;
	}
	cumulative = 46;
	while (mPenguinPos.x > cumulative) {
		col++;
		cumulative += 46;
	}
	return std::pair<int, int>(row, col);
}

int PenguinNew::GetBlockInDirection(int x, int y)
{
	auto cell = GetPenguinRowColumn();
	x += cell.second;
	y += cell.first;
	if (y >= RowCount || y < 0 || x >= ColCount || x < 0) {
		return OUT_OF_BOUNDS
	}
	else {
		return mCustomLevel->LevelDesign[y][x];
	}
}



void PenguinNew::FollowPath()
{
	/*int destX = path.front().second * (m_fRectSize + 1) + m_fRectSize / 2;
	int destY = path.front().first * (m_fRectSize + 1) + m_fRectSize / 2;
	float dist = (mPenguinPos - Vec2f(destX, destY)).Length();
	if (dist < 1.0f) {
		path.erase(path.begin());
	}*/

	if (mCurrentPath.empty()) {
		return;
	}

	auto cell = GetPenguinRowColumn();

	if (cell.first == mCurrentPath.front().first && cell.second == mCurrentPath.front().second) {
		mCurrentPath.erase(mCurrentPath.begin());
		return;
	}

	int rowDiff = mCurrentPath.front().first - cell.first;
	int colDiff = mCurrentPath.front().second - cell.second;


	if (rowDiff == 1) {
		mMovementState = ePenguinMoveUp;
	}
	else if (rowDiff == -1) {
		mMovementState = ePenguinMoveDown;
	}

	else if (colDiff == 1) {
		mMovementState = ePenguinMoveRight;
	}
	else if (colDiff == -1) {
		mMovementState = ePenguinMoveLeft;
	}
	else {
		// BAD PATH
	}
}

void PenguinNew::FollowExplorePath()
{
	/*int destX = path.front().second * (m_fRectSize + 1) + m_fRectSize / 2;
	int destY = path.front().first * (m_fRectSize + 1) + m_fRectSize / 2;
	float dist = (mPenguinPos - Vec2f(destX, destY)).Length();
	if (dist < 1.0f) {
		path.erase(path.begin());
	}*/

	if (mCurrentExplorePath.empty()) {
		return;
	}

	auto cell = GetPenguinRowColumn();

	if (cell.first == mCurrentExplorePath.front().first && cell.second == mCurrentExplorePath.front().second) {
		mCurrentExplorePath.erase(mCurrentExplorePath.begin());
		return;
	}

	int rowDiff = mCurrentExplorePath.front().first - cell.first;
	int colDiff = mCurrentExplorePath.front().second - cell.second;

	if (rowDiff == 1) {
		mMovementState = ePenguinMoveUp;
	}
	else if (rowDiff == -1) {
		mMovementState = ePenguinMoveDown;
	}

	else if (colDiff == 1) {
		mMovementState = ePenguinMoveRight;
	}
	else if (colDiff == -1) {
		mMovementState = ePenguinMoveLeft;
	}
	else {
		// BAD PATH
	}
}

Path PenguinNew::PathAStarFromMe(int destRow, int destCol)
{
	auto cell = GetPenguinRowColumn();
	return PathFinder::PathAStar(cell.first, cell.second, destRow, destCol);
}

Vec2f PenguinNew::GetCentreOfCell(int row, int col)
{
	return Vec2f(
		(m_fRectSize + 1) * col + m_fRectSize / 2,
		(m_fRectSize + 1) * row + m_fRectSize / 2
	);
}

void PenguinNew::PushCube(int rowDir, int colDir)
{
	auto cell = GetPenguinRowColumn();
	auto cell_over(cell);
	cell_over.first += rowDir;
	cell_over.second += colDir;
	auto cell_over_two(cell_over);
	cell_over_two.first += rowDir;
	cell_over_two.second += colDir;

	int nextBlock = mCustomLevel->LevelDesign[cell_over.first][cell_over.second];
	int nextBlockTwo = mCustomLevel->LevelDesign[cell_over_two.first][cell_over_two.second];
	IceCubeNew::mIceDirection dir;

	if (rowDir == 1) {
		dir = IceCubeNew::eIceMoveUp;
	}
	else if (rowDir == -1) {
		dir = IceCubeNew::eIceMoveDown;
	}
	else if (colDir == 1) {
		dir = IceCubeNew::eIceMoveRight;
	}
	else if (colDir == -1) {
		dir = IceCubeNew::eIceMoveLeft;
	}

	if (nextBlock == ICE_BLOCK || nextBlock == DIAMOND_BLOCK) {
		if (nextBlockTwo != ICE_BLOCK && nextBlockTwo != DIAMOND_BLOCK) {
			mCustomLevel->LevelDesign[cell_over.first][cell_over.second] = MOVING_BLOCK;
			IceCubeNew ic(cell_over.first, cell_over.second, dir, nextBlock);
			ic.SetCustomLevel(mCustomLevel);
			mIceCubes.push_back(ic);
		}
	}
}
