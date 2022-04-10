#include "CustomLevel.h"

CustomLevel::CustomLevel(void)
{

	/*
		Note: 
			1 = Static Ice Block
			0 = Empty Space
			2 = Penguin Postion in the Level
			3 = Bee Postion in the Level
			4 = Moving IceCube
			5 = Dead Bee
			8 = DiamondIceCube

		if the Gap between Bee & the Penguin is less than 3 cell the Bee Speed will increase as he will switch to attack mode from Normal Mode
	*/	
	int Temp_LevelDesign[RowCount][ColCount]	= {
		{1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
		{0, 1, 1, 0, 1, 0, 1, 1, 1, 0},
		{0, 0, 0, 0, 1, 0, 0, 8, 0, 0},
		{0, 1, 0, 1, 0, 0, 8, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
		{0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
		{1, 1, 1, 0, 0, 1, 0, 0, 1, 0},
		{1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
		{1, 1, 0, 0, 1, 0, 0, 0, 1, 1},
		{0, 1, 0, 1, 1, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 8, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0, 1, 1}
	};

	mTextureID [ TXTR_ICE_BLOCK ]		= tgaLoadAndBind ( "Images/iceBlock.tga",TGA_DEFAULT);
	mTextureID [ TXTR_DIAMOND_BLOCK ]	= tgaLoadAndBind ( "Images/DiamondBlock.tga",TGA_DEFAULT);

	for( int i = 0; i < RowCount; i++){
		for( int j = 0; j < ColCount; j++){
			LevelDesign[i][j]	= Temp_LevelDesign[i][j];
		}
	}
}

CustomLevel::~CustomLevel(void)
{
}


void CustomLevel::DrawLevel () {

	float	size = (m_fRectSize/2);
	for (int j = 0; j < RowCount; j++){
		for (int i = 0; i < ColCount; i++){
			if (LevelDesign[j][i] == ICE_BLOCK) {
				glBindTexture(GL_TEXTURE_2D,mTextureID [ TXTR_ICE_BLOCK ]);
				glPushMatrix();
					glTranslatef(((m_fRectSize+1)*(i)+(m_fRectSize/2)),((m_fRectSize+1)*(j)+(m_fRectSize/2)),0);

					glBegin (GL_QUADS);
						glTexCoord2f (0.0, 0.0);
						glVertex3f (-size, -size, -2.0);
						glTexCoord2f (1.0, 0.0);
						glVertex3f (size, -size, -2.0);
						glTexCoord2f (1.0, 1.0);
						glVertex3f (size, size, -2.0);
						glTexCoord2f (0.0, 1.0);
						glVertex3f (-size, size, -2.0);
					glEnd ();
					
				glPopMatrix();
			}else if (LevelDesign[j][i] == DIAMOND_BLOCK) {
				glBindTexture(GL_TEXTURE_2D,mTextureID [ TXTR_DIAMOND_BLOCK ]);
				glPushMatrix();
					glTranslatef(((m_fRectSize+1)*(i)+(m_fRectSize/2)),((m_fRectSize+1)*(j)+(m_fRectSize/2)),0);

					glBegin (GL_QUADS);
						glTexCoord2f (0.0, 0.0);
						glVertex3f (-size, -size, -2.0);
						glTexCoord2f (1.0, 0.0);
						glVertex3f (size, -size, -2.0);
						glTexCoord2f (1.0, 1.0);
						glVertex3f (size, size, -2.0);
						glTexCoord2f (0.0, 1.0);
						glVertex3f (-size, size, -2.0);
					glEnd ();
					
				glPopMatrix();
			}
		}
	}
}