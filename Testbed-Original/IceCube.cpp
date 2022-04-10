#include "IceCube.h"

IceCube::IceCube(void)
{
	m_fMoveSpeed	= 3;
}

IceCube::IceCube( Vec2f StartPos, Vec2f EndPos, int CurrentRowID, int CurrentColID)	{

	m_vPosition		= StartPos;			//	Current Position of the ice cube
	m_vEndPosition	= EndPos;			//	Expected End Position of the Ice Cube

	m_iCurrentRowID	= CurrentRowID;
	m_iCurrentColID	= CurrentColID;

	m_fMoveSpeed	= 3;

	m_iCurrentIceID	= -1;

	m_eMoveDirection	= eMoveCreated;
	// mTextureID defined as int array[2] but not indexed correctly here
	// BUT ICE_BLOCK defined as 1 - use LOCAL_IceCube_TXEXTURE
	// BUT DIAMOND_BLOCK defined as 8 (hence DIAMOND_BLOCK-DIAMOND_BLOCK) - use LOCAL_Diamond_TXEXTURE 
	mTextureID[LOCAL_IceCube_TXEXTURE]		= tgaLoadAndBind ( ".\\Images/iceBlock.tga",TGA_DEFAULT);
	mTextureID[LOCAL_Diamond_TXEXTURE]	= tgaLoadAndBind ( ".\\Images/DiamondBlock.tga",TGA_DEFAULT);

}

IceCube::~IceCube(void)	{
}

void IceCube::setDirection ( mMoveDirection MoveDir) {
	m_eMoveDirection	= MoveDir;
}

void IceCube::MoveIceCube()	{

	float Pos	= 0.0;
	if (Print_Verbose) printf("Into MoveIceCube\n");
	switch ( m_eMoveDirection ) {
		case eMoveUp:
			m_vPosition.y	+= m_fMoveSpeed;
			if ( (m_vPosition.y > m_vEndPosition.y) ){
				m_vPosition.y		= m_vEndPosition.y;
				m_eMoveDirection	= eDone;
			}
			Pos	= ((m_fRectSize+1)*(RowCount-1)+(m_fRectSize/2));
			if (m_vPosition.y > Pos ){		// If the Ice reached the End of the Grid
				m_vPosition.y		= Pos;
				m_eMoveDirection	= eDone;
			}
			break;
		case eMoveLeft:
			m_vPosition.x	-= m_fMoveSpeed;
			if ( (m_vPosition.x < m_vEndPosition.x) ){		// if the End Condtion is meet
				m_vPosition.x		= m_vEndPosition.x;
				m_eMoveDirection	= eDone;
			}
			if ((m_vPosition.x < (m_fRectSize/2)) ){		// If the Ice reached the End of the Grid
				m_vPosition.x		= (m_fRectSize/2);
				m_eMoveDirection	= eDone;
			}
			break;
		case eMoveDown:
			m_vPosition.y	-= m_fMoveSpeed;
			if ( (m_vPosition.y < m_vEndPosition.y) ){
				m_vPosition.y		= m_vEndPosition.y;
				m_eMoveDirection	= eDone;
			}
			if ((m_vPosition.y < (m_fRectSize/2)) ){		// If the Ice reached the End of the Grid
				m_vPosition.y		= (m_fRectSize/2);
				m_eMoveDirection	= eDone;
			}
			break;
		case eMoveRight:
			m_vPosition.x	+= m_fMoveSpeed;
			if ( (m_vPosition.x > m_vEndPosition.x) ){
				m_vPosition.x		= m_vEndPosition.x;
				m_eMoveDirection	= eDone;
			}
			Pos	= ((m_fRectSize+1)*(ColCount)+(m_fRectSize/2));
			if (m_vPosition.x > Pos ){		// If the Ice reached the End of the Grid
				m_vPosition.x		= Pos;
				m_eMoveDirection	= eDone;
			}
			break;
	}
}

void IceCube::DrawIceCube()	{
	MoveIceCube();
	CalculateCurrentCellID();

	float	size	= (m_fRectSize/2);
	switch (m_iCurrentIceID){
		case ICE_BLOCK:
			glBindTexture(GL_TEXTURE_2D,mTextureID [ LOCAL_IceCube_TXEXTURE ]);
			break;

		case DIAMOND_BLOCK:
			glBindTexture(GL_TEXTURE_2D,mTextureID [ LOCAL_Diamond_TXEXTURE ]);
			break;

		default: 
			glBindTexture(GL_TEXTURE_2D,mTextureID [ LOCAL_IceCube_TXEXTURE ]);
			break;
	}

	glPushMatrix();
		glTranslatef(m_vPosition.x,m_vPosition.y,0);
		glBegin (GL_QUADS);
			glTexCoord2f (0.0, 0.0);
			glVertex3f (-size, -size, -1.5);
			glTexCoord2f (1.0, 0.0);
			glVertex3f (size, -size, -1.5);
			glTexCoord2f (1.0, 1.0);
			glVertex3f (size, size, -1.5);
			glTexCoord2f (0.0, 1.0);
			glVertex3f (-size, size, -1.5);
		glEnd();
	glPopMatrix();
}

void IceCube::setEndCellID (int RowID, int ColID) {
	m_iEndRowID	= RowID;
	m_iEndColID	= ColID;
}

Vec2f IceCube::getCurrentPos()	{
	return m_vPosition;
}
Vec2f IceCube::getCurrentCellID()	{
	CalculateCurrentCellID();

	Vec2f	mCurrentCeelID;
	mCurrentCeelID.x	= m_iCurrentRowID;
	mCurrentCeelID.y	= m_iCurrentColID;
	return	mCurrentCeelID;
}


void IceCube::CalculateCurrentCellID ()	{
	int PreviousRowID, PreviousColID;
	PreviousRowID	= m_iCurrentRowID;
	PreviousColID	= m_iCurrentColID;
	for (int j = 0; j < RowCount; j++){
		int PosY	= ((m_fRectSize+1)*(j)+m_fRectSize/2);
		if( abs(m_vPosition.y-PosY) < m_fRectSize/2 ){
			m_iCurrentRowID	= j;
			break;
		}
	}

	for (int i = 0; i < ColCount; i++){
		int	PosX	 = ((m_fRectSize+1)*(i)+m_fRectSize/2);
		if( abs(m_vPosition.x-PosX) < m_fRectSize/2 ){
			m_iCurrentColID	= i;
			break;
		}
	}
	m_pCustomLevel->LevelDesign[PreviousRowID][PreviousColID]	= FREE;

	m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID]	= MOVING_BLOCK;
}

void IceCube::setCustLevelObj ( CustomLevel* Level ) {
	m_pCustomLevel	= Level;


	/*for (int i = 0; i < RowCount;i++){
		for(int j = 0; j< ColCount; j++){
			printf(" m_pCustomLevel[%d][%d] = %d",i,j,m_pCustomLevel->LevelDesign[i][j]);
		}
		printf("\n");
	}*/
}