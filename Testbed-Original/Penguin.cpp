// This is the Main File for the Penguin Controller
// Modified by DND
#include "Penguin.h"
#include <algorithm>
#include <string>
#include <iostream>

Penguin::Penguin(void){

	/*m_fPenguinMoveSpeed	= 1;
	m_iCurrentRowID	= -1;
	m_iCurrentColID	= -1;
	m_ePenguinState		= m_ePreviousPenguinState	= ePenguinCreated;

	int Counter = 0;
	int RandVal	= rand() % 70; // why [0..69]? grid is 10 by 14
	for (int j = 0; j < RowCount; j++)
	{
		for (int i = 0; i < ColCount; i++)
		{
			m_knownWorld[i][j] = UNKNOWN;
			if( m_pCustomLevel->LevelDesign[j][i] == FREE)
			{
				if(Counter == RandVal)
				{
					mPenguinPos.x	=((m_fRectSize+1)*(i)+(m_fRectSize/2));
					mPenguinPos.y	=((m_fRectSize+1)*(j)+(m_fRectSize/2));
					CalculateCurrentCell();
					Counter++;
					break;
				}
				else
				{
					Counter++;
				}
			}
		}
	}*/
}

Penguin::Penguin(CustomLevel * TempLevel ){

	m_pIceCube_1	= NULL;
	m_pIceCube_2	= NULL;
	m_pIceCube_3	= NULL;
	m_pIceCube_4	= NULL;

	m_pCustomLevel			= TempLevel;
	m_ePenguinStragicState	= ePenguinNormal;

	m_fPenguinMoveSpeed	= 1;
	m_iCurrentRowID	= -1;
	m_iCurrentColID	= -1;
	m_ePenguinState		= m_ePreviousPenguinState	= ePenguinCreated;
	m_ePenguinState		= ePenguinMoveDown;

	int Counter = 0;
	int RandVal	= rand() % 70; // why [0..69]? grid is 10 by 14
	for (int j = 0; j < RowCount; j++)
	{
		for (int i = 0; i < ColCount; i++)
		{
			if( m_pCustomLevel->LevelDesign[j][i] == FREE)
			{
				if(Counter == RandVal)
				{
					mPenguinPos.x	=((m_fRectSize+1)*(i)+(m_fRectSize/2));
					mPenguinPos.y	=((m_fRectSize+1)*(j)+(m_fRectSize/2));
					CalculateCurrentCell();
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
}

Penguin::~Penguin(void)
{
}


void Penguin::setPenguinPosition(int X, int Y)
{
	mPenguinPos.x	= ((m_fRectSize+1)*(X)+(m_fRectSize/2));
	mPenguinPos.y	= ((m_fRectSize+1)*(Y)+(m_fRectSize/2));
	CalculateCurrentCell();
}

void Penguin::CalculateCurrentCell() {

	int PreviousRow, PreviousCol;
	PreviousRow	= m_iCurrentRowID; 
	PreviousCol = m_iCurrentColID;

	for (int j = 0; j < RowCount; j++)
	{
		int PosY	= ((m_fRectSize+1)*(j)+m_fRectSize/2);
		if( abs(mPenguinPos.y-PosY) < m_fRectSize/2 )
		{
			m_iCurrentRowID	= j;
			break;
		}
	}

	for (int i = 0; i < ColCount; i++)
	{
		int	PosX	 = ((m_fRectSize+1)*(i)+m_fRectSize/2);
		if( abs(mPenguinPos.x-PosX) < m_fRectSize/2 )
		{
			m_iCurrentColID	= i;
			break;
		}
	}

	//	Setting the Current Penguin Postion in the Grid.
	if ( (m_pCustomLevel->LevelDesign[PreviousRow][PreviousCol] != ICE_BLOCK) || 
		 (m_pCustomLevel->LevelDesign[PreviousRow][PreviousCol] != DIAMOND_BLOCK) )
	{
		m_pCustomLevel->LevelDesign[PreviousRow][PreviousCol]	=  FREE;
	}
	m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID]	=  PENGUIN;
	CheckForBees();
	///-------------
	switch ( m_ePenguinState )
	{
	case ePenguinMoveUp:
		{
		if((m_vExpectedPos.y-mPenguinPos.y) < 0)
		{
			CheckForBees();
			calculateNewPath ();
		}
		break;
		}
	case ePenguinMoveDown:
		{
		if((mPenguinPos.y - m_vExpectedPos.y) < 0)
		{
			CheckForBees();
			calculateNewPath ();
		}
		break;
		}
	case ePenguinMoveRight:
		{
		if((m_vExpectedPos.x - mPenguinPos.x ) < 0)
		{
			CheckForBees();
			calculateNewPath ();
		}
		break;
		}
	case ePenguinMoveLeft:
		{
		if((mPenguinPos.x - m_vExpectedPos.x) < 0)
		{
			CheckForBees();
			calculateNewPath ();
		}
		break;
		}
	}
	// Used at start-up
	if( ( m_vExpectedPos.x == 0) && (m_vExpectedPos.y == 0))
	{
		CheckForBees();
		calculateNewPath ();
	}

}

// calculateNewPath - Top Level "AI" Decision Algorithm
// In effect Random number to decide upon between PathFinding1 and PathFinding2
// This Function (calculateNewPath) is modified with call to improved Algorithm MyPenguinController()
// PathFinding1 and PathFinding2 are left as is BUT not called
void Penguin::calculateNewPath() {
/*	int RandDirection;
	RandDirection	= rand() % 2;		// Generating Random number in range [0,1]
	if (Print_Verbose) printf("Random Direction for Penguin in calculateNewPath: %d\n", RandDirection);
	if ( RandDirection < 1 )
		PathFinding1 ();
	else
		PathFinding2 ();
		*/
// For ACW comment out above lines and uncomment following call
//	MyPenguinController();

}

//-----------------------------------------------------------------------------------------
// THIS IS THE FUNCTION WHERE YOU ADD YOUR TOP LEVEL CODE
void Penguin::MyPenguinController() {
	//std::cout << "Penguin X " << mPenguinPos.x << std::endl;
	//std::cout << "Penguin Y " << mPenguinPos.y << std::endl;

	if (path.size() > 0) { // if path exists
		//calculateNewPosition();
		int nextRow = path.front().first;
		int nextCol = path.front().second;
		int nextX = nextCol * (m_fRectSize + 1) + m_fRectSize / 2;
		int nextY = nextRow * (m_fRectSize + 1) + m_fRectSize / 2;

		float dX = nextX - mPenguinPos.x;
		float dY = nextY - mPenguinPos.y;

		Vec2f dV(dX, dY);

		float distance = dV.Length();
		if (distance < 0.3f) {
			//mPenguinPos.x = nextX;
			//mPenguinPos.y = nextY;
			path.erase(path.begin());
		}
		else {
			auto dir = dV.Normalize();
			mPenguinPos += dir * m_fPenguinMoveSpeed;
		}
	}
}


/*
	Both PathFinding1 and PathFinding2 are niave algorithms that lead to poor direction choices
	Supposedly work as follows:
	1-first get the current pos of the Penguin
	2-Now decide if you want to move in Row Or col
	3-Once this is decide than decide if you want to go right or left
	4-once this is decided than Find the last Empty Slot in the Penguins current row.
		4.1- if there is no cell to move in the current direction than again start from step 2.
		4.2- else if you find the last empty cell without any obstraction than set the movement direction to it.
	5- Once you start the movement continously check the distance detween the Penguin pos & the expected pos.
		5.1- once it reaches zero start over from step 2
	*/
void Penguin::PathFinding2 ()
{
	int		Round = 0;
	bool	PathSelectionDone	= false;
	mPenguinStates	Temp_PenguinState;
	Temp_PenguinState	= m_ePenguinState;			// Setting The Temp_PenguinState to the Current Penguin State
	if (Print_Verbose) 
		printf("PenguinState in PathFindingAlgo_2: %d\n", Temp_PenguinState);
	while (!PathSelectionDone)	
	{
		switch (Round){
			case 0:
			case 1:
			case 2:
			case 3:
				switch (Temp_PenguinState){
					case ePenguinMoveUp:
						if (m_ePenguinState	== ePenguinMoveDown){
							///	Checking wht is the current Penguin movement direction 
							// this is to avoide the Penguin to Move is opposite direction Unless 
							// & until He comes in for the Second Round
							Temp_PenguinState	= ePenguinMoveRight;
							Round++;
							break;
						}

						if( ((m_iCurrentRowID+1) >= RowCount) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID+1][m_iCurrentColID] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID+1][m_iCurrentColID] == DIAMOND_BLOCK)){
							Temp_PenguinState	= ePenguinMoveRight;
							Round++;
						}else{
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID+1)+(m_fRectSize/2));
							if(m_vExpectedPos.x == 0){ 
								m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID))+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
					case ePenguinMoveRight:
						if (m_ePenguinState	== ePenguinMoveLeft){
							///	Checking wht is the current Penguin movement direction this is to avoide the Penguin to Move is opposite direction Unless & until He comes in for the Second Round
							Temp_PenguinState	= ePenguinMoveDown;
							Round++;
							break;
						}
						if( ((m_iCurrentColID+1) >= ColCount ) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID+1] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID+1] == DIAMOND_BLOCK)){
							Temp_PenguinState	= ePenguinMoveDown;
							Round++;
						}else{
							m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID+1))+(m_fRectSize/2));
							if(m_vExpectedPos.y == 0){
								m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
					case ePenguinMoveDown:
						if (m_ePenguinState	== ePenguinMoveUp){
							///	Checking wht is the current Penguin movement direction this is to avoide the Penguin to Move is opposite direction Unless & until He comes in for the Second Round
							Temp_PenguinState	= ePenguinMoveLeft;
							Round++;
							break;
						}
						if( ((m_iCurrentRowID-1) < 0 ) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID-1][m_iCurrentColID] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID-1][m_iCurrentColID] == DIAMOND_BLOCK))
						{
							Temp_PenguinState	= ePenguinMoveLeft;
							Round++;
						}
						else
						{
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID-1)+(m_fRectSize/2));
							if(m_vExpectedPos.x == 0){ 
								m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID))+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
					case ePenguinMoveLeft:
						if (m_ePenguinState	== ePenguinMoveRight){
							///	Checking wht is the current Penguin movement direction this is to avoide the Penguin to Move is opposite direction Unless & until He comes in for the Second Round
							Temp_PenguinState	= ePenguinMoveUp;
							Round++;
							break;
						}
						if( ((m_iCurrentColID-1) < 0 ) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID-1] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID-1] == DIAMOND_BLOCK)){
							Temp_PenguinState	= ePenguinMoveUp;
							Round++;
						}else {
							m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID-1))+(m_fRectSize/2));
							if(m_vExpectedPos.y == 0){
								m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
				}	////	End Of Internal Switch
				break;

			case 4:
			case 5:
			case 6:
			case 7:
				switch (Temp_PenguinState){
					case ePenguinMoveUp:
						if( ((m_iCurrentRowID+1) >= RowCount) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID+1][m_iCurrentColID] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID+1][m_iCurrentColID] == DIAMOND_BLOCK)){
							Temp_PenguinState	= ePenguinMoveRight;
							Round++;
						}else{
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID+1)+(m_fRectSize/2));
							if(m_vExpectedPos.x == 0){ 
								m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID))+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
					case ePenguinMoveRight:
						if( ((m_iCurrentColID+1) >= ColCount ) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID+1] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID+1] == DIAMOND_BLOCK)){
							Temp_PenguinState	= ePenguinMoveDown;
							Round++;
						}else{
							m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID+1))+(m_fRectSize/2));
							if(m_vExpectedPos.y == 0){
								m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
					case ePenguinMoveDown:
						if( ((m_iCurrentRowID-1) < 0 ) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID-1][m_iCurrentColID] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID-1][m_iCurrentColID] == DIAMOND_BLOCK)){
							Temp_PenguinState	= ePenguinMoveLeft;
							Round++;
						}else {
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID-1)+(m_fRectSize/2));
							if(m_vExpectedPos.x == 0){ 
								m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID))+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
					case ePenguinMoveLeft:
						if( ((m_iCurrentColID-1) < 0 ) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID-1] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID-1] == DIAMOND_BLOCK)){
							Temp_PenguinState	= ePenguinMoveUp;
							Round++;
						}else {
							m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID-1))+(m_fRectSize/2));
							if(m_vExpectedPos.y == 0){
								m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
				}////	End Of Internal Switch
				break;
		}
	}
