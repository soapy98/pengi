#include "IceCubeNew.h"

IceCubeNew::IceCubeNew(int startRow, int startCol, mIceDirection dir, int blockType)
{
	mPosition = GetCentreOfCell(startRow, startCol);
	mDirection = dir;
	mVelocity = 3.0f;
	mBlockType = blockType;
	mPreviousCell = GetCurrentCell();
	mPendingDelete = false;

	mTextureID[0] = tgaLoadAndBind(".\\Images/iceBlock.tga", TGA_DEFAULT);
	mTextureID[1] = tgaLoadAndBind(".\\Images/DiamondBlock.tga", TGA_DEFAULT);
}


IceCubeNew::~IceCubeNew()
{
}

void IceCubeNew::Draw()
{
	float	size = (m_fRectSize / 2);
	switch (mBlockType) {
	case ICE_BLOCK:
		glBindTexture(GL_TEXTURE_2D, mTextureID[0]);
		break;

	case DIAMOND_BLOCK:
		glBindTexture(GL_TEXTURE_2D, mTextureID[1]);
		break;

	default:
		glBindTexture(GL_TEXTURE_2D, mTextureID[0]);
		break;
	}

	glPushMatrix();
		glTranslatef(mPosition.x, mPosition.y, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-size, -size, -1.5);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(size, -size, -1.5);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(size, size, -1.5);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-size, size, -1.5);
		glEnd();
	glPopMatrix();
}

void IceCubeNew::Update()
{
	Draw();
	if (mPendingDelete)
		return;

	auto cell = GetCurrentCell();
	std::pair<int, int> cell_over(cell);

	switch (mDirection) {
		case (eIceMoveDown):
			mPosition.y -= mVelocity;
			cell_over.first -= 1;
		break;
		case (eIceMoveUp):
			mPosition.y += mVelocity;
			cell_over.first += 1;
			break;
		case (eIceMoveRight):
			mPosition.x += mVelocity;
			cell_over.second += 1;
			break;
		case (eIceMoveLeft):
			mPosition.x -= mVelocity;
			cell_over.second -= 1;
			break;
	}

	int nextRow = cell_over.first;
	int nextCol = cell_over.second;
	int nextBlock = mCustomLevel->LevelDesign[nextRow][nextCol];
	if (nextRow >= RowCount || nextRow < 0 ||
		nextCol >= ColCount || nextCol < 0 ||
		nextBlock == ICE_BLOCK || nextBlock == DIAMOND_BLOCK) {
		Finish();
	}
	else if (cell.first != mPreviousCell.first || cell.second != mPreviousCell.second) {
		int block = mCustomLevel->LevelDesign[cell.first][cell.second];
		mCustomLevel->LevelDesign[mPreviousCell.first][mPreviousCell.second] = FREE;
		mCustomLevel->LevelDesign[cell.first][cell.second] = MOVING_BLOCK;
		mPreviousCell = cell;
	}
}

void IceCubeNew::SetCustomLevel(CustomLevel* level)
{
	mCustomLevel = level;
}

void IceCubeNew::Finish()
{
	auto cell = GetCurrentCell();
	mCustomLevel->LevelDesign[mPreviousCell.first][mPreviousCell.second] = FREE;
	mCustomLevel->LevelDesign[cell.first][cell.second] = mBlockType;
	mPendingDelete = true;
}

std::pair<int, int> IceCubeNew::GetCurrentCell()
{
	int row = 0;
	int col = 0;

	int cumulative = 46;
	while (mPosition.y > cumulative) {
		row++;
		cumulative += 46;
	}
	cumulative = 46;
	while (mPosition.x > cumulative) {
		col++;
		cumulative += 46;
	}
	return std::pair<int, int>(row, col);
}

Vec2f IceCubeNew::GetCentreOfCell(int row, int col)
{
	return Vec2f(
		(m_fRectSize + 1) * col + m_fRectSize / 2,
		(m_fRectSize + 1) * row + m_fRectSize / 2
	);
}