// Moved this to movePenguin	m_ePreviousPenguinState	= m_ePenguinState;
	m_ePenguinState			= Temp_PenguinState;

}


void Penguin::PathFinding1 () 
{
	int RandDirection_1, RandDirection_2;

	RandDirection_1	= rand() % 2;		// Generating Random number in range [0..1]
	if (Print_Verbose) 
		printf("Random Direction for Penguin in PathFindingAlgo_1: %d\n", RandDirection_1);
	// Switch at random between horizontal or vertical movement
	if (RandDirection_1 == 0)
	{ //	Move in Row	
		//srand ( time(NULL) );
		RandDirection_2	= rand() % 2;		// Generating Random number in range up to 2, ie [0..1]
		//	Deciding the Direction Depending on the selection ofRow or Col
		if (RandDirection_2 == 0)
		{ //	Moving +ve Row
			Move_PenguinPositiveRow();
		}
		else
		{ //	Moving -ve Row
			Move_PenguinNegativeRow();
		}
	} //	End Of ROW Condition
	else
	{  //	Move in Col
		//srand ( time(NULL) );
		RandDirection_2	= rand() % 2;		// Generating Random number in range up to 2 [0..1]
		//	Deciding the Direction Depending on the selection ofRow or Col
		if (RandDirection_2 == 0)
		{	//	Moving +ve
			Move_PenguinPositiveColumn();
		}
		else
		{	// Moving -ve
			Move_PenguinNegativeColumn();
		}
	} //	End Of Rows-Column Moves Condition
} // End of Penguin::PathFindingAlgo_1 () 

void Penguin::Move_PenguinPositiveRow ()
{
	m_ePenguinState = ePenguinMoveRight;
	if((m_iCurrentColID+1) >= ColCount )
	{
		calculateNewPath();
		return;
	}
	else
	{
		if( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID+1] == FREE)
		{
			m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID+1))+(m_fRectSize/2));
			if(m_vExpectedPos.y == 0)
			{
				m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
			}
		}
		else
		{
			calculateNewPath();
			return;
		}
	}
} // End of Penguin::Move_PenguinPositiveRow()

void	Penguin::Move_PenguinNegativeRow ()
{
	m_ePenguinState = ePenguinMoveLeft;
	if((m_iCurrentColID-1) <= 0 )
	{
		calculateNewPath();
		return;
	}
	else
	{
		if( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID-1] == FREE)
		{
			m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID-1))+(m_fRectSize/2));
			if(m_vExpectedPos.y == 0)
			{
				m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
			}
		}
		else
		{
			calculateNewPath();
			return;
		}
	}
} // End of Penguin::Move_PenguinNegativeRow()

void	Penguin::Move_PenguinPositiveColumn()
{
	m_ePenguinState = ePenguinMoveUp;
	if((m_iCurrentRowID+1) >= RowCount )
	{
		calculateNewPath();
		return;
	}
	else
	{
		if( m_pCustomLevel->LevelDesign[m_iCurrentRowID+1][m_iCurrentColID] == FREE)
		{
			m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID+1)+(m_fRectSize/2));
			if(m_vExpectedPos.x == 0)
			{ 
				m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID))+(m_fRectSize/2));
			}
		}
		else
		{
			calculateNewPath();
			return;
		}
	}
} // End of Penguin::Move_PenguinPositiveColumn()

void Penguin::Move_PenguinNegativeColumn ()
{
	int Cell_Difference;
	m_ePenguinState = ePenguinMoveDown;
	if((m_iCurrentRowID-1) <= 0 )
	{
		calculateNewPath();
		return;
	}
	else
	{
		Cell_Difference = (ColCount-m_iCurrentColID);
		if( m_pCustomLevel->LevelDesign[m_iCurrentRowID-1][m_iCurrentColID] == FREE)
		{
			m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID-1)+(m_fRectSize/2));
			if(m_vExpectedPos.x == 0)
			{ 
				m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID))+(m_fRectSize/2));
			}
		}
		else
		{
			calculateNewPath();
			return;
		}
	}
} // End of Penguin::Move_PenguinNegativeColumn


void Penguin::calculateNewPosition()
{
	switch (m_ePenguinState)
	{
		case ePenguinMoveUp:
		{
			Move_PenguinPositiveColumn();
			break;
		}
		case ePenguinMoveDown:
		{
			Move_PenguinNegativeColumn();
			break;
		}
		case ePenguinMoveRight:
		{
			Move_PenguinPositiveRow();
			break;
		}
		case ePenguinMoveLeft:
		{
			Move_PenguinNegativeRow();
			break;
		}
	}
}

// New Version - DNDavis
// Changed if statements to switch and seperated out high level strategic state algorithms
/* Note:
   if you move
				calculateNewPath ();
   out of current nested conditions in switch statements to end of ecah method
   the Penguin will move in "STRANGE" ways!
*/

// movePenguin_Normal called if m_ePenguinStragicState)== ePenguinNormal:
// Little different to other two in current state of code
void Penguin::movePenguin_Normal()
{
	switch (m_ePenguinState)
	{
		case ePenguinMoveUp:
		{
			mPenguinPos.y	+= m_fPenguinMoveSpeed;
			if(mPenguinPos.y > (MAX_HEIGHT-(m_fRectSize/2))){
				mPenguinPos.y	-= m_fPenguinMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
		case ePenguinMoveRight:
		{
			mPenguinPos.x	+= m_fPenguinMoveSpeed;
			if(mPenguinPos.x > (MAX_WIDTH-(m_fRectSize/2))){
				mPenguinPos.x	-= m_fPenguinMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
		case ePenguinMoveDown:
		{
			mPenguinPos.y	-= m_fPenguinMoveSpeed;
			if(mPenguinPos.y < (MIN_HEIGHT+(m_fRectSize/2))){
				mPenguinPos.y	+= m_fPenguinMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
		case ePenguinMoveLeft:
		{
			mPenguinPos.x	-= m_fPenguinMoveSpeed;
			if(mPenguinPos.x < (MIN_WIDTH+(m_fRectSize/2))){
				mPenguinPos.x	+= m_fPenguinMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
	} // end of switch
}

// movePenguin_Attack called if m_ePenguinStragicState)== ePenguinAttack:
// Little different to other two in current state of code
void Penguin::movePenguin_Attack()
{
	switch (m_ePenguinState)
	{
	case ePenguinMoveUp:
		{
			mPenguinPos.y	+= m_fPenguinMoveSpeed;
			if(mPenguinPos.y > (MAX_HEIGHT-(m_fRectSize/2))){
				mPenguinPos.y	-= m_fPenguinMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
	case ePenguinMoveRight:
		{
			mPenguinPos.x	+= m_fPenguinMoveSpeed;
			if(mPenguinPos.x > (MAX_WIDTH-(m_fRectSize/2))){
				mPenguinPos.x	-= m_fPenguinMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
	case ePenguinMoveDown:
		{
			mPenguinPos.y	-= m_fPenguinMoveSpeed;
			if(mPenguinPos.y < (MIN_HEIGHT+(m_fRectSize/2))){
				mPenguinPos.y	+= m_fPenguinMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
	case ePenguinMoveLeft:
		{
			mPenguinPos.x	-= m_fPenguinMoveSpeed;
			if(mPenguinPos.x < (MIN_WIDTH+(m_fRectSize/2))){
				mPenguinPos.x	+= m_fPenguinMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
	}
}

// movePenguin_Run called if m_ePenguinStragicState)== ePenguinRun:
// Little different to other two in current state of code
void Penguin::movePenguin_Run()
{
	// First Stage - Switch Direction
	// This is Not Clever as may be blocked in opposite direction
	// AND DOES NOT WORK AS PENGUIN OSCILLATES!
// /* What it needs to do is find direction away from ALL Bees
	if ( (!(m_ePreviousPenguinStragicState == m_ePenguinStragicState))&&(m_ePreviousPenguinState == m_ePenguinState) )	
	{
		switch (m_ePenguinState)
		{
			case ePenguinMoveUp:
			{
				if (CheckDownforBee() > 0) m_ePenguinState = ePenguinMoveDown;
				break;
			}
			case ePenguinMoveRight:
			{
				if (CheckRightforBee() > 0) m_ePenguinState = ePenguinMoveLeft;
				break;
			}
			case ePenguinMoveDown:
			{
				if (CheckDownforBee() > 0) m_ePenguinState = ePenguinMoveUp;
				break;
			}
			case ePenguinMoveLeft:
			{
				if (CheckLeftforBee() > 0) m_ePenguinState = ePenguinMoveRight;
				break;
			}
		}
	} // End of Stage 1
// */
	// Stage 2 Now Move in NEW Direction!
	switch (m_ePenguinState)
	{
		case ePenguinMoveUp:
		{
			mPenguinPos.y	+= m_fPenguinMoveSpeed;
			if(mPenguinPos.y > (MAX_HEIGHT-(m_fRectSize/2))){
				mPenguinPos.y	-= m_fPenguinMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
		case ePenguinMoveRight:
		{
			mPenguinPos.x	+= m_fPenguinMoveSpeed;
			if(mPenguinPos.x > (MAX_WIDTH-(m_fRectSize/2))){
				mPenguinPos.x	-= m_fPenguinMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
		case ePenguinMoveDown:
		{
			mPenguinPos.y	-= m_fPenguinMoveSpeed;
			if(mPenguinPos.y < (MIN_HEIGHT+(m_fRectSize/2))){
				mPenguinPos.y	+= m_fPenguinMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
		case ePenguinMoveLeft:
		{
			mPenguinPos.x	-= m_fPenguinMoveSpeed;
			if(mPenguinPos.x < (MIN_WIDTH+(m_fRectSize/2))){
				mPenguinPos.x	+= m_fPenguinMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
	}
}

void Penguin::movePenguin()
{
	CheckForBees();
	switch (m_ePenguinStragicState)
	{
		case ePenguinNormal: // print statements only if Penguin changed Strategic Stste
		{
			if ((Print_Verbose)&&(!(m_ePreviousPenguinStragicState==m_ePenguinStragicState)) )
			{
				printf(" *** movePenguin to movePenguinNormal: %d\n", m_ePenguinStragicState);
			}
			movePenguin_Normal();
			break;
		} // end of 	case ePenguinNormal:
		case ePenguinAttack:
		{
			if ((Print_Verbose)&&(!(m_ePreviousPenguinStragicState==m_ePenguinStragicState)))
			{
				printf(" *** movePenguin to movePenguinAttack: %d\n", m_ePenguinStragicState);
			}
			movePenguin_Attack();
			break;
		} // end of 	case ePenguinAttack:
		case ePenguinRun:
		{
			if ((Print_Verbose)&&(!(m_ePreviousPenguinStragicState==m_ePenguinStragicState)))
			{
				printf(" *** movePenguin to movePenguinRun: %d\n", m_ePenguinStragicState);
			}
			movePenguin_Run();
			break;
		} // end of 	case ePenguinRun:
	}

	// Set up previous State
	m_ePreviousPenguinStragicState = m_ePenguinStragicState;
	m_ePreviousPenguinState = m_ePenguinState;
//	calculateNewPosition(); This is causing it to move to Half Squares!
}
////////////////////////////////////////////////////////////////////////////////////////
// Perception Functions and Methods
// CheckXDIRECTIONXforBee return 0 or number of Positions away
int Penguin::CheckDownforBee ()
{
	int response = 0;
	for (int i = m_iCurrentRowID-1;( (i >= 0)&&((m_iCurrentRowID-i)< SENSE_LIMIT) ); i--)
	{
		if ( m_pCustomLevel->LevelDesign[i][m_iCurrentColID] == KILLER_BEE )
			return( i );
	}
	return( response );
}
int Penguin::CheckUpforBee ()
{
	int response = 0;
	for (int i = m_iCurrentRowID+1;( (i < RowCount)&&((i-m_iCurrentRowID)< SENSE_LIMIT) ); i++)
	{
		if ( m_pCustomLevel->LevelDesign[i][m_iCurrentColID] == KILLER_BEE )
			return( i );
	}
	return( response );
}
int Penguin::CheckRightforBee ()
{
	int response = 0;
	for (int i = m_iCurrentColID+1;( (i < ColCount)&&((i-m_iCurrentColID)< SENSE_LIMIT) ); i++)
	{
		if ( m_pCustomLevel->LevelDesign[m_iCurrentRowID][i]	== KILLER_BEE )
			return( i );
	}
	return( response );
}
int Penguin::CheckLeftforBee ()
{
	int response = 0;
	for (int i = m_iCurrentColID-1;( (i >= 0)&&((m_iCurrentColID-i)< SENSE_LIMIT) ); i--)
	{
		if ( m_pCustomLevel->LevelDesign[m_iCurrentRowID][i] == KILLER_BEE )
			return( i );
	}
	return( response );
}

// This is the code that checks for Bees
// Two Stages
// STAGE 2 Calls FOUR Direction Functions
void Penguin::CheckForBees ()
{
	m_fPenguinMoveSpeed	= 1;
	m_ePenguinStragicState	=	ePenguinNormal;
	int TempRow , TempCol;
	TempRow = TempCol	= -1;

	//	Step 1:	Get Current Row & Col Index
	for (int a = 0; a < RowCount; a++){
		int PosY	= ((m_fRectSize+1)*(a)+m_fRectSize/2);
		if( abs(mPenguinPos.y-PosY) < m_fRectSize/2 ){
			TempRow	= a;
			break;
		}
	}
	//	Calculating the Current Col Index for the Bee
	for (int a = 0; a < ColCount; a++){
		int	PosX	 = ((m_fRectSize+1)*(a)+m_fRectSize/2);
		if( abs(mPenguinPos.x-PosX) < m_fRectSize/2 ){
			TempCol	= a;
			break;
		}
	}
	//	Step 2: Finding for Bee in 4 directions Up, Down, Right Left
	CheckInUpDirection();
	CheckInRightDirection();
	CheckInDownDirection();
	CheckInLeftDirection();
}

void Penguin::CheckInRightDirection () {
	bool	m_bBeeFound		= false;
	int		m_iBeeIndex		= -1;
	int		m_iIceCubeIndex	= -1;
//	int		mIceCubeCount	= 0;

	// Checking TO RIGHT of the Penguin
	// Increase Column Count to Max OR UNtil BEE Found
	for (int i = m_iCurrentColID+1;( (i < ColCount)&&(!m_bBeeFound) ); i++)
	{
		if ( m_pCustomLevel->LevelDesign[m_iCurrentRowID][i]	== KILLER_BEE )
		{
			m_bBeeFound	= true;
			m_iBeeIndex	= i;

			int mIceCubeCount	= 0;
			for (int j = m_iCurrentColID+1; j < m_iBeeIndex; j++) 
			{
				if ( (m_pCustomLevel->LevelDesign[m_iCurrentRowID][j] == DIAMOND_BLOCK) ||
					(m_pCustomLevel->LevelDesign[m_iCurrentRowID][j] == ICE_BLOCK) )
				{
					mIceCubeCount++;
					m_iIceCubeIndex	= j;
				}
			}
			if ( mIceCubeCount < 1 ) // Run Away IF no protection or cubes to attack with
			{
				m_ePenguinStragicState	=	ePenguinRun;
			}
			if ( mIceCubeCount == 1 ) 
			{
				m_fPenguinMoveSpeed		=	2;
				m_ePenguinStragicState	=	ePenguinAttack;
//				if (Print_Verbose) printf("Ice Cube to Right of Penguin to Bee\n");
					
				if ( (abs(mPenguinPos.x - m_vExpectedPos.x) < m_fPenguinMoveSpeed) && 
					 (abs(mPenguinPos.y - m_vExpectedPos.y) < m_fPenguinMoveSpeed) )
				{
					mPenguinPos.x	= m_vExpectedPos.x;
					mPenguinPos.y	= m_vExpectedPos.y;
						
					m_ePenguinState	= ePenguinMoveRight;
					m_vExpectedPos.x	= ((m_fRectSize+1)*(m_iCurrentColID+1)+(m_fRectSize/2));	
					m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
//					printf("2: Ice Cube to Right of Penguin to Bee: %d\n", (m_iIceCubeIndex-m_iCurrentColID) );
					if ( (m_iIceCubeIndex-m_iCurrentColID) == 1 )
					{
//						printf(" *** ShiftCubeRight: %d %d %d\n", m_iCurrentRowID, m_iCurrentColID+1, m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID+1]);
						ShiftCubeRight(m_iCurrentRowID, m_iCurrentColID+1, m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID+1]);
					}
				}
			}
		}
	}	//	Check for Bee TO RIGHT is complete
}

void Penguin::CheckInLeftDirection () {
	bool	m_bBeeFound		= false;
	int		m_iBeeIndex		= -1;
	int		m_iIceCubeIndex	= -1;

	//	Checking TO LEFT of the Penguin
	// COLUMN COUNT >= 0 or Bee Found
	for (int i = m_iCurrentColID-1;( (i >= 0)&&(!m_bBeeFound) ); i--)
	{
		if ( m_pCustomLevel->LevelDesign[m_iCurrentRowID][i]	== KILLER_BEE )
		{
			m_bBeeFound	= true;
			m_iBeeIndex	= i;

			int		mIceCubeCount	= 0;
			for (int j = m_iCurrentColID-1; j > m_iBeeIndex; j--) 
			{
				if ( (m_pCustomLevel->LevelDesign[m_iCurrentRowID][j] == DIAMOND_BLOCK) || 
					 (m_pCustomLevel->LevelDesign[m_iCurrentRowID][j] == ICE_BLOCK) ){
					mIceCubeCount++;
					m_iIceCubeIndex	= j;
				}
			}
			if ( mIceCubeCount < 1 ) // Run Away IF no protection or cubes to attack with
			{
				m_ePenguinStragicState	=	ePenguinRun;
			}
			if ( mIceCubeCount == 1 ) 
			{
				m_fPenguinMoveSpeed		=	2;
				m_ePenguinStragicState	=	ePenguinAttack;
	
//				printf("Ice Cube to Lefht of Penguin to Bee\n");
				if ( (abs(mPenguinPos.x - m_vExpectedPos.x) < m_fPenguinMoveSpeed) && (abs(mPenguinPos.y - m_vExpectedPos.y) < m_fPenguinMoveSpeed) )
				{
					mPenguinPos.x	= m_vExpectedPos.x;
					mPenguinPos.y	= m_vExpectedPos.y;
					
					m_ePenguinState	= ePenguinMoveLeft;
					m_vExpectedPos.x	= ((m_fRectSize+1)*(m_iCurrentColID-1)+(m_fRectSize/2));	
					m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
					if ( (m_iCurrentColID-m_iIceCubeIndex) == 1 )
					{
//						printf(" *** ShiftCubeLeft: %d %d %d\n", m_iCurrentRowID, m_iCurrentColID-1, m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID-1]);
						ShiftCubeLeft(m_iCurrentRowID, m_iCurrentColID-1, m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID-1]);
					}
				}
			}
		}
	}	//	Check for Bee TO LEFT is complete
}


void Penguin::CheckInDownDirection () {
	bool	m_bBeeFound		= false;
	int		m_iBeeIndex		= -1;
	int		m_iIceCubeIndex	= -1;

	//	first Checking BELOW of the Penguin
	for (int i = m_iCurrentRowID-1;( (i >= 0)&&(!m_bBeeFound) ); i--)
	{
		if ( m_pCustomLevel->LevelDesign[i][m_iCurrentColID]	== KILLER_BEE )
		{
			m_bBeeFound	= true;
			m_iBeeIndex	= i;

			int		mIceCubeCount	= 0;
			for (int j = m_iCurrentRowID-1; j > m_iBeeIndex; j--) 
			{
				if ( (m_pCustomLevel->LevelDesign[j][m_iCurrentColID] == DIAMOND_BLOCK) ||
					 (m_pCustomLevel->LevelDesign[j][m_iCurrentColID] == ICE_BLOCK) )
				{
					mIceCubeCount++;
					m_iIceCubeIndex	= j;
				}
			}
			if ( mIceCubeCount < 1 ) // Run Away IF no protection or cubes to attack with
			{
				m_ePenguinStragicState	=	ePenguinRun;
			}
			if ( mIceCubeCount == 1 ) 
			{
				m_fPenguinMoveSpeed		=	2;
				m_ePenguinStragicState	=	ePenguinAttack;
//				printf("Ice Cube to Below of Penguin to Bee\n");
	
				if ( (abs(mPenguinPos.x - m_vExpectedPos.x) < m_fPenguinMoveSpeed) && 
					 (abs(mPenguinPos.y - m_vExpectedPos.y) < m_fPenguinMoveSpeed) )
				{
					mPenguinPos.x	= m_vExpectedPos.x;
					mPenguinPos.y	= m_vExpectedPos.y;
			
					m_ePenguinState	= ePenguinMoveDown;
					m_vExpectedPos.x	= ((m_fRectSize+1)*(m_iCurrentColID)+(m_fRectSize/2));	
					m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID-1)+(m_fRectSize/2));
					if ( (m_iCurrentRowID-m_iIceCubeIndex) == 1 )
					{
//						printf(" *** ShiftCubeDown: %d %d %d\n", m_iCurrentRowID-1, m_iCurrentColID, m_pCustomLevel->LevelDesign[m_iCurrentRowID-1][m_iCurrentColID]);
						ShiftCubeDown(m_iCurrentRowID-1, m_iCurrentColID, m_pCustomLevel->LevelDesign[m_iCurrentRowID-1][m_iCurrentColID]);
					}
				}
			}
		}
	}	//	Check for Bee BELOW is complete
}

void Penguin::CheckInUpDirection () {
	bool	m_bBeeFound		= false;
	int		m_iBeeIndex		= -1;
	int		m_iIceCubeIndex	= -1;

	//	first Checking ABOVE of the Penguin
	for (int i = m_iCurrentRowID+1;( (i < RowCount)&&(!m_bBeeFound) ); i++)
	{
		if ( m_pCustomLevel->LevelDesign[i][m_iCurrentColID] == KILLER_BEE )
		{
			m_bBeeFound	= true;
			m_iBeeIndex	= i;

			int		mIceCubeCount	= 0;
			for (int j = m_iCurrentRowID+1; j < m_iBeeIndex; j++) 
			{
				if ( (m_pCustomLevel->LevelDesign[j][m_iCurrentColID] == DIAMOND_BLOCK) || 
					 (m_pCustomLevel->LevelDesign[j][m_iCurrentColID] == ICE_BLOCK) ){
					mIceCubeCount++;
					m_iIceCubeIndex	= j;
				}
			}
			if ( mIceCubeCount < 1 ) // Run Away IF no protection or cubes to attack with
			{
				m_ePenguinStragicState	=	ePenguinRun;
			}
			if ( mIceCubeCount == 1 ) 
			{
				m_fPenguinMoveSpeed		=	2;
				m_ePenguinStragicState	=	ePenguinAttack;
//				printf("Ice Cube to Above of Penguin to Bee\n");
	
				if ( (abs(mPenguinPos.x - m_vExpectedPos.x) < m_fPenguinMoveSpeed) && 
					 (abs(mPenguinPos.y - m_vExpectedPos.y) < m_fPenguinMoveSpeed) )
				{
					mPenguinPos.x	= m_vExpectedPos.x;
					mPenguinPos.y	= m_vExpectedPos.y;
						
					m_ePenguinState	= ePenguinMoveUp;
					m_vExpectedPos.x	= ((m_fRectSize+1)*(m_iCurrentColID)+(m_fRectSize/2));	
					m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID+1)+(m_fRectSize/2));
					if ( (m_iIceCubeIndex - m_iCurrentRowID) == 1 )
					{
//						printf(" *** ShiftCubeUp: %d %d %d\n", m_iCurrentRowID+1, m_iCurrentColID, m_pCustomLevel->LevelDesign[m_iCurrentRowID+1][m_iCurrentColID]);
						ShiftCubeUp(m_iCurrentRowID+1, m_iCurrentColID, m_pCustomLevel->LevelDesign[m_iCurrentRowID+1][m_iCurrentColID]);
					}
				}
			}
		}

	}	//	Check for Bee Upwards is complete
}

/////////////////////////////////////////////////////////////////////////
void Penguin::ShiftIceCubeUp (IceCube *localCube, int RowID, int ColID, int IceBlockType) 
{
	Vec2f	StartPos, EndPos;
	StartPos.x	= ((m_fRectSize+1)*(ColID)+(m_fRectSize/2));
	StartPos.y	= ((m_fRectSize+1)*(RowID)+(m_fRectSize/2));
	int CurrentRowID = RowID;
	if (Print_Verbose) printf("Local Ice Cube %d %d %d\n", RowID, ColID, IceBlockType);

	localCube->setCustLevelObj(m_pCustomLevel);
	localCube->m_iCurrentIceID	= m_pCustomLevel->LevelDesign[RowID][ColID];
	m_pCustomLevel->LevelDesign[RowID][ColID]	= MOVING_BLOCK;

	for (int i = CurrentRowID; i < RowCount; i++)
	{
		if ( (i != CurrentRowID) && 
			 ((m_pCustomLevel->LevelDesign[i][ColID] == ICE_BLOCK) || 
			  (m_pCustomLevel->LevelDesign[i][ColID] == DIAMOND_BLOCK)))
		{
			if (abs(i-RowID)<= 1)
			{
				m_pCustomLevel->LevelDesign[RowID][ColID]	= localCube->m_iCurrentIceID;
				localCube	= NULL;
				return;
			}
			EndPos.x	= ((m_fRectSize+1)*(ColID)+(m_fRectSize/2));
			EndPos.y	= ((m_fRectSize+1)*(i-1)+(m_fRectSize/2));
			localCube->m_vEndPosition	= EndPos;
			localCube->setEndCellID(i-1, ColID);

			break;
		}
		if(i == ColCount){
			EndPos.x	= ((m_fRectSize+1)*(ColID)+(m_fRectSize/2));
			EndPos.y	= ((m_fRectSize+1)*(i)+(m_fRectSize/2));
			localCube->m_vEndPosition	= EndPos;
			localCube->setEndCellID(i, ColID);
		}
	}
	localCube->setDirection(localCube->eMoveUp);
	localCube->m_iCurrentIceID	= IceBlockType;
}

void Penguin::ShiftCubeUp (int RowID, int ColID, int IceBlockType) 
{
	Vec2f	StartPos, EndPos;
	StartPos.x	= ((m_fRectSize+1)*(ColID)+(m_fRectSize/2));
	StartPos.y	= ((m_fRectSize+1)*(RowID)+(m_fRectSize/2));
		
	int CurrentRowID = RowID;

	if ((m_pCustomLevel->LevelDesign[RowID][ColID] != ICE_BLOCK) && 
		(m_pCustomLevel->LevelDesign[RowID][ColID] != DIAMOND_BLOCK) ){
		return;
	}

	if(!m_pIceCube_1)
	{
//		printf("Using Ice Cube1\n");
		m_pIceCube_1	= new IceCube(StartPos,EndPos,RowID,ColID);
		ShiftIceCubeUp(m_pIceCube_1, RowID, ColID, IceBlockType);
	}else if(!m_pIceCube_2)
	{
//		printf("Using Ice Cube2\n");
		m_pIceCube_2	= new IceCube(StartPos,EndPos,RowID,ColID);
		ShiftIceCubeUp(m_pIceCube_2, RowID, ColID, IceBlockType);
	}else if(!m_pIceCube_3)
	{
//		printf("Using Ice Cube3\n");
		m_pIceCube_3	= new IceCube(StartPos,EndPos,RowID,ColID);
		ShiftIceCubeUp(m_pIceCube_3, RowID, ColID, IceBlockType);
	}else if(!m_pIceCube_4)
	{
//		printf("Using Ice Cube4\n");
		m_pIceCube_4	= new IceCube(StartPos,EndPos,RowID,ColID);
		ShiftIceCubeUp(m_pIceCube_4, RowID, ColID, IceBlockType);
	}
}

///////////////////////////////////////////////////////////////////////
void Penguin::ShiftIceCubeDown (IceCube *localCube, int RowID, int ColID, int IceBlockType) 
{
	Vec2f	StartPos, EndPos;
	StartPos.x	= ((m_fRectSize+1)*(ColID)+(m_fRectSize/2));
	StartPos.y	= ((m_fRectSize+1)*(RowID)+(m_fRectSize/2));		
	int CurrentRowID = RowID;
	if (Print_Verbose) printf("Local Ice Cube %d %d %d\n", RowID, ColID, IceBlockType);

	localCube->setCustLevelObj(m_pCustomLevel);
	localCube->m_iCurrentIceID	= m_pCustomLevel->LevelDesign[RowID][ColID];
	m_pCustomLevel->LevelDesign[RowID][ColID]	= MOVING_BLOCK;

	for (int i = CurrentRowID; i >= 0; i--)
	{
		if ( (i != CurrentRowID) && 
			 ((m_pCustomLevel->LevelDesign[i][ColID] == ICE_BLOCK)||(m_pCustomLevel->LevelDesign[i][ColID] == DIAMOND_BLOCK))) {
			if (abs(i-RowID)<= 1){
					m_pCustomLevel->LevelDesign[RowID][ColID]	= localCube->m_iCurrentIceID;
					localCube->~IceCube();
					localCube	= NULL;
					return;
				}
				EndPos.x	= ((m_fRectSize+1)*(ColID)+(m_fRectSize/2));
				EndPos.y	= ((m_fRectSize+1)*(i+1)+(m_fRectSize/2));
				localCube->m_vEndPosition	= EndPos;
				localCube->setEndCellID(i+1, ColID);
				break;
			}
			if(i == 0){
				EndPos.x	= ((m_fRectSize+1)*(ColID)+(m_fRectSize/2));
				EndPos.y	= ((m_fRectSize+1)*(i)+(m_fRectSize/2));
				localCube->m_vEndPosition	= EndPos;
				localCube->setEndCellID(i, ColID);
			}
		}
		localCube->setDirection(localCube->eMoveDown);
		localCube->m_iCurrentIceID	= IceBlockType;
}

void Penguin::ShiftCubeDown ( int RowID, int ColID, int IceBlockType ) {

	Vec2f	StartPos, EndPos;
		StartPos.x	= ((m_fRectSize+1)*(ColID)+(m_fRectSize/2));
		StartPos.y	= ((m_fRectSize+1)*(RowID)+(m_fRectSize/2));		
	int CurrentRowID = RowID;
	if (Print_Verbose) printf("Local Ice Cube %d %d %d\n", RowID, ColID, IceBlockType);

	if( (m_pCustomLevel->LevelDesign[RowID][ColID]	!= ICE_BLOCK) && 
		(m_pCustomLevel->LevelDesign[RowID][ColID]	!= DIAMOND_BLOCK))
	{
		return;
	}

	if(!m_pIceCube_1)
	{
		m_pIceCube_1	= new IceCube(StartPos,EndPos,RowID,ColID);
		ShiftIceCubeDown(m_pIceCube_1, RowID, ColID, IceBlockType);
	}else if(!m_pIceCube_2)
	{
		m_pIceCube_2	= new IceCube(StartPos,EndPos,RowID,ColID);
		ShiftIceCubeDown(m_pIceCube_2, RowID, ColID, IceBlockType);
	}else if(!m_pIceCube_3)
	{
		m_pIceCube_3	= new IceCube(StartPos,EndPos,RowID,ColID);
		ShiftIceCubeDown(m_pIceCube_3, RowID, ColID, IceBlockType);
	}else if(!m_pIceCube_4)
	{
		m_pIceCube_4	= new IceCube(StartPos,EndPos,RowID,ColID);
		ShiftIceCubeDown(m_pIceCube_4, RowID, ColID, IceBlockType);
	}
}

void Penguin::ShiftIceCubeRight (IceCube *localCube, int RowID, int ColID, int IceBlockType) 
{
	Vec2f	StartPos, EndPos;
	StartPos.x	= ((m_fRectSize+1)*(ColID)+(m_fRectSize/2));
	StartPos.y	= ((m_fRectSize+1)*(RowID)+(m_fRectSize/2));
	localCube->setCustLevelObj(m_pCustomLevel);

	if (Print_Verbose) printf("Local Ice Cube %d %d %d\n", RowID, ColID, IceBlockType);

//	printf("Direction %d Right %d\n",localCube->m_eMoveDirection, localCube->eMoveRight);

	localCube->m_iCurrentIceID	= m_pCustomLevel->LevelDesign[RowID][ColID];
	m_pCustomLevel->LevelDesign[RowID][ColID]	= MOVING_BLOCK;

	for (int i = ColID; i < ColCount; i++){
		if ( (i != ColID) && 
			 ((m_pCustomLevel->LevelDesign[RowID][i] == ICE_BLOCK) || (m_pCustomLevel->LevelDesign[RowID][i] == DIAMOND_BLOCK))) {
			EndPos.x	= ((m_fRectSize+1)*(i-1)+(m_fRectSize/2));
			EndPos.y	= ((m_fRectSize+1)*(RowID)+(m_fRectSize/2));
			localCube->m_vEndPosition	= EndPos;
			localCube->setEndCellID(RowID,i-1);

			break;
		}
		if(i == ColCount){
			EndPos.x	= ((m_fRectSize+1)*(i)+(m_fRectSize/2));
			EndPos.y	= ((m_fRectSize+1)*(RowID)+(m_fRectSize/2));
			localCube->m_vEndPosition	= EndPos;
			localCube->setEndCellID( RowID, i);
		}
	}
	localCube->setDirection(localCube->eMoveRight);
	localCube->m_iCurrentIceID	= IceBlockType;
}

void Penguin::ShiftCubeRight (int RowID, int ColID, int IceBlockType) {
	Vec2f	StartPos, EndPos;
	
	StartPos.x	= ((m_fRectSize+1)*(ColID)+(m_fRectSize/2));
	StartPos.y	= ((m_fRectSize+1)*(RowID)+(m_fRectSize/2));
	if (Print_Verbose) printf("Local Right Ice Cube %d %d %d\n", RowID, ColID, IceBlockType);

	if( (m_pCustomLevel->LevelDesign[RowID][ColID]	!= ICE_BLOCK) && 
		(m_pCustomLevel->LevelDesign[RowID][ColID]	!= DIAMOND_BLOCK) )
	{
//		printf("Exiting SCRight as not either Cube\n");
		return;
	}
	if(!m_pIceCube_1)
	{
		m_pIceCube_1	= new IceCube(StartPos,EndPos,RowID,ColID);
//		printf("Shifting IceCube#1 Right\n");
		ShiftIceCubeRight(m_pIceCube_1, RowID, ColID, IceBlockType);
	}else if(!m_pIceCube_2)
	{
		m_pIceCube_2	= new IceCube(StartPos,EndPos,RowID,ColID);
//		printf("Shifting IceCube#2 Right\n");
		ShiftIceCubeRight(m_pIceCube_2, RowID, ColID, IceBlockType);
	}else if(!m_pIceCube_3)
	{
		m_pIceCube_3	= new IceCube(StartPos,EndPos,RowID,ColID);
//		printf("Shifting IceCube#3 Right\n");
		ShiftIceCubeRight(m_pIceCube_3, RowID, ColID, IceBlockType);
	}else if(!m_pIceCube_4)
	{
		m_pIceCube_4	= new IceCube(StartPos,EndPos,RowID,ColID);
//		printf("Shifting IceCube#4 Right\n");
		ShiftIceCubeRight(m_pIceCube_4, RowID, ColID, IceBlockType);
	}
}

void Penguin::ShiftIceCubeLeft (IceCube *localCube, int RowID, int ColID, int IceBlockType) 
{
	Vec2f	StartPos, EndPos;
	StartPos.x	= ((m_fRectSize+1)*(ColID)+(m_fRectSize/2));
	StartPos.y	= ((m_fRectSize+1)*(RowID)+(m_fRectSize/2));
	if (Print_Verbose) printf("Local Left Ice Cube %d %d %d\n", RowID, ColID, IceBlockType);
		localCube->setCustLevelObj(m_pCustomLevel);

		localCube->m_iCurrentIceID	= m_pCustomLevel->LevelDesign[RowID][ColID];
		m_pCustomLevel->LevelDesign[RowID][ColID]	= MOVING_BLOCK;

		for (int i = ColID; i >= 0; i--){
			if ( (i != ColID) && 
				 ( (m_pCustomLevel->LevelDesign[RowID][i] == ICE_BLOCK)||
				   (m_pCustomLevel->LevelDesign[RowID][i] == DIAMOND_BLOCK)))
			{
				EndPos.x	= ((m_fRectSize+1)*(i+1)+(m_fRectSize/2));
				EndPos.y	= ((m_fRectSize+1)*(RowID)+(m_fRectSize/2));
				localCube->m_vEndPosition	= EndPos;
				localCube->setEndCellID(RowID,i+1);
				break;
			}if(i == 0){
				EndPos.x	= ((m_fRectSize+1)*(i)+(m_fRectSize/2));
				EndPos.y	= ((m_fRectSize+1)*(RowID)+(m_fRectSize/2));
				localCube->m_vEndPosition	= EndPos;
				localCube->setEndCellID( RowID, i);
			}
		}
		localCube->setDirection(localCube->eMoveLeft);
		localCube->m_iCurrentIceID	= IceBlockType;
}

void Penguin::ShiftCubeLeft (int RowID, int ColID, int IceBlockType) {
	Vec2f	StartPos, EndPos;
	StartPos.x	= ((m_fRectSize+1)*(ColID)+(m_fRectSize/2));
	StartPos.y	= ((m_fRectSize+1)*(RowID)+(m_fRectSize/2));
		
	if( (m_pCustomLevel->LevelDesign[RowID][ColID]	!= ICE_BLOCK) && 
		(m_pCustomLevel->LevelDesign[RowID][ColID]	!= DIAMOND_BLOCK))
	{
		return;
	}

	if(!m_pIceCube_1){
		m_pIceCube_1	= new IceCube(StartPos,EndPos,RowID,ColID);
		ShiftIceCubeLeft(m_pIceCube_1, RowID, ColID, IceBlockType);
	}else if(!m_pIceCube_2){
		m_pIceCube_2	= new IceCube(StartPos,EndPos,RowID,ColID);
		ShiftIceCubeLeft(m_pIceCube_2, RowID, ColID, IceBlockType);
	}else if(!m_pIceCube_3){
		m_pIceCube_3	= new IceCube(StartPos,EndPos,RowID,ColID);
		ShiftIceCubeLeft(m_pIceCube_3, RowID, ColID, IceBlockType);
	}else if(!m_pIceCube_4){
		m_pIceCube_4	= new IceCube(StartPos,EndPos,RowID,ColID);
		ShiftIceCubeLeft(m_pIceCube_4, RowID, ColID, IceBlockType);
	}
	
}

void Penguin::setIceCubeTextureID(GLint textureID){
	IceCube_texture_id	= textureID;
}


void Penguin::renderPenguin(void){

	if (m_ePenguinStragicState	== ePenguinDead){
		return;
	}

	CalculateCurrentCell();			///	Calculating Current Grid Position

	MyPenguinController();

	//CheckForBees();				//	Checking for the Bee postions & accordingly deciding the strategy
	//movePenguin();					//	Moving the Penguin Depending on the current strategy.
	float	size	= (m_fRectSize/2);
	glPushMatrix();
	glTranslatef(mPenguinPos.x,mPenguinPos.y,0);
	glBegin(GL_QUADS);						// Draw A Quad
	glTexCoord2f (0.0, 0.0);
	glVertex3f (-size, -size, -2.0);
	glTexCoord2f (1.0, 0.0);
	glVertex3f (size, -size, -2.0);
	glTexCoord2f (1.0, 1.0);
	glVertex3f (size, size, -2.0);
	glTexCoord2f (0.0, 1.0);
	glVertex3f (-size, size, -2.0);
	glEnd();							// Done Drawing The Quad

	glPopMatrix();
	glPushMatrix();
	//	Rending Cube_1
	if( m_pIceCube_1 ){
		glPushMatrix();
		m_pIceCube_1->DrawIceCube();
		glPopMatrix();
		if (m_pIceCube_1->m_eMoveDirection	== m_pIceCube_1->eDone){
			if( ((m_pIceCube_1->m_iEndRowID >= 0) && (m_pIceCube_1->m_iEndRowID <= RowCount)) || 
				((m_pIceCube_1->m_iEndColID >= 0) && (m_pIceCube_1->m_iEndColID <= ColCount)) )
			{
				m_pCustomLevel->LevelDesign[m_pIceCube_1->m_iEndRowID][m_pIceCube_1->m_iEndColID]	= m_pIceCube_1->m_iCurrentIceID;
			}
			m_pIceCube_1->~IceCube();
			//free(m_pIceCube_1);
			m_pIceCube_1	= NULL;
		}
	}

	//Rendering Cube 2
	if( m_pIceCube_2 ){
		glPushMatrix();
		m_pIceCube_2->DrawIceCube();
		glPopMatrix();
		if (m_pIceCube_2->m_eMoveDirection	== m_pIceCube_2->eDone){
			if( ((m_pIceCube_2->m_iEndRowID >= 0) && (m_pIceCube_2->m_iEndRowID <= RowCount)) || 
				((m_pIceCube_2->m_iEndColID >= 0) && (m_pIceCube_2->m_iEndColID <= ColCount)) )
			{
				m_pCustomLevel->LevelDesign[m_pIceCube_2->m_iEndRowID][m_pIceCube_2->m_iEndColID]	= m_pIceCube_2->m_iCurrentIceID;
			}
			m_pIceCube_2->~IceCube();
			//free(m_pIceCube_2);
			m_pIceCube_2	= NULL;
		}
	}

	//Rendering Cube 3
	if( m_pIceCube_3 ){
		glPushMatrix();
		m_pIceCube_3->DrawIceCube();
		glPopMatrix();
		if (m_pIceCube_3->m_eMoveDirection	== m_pIceCube_3->eDone){
			if( ((m_pIceCube_3->m_iEndRowID >= 0) && (m_pIceCube_3->m_iEndRowID <= RowCount)) || 
				((m_pIceCube_3->m_iEndColID >= 0) && (m_pIceCube_3->m_iEndColID <= ColCount)) )
			{
				m_pCustomLevel->LevelDesign[m_pIceCube_3->m_iEndRowID][m_pIceCube_3->m_iEndColID]	= m_pIceCube_3->m_iCurrentIceID;
			}
			m_pIceCube_3->~IceCube();
			//free(m_pIceCube_3);
			m_pIceCube_3	= NULL;
		}
	}

	//Rendering Cube 4
	if( m_pIceCube_4 ){
		glPushMatrix();
		m_pIceCube_4->DrawIceCube();
		glPopMatrix();
		if (m_pIceCube_4->m_eMoveDirection	== m_pIceCube_4->eDone){
			if( ((m_pIceCube_4->m_iEndRowID >= 0) && (m_pIceCube_4->m_iEndRowID <= RowCount)) || 
				((m_pIceCube_4->m_iEndColID >= 0) && (m_pIceCube_4->m_iEndColID <= ColCount)) )
			{
				m_pCustomLevel->LevelDesign[m_pIceCube_4->m_iEndRowID][m_pIceCube_4->m_iEndColID]	= m_pIceCube_4->m_iCurrentIceID;
			}
			m_pIceCube_4->~IceCube();
			//free(m_pIceCube_4);
			m_pIceCube_4	= NULL;
		}
	}
	glPopMatrix();
}

//-------------------
// MY FUNCTIONS BELOW
//-------------------

