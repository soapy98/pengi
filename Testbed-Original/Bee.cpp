#include "Bee.h"
//#include "Globals.h"

Bee::Bee( void ) {
}

Bee::Bee(CustomLevel* TempLevel) {
	m_pCustomLevel	= TempLevel;

	m_fBeeMoveSpeed	= 1;
	m_iCurrentRowID	= -1;
	m_iCurrentColID	= -1;
	m_eBeeState		= eBeeMoveUp;
	m_eBeeStragicState	= eBeeNormal;
	
	m_ePreviousBeeState 	= eBeeCreated;
	
	int RandVal	= rand() % 40;
	int Counter = 0;
	for (int j = 0; j < RowCount; j++){
		for (int i = 0; i < ColCount; i++){
			if( m_pCustomLevel->LevelDesign[j][i] == FREE){
				if(Counter == RandVal){
					mBeePos.x	=((m_fRectSize+1)*(i)+(m_fRectSize/2));
					mBeePos.y	=((m_fRectSize+1)*(j)+(m_fRectSize/2));
					CalculateCurrentCell();
					Counter++;
					break;
				}else{
					Counter++;
				}
			}
		}
	}
	CalculateCurrentCell();
	SetNewEndPos ();
}

Bee::~Bee(void) {
	
}

void Bee::setBeePosition(int X, int Y)
{
	mBeePos.x	=((m_fRectSize+1)*(X)+(m_fRectSize/2));
	mBeePos.y	=((m_fRectSize+1)*(Y)+(m_fRectSize/2));
	CalculateCurrentCell();
}

void Bee::setBeePos(Vec2f pos){
	mBeePos	= pos;

	CalculateCurrentCell();			//	Calculating current Row & col Id's
	SetNewEndPos();
}

Vec2f Bee::getBeePos () {
	return mBeePos;
}


void Bee::calculateNewPath() {

	/*
	1-first get the current pos of the bee
	2-Now decide if you want to move in Row Or col
	3-Once this is decide than decide if you want to go right or left
	4-once this is decided than Find the last Empty Slogth in the bees current row.
		4.1- if there is no cell to move in the current direction than again start from step 2.
		4.2- else if you find the last empty cell without any obstraction than set the movement direction to it.
	5- Once you start the movement continously check the distance detween the bee pos & the expected pos.
		5.1- once it reaches zero start over from step 2
	*/

	int RandDirection_1;
	RandDirection_1	= rand() % 10;		// Generating Random number in range up to 10
//	printf("Bee Random Value: %d \n", RandDirection_1 );
	if (RandDirection_1 < 5)
			Bee_PathFinder1 ();
	else
			Bee_PathFinder2 ();

	if(m_ePreviousBeeState != m_eBeeState ){
		m_ePreviousBeeState = m_eBeeState;
	}
}

void Bee::Bee_PathFinder2 () {

	int		Round = 0;
	bool	PathSelectionDone	= false;
	mBeeStates	Temp_BeeState;

	Temp_BeeState	= m_eBeeState;			// Setting The Temp_BeeState to the Current Bee State
	while (!PathSelectionDone)	{
		switch (Round){
			case 0:
			case 1:
			case 2:
			case 3:
				switch (Temp_BeeState){
					case eBeeMoveUp:
						if (m_eBeeState	== eBeeMoveDown){
							///	Checking wht is the current bee movement direction 
							// this is to avoide the Bee to Move is opposite direction 
							// Unless & until He comes in for the Second Round
							Temp_BeeState	= eBeeMoveRight;
							Round++;
							break;
						}

						if( ((m_iCurrentRowID+1) >= RowCount) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID+1][m_iCurrentColID] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID+1][m_iCurrentColID] == DIAMOND_BLOCK)){
							Temp_BeeState	= eBeeMoveRight;
							Round++;
						}else{
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID+1)+(m_fRectSize/2));
							if(m_vExpectedPos.x == 0){ 
								m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID))+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
					case eBeeMoveRight:
						if (m_eBeeState	== eBeeMoveLeft){
							///	Checking wht is the current bee movement direction 
							// this is to avoide the Bee to Move is opposite direction 
							// Unless & until He comes in for the Second Round
							Temp_BeeState	= eBeeMoveDown;
							Round++;
							break;
						}
						if( ((m_iCurrentColID+1) >= ColCount ) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID+1] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID+1] == DIAMOND_BLOCK)){
							Temp_BeeState	= eBeeMoveDown;
							Round++;
						}else{
							m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID+1))+(m_fRectSize/2));
							if(m_vExpectedPos.y == 0){
								m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
					case eBeeMoveDown:
						if (m_eBeeState	== eBeeMoveUp){
							///	Checking wht is the current bee movement direction 
							// this is to avoide the Bee to Move is opposite direction 
							// Unless & until He comes in for the Second Round
							Temp_BeeState	= eBeeMoveLeft;
							Round++;
							break;
						}
						if( ((m_iCurrentRowID-1) < 0 ) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID-1][m_iCurrentColID] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID-1][m_iCurrentColID] == DIAMOND_BLOCK)){
							Temp_BeeState	= eBeeMoveLeft;
							Round++;
						}else {
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID-1)+(m_fRectSize/2));
							if(m_vExpectedPos.x == 0){ 
								m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID))+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
					case eBeeMoveLeft:
						if (m_eBeeState	== eBeeMoveRight){
							///	Checking wht is the current bee movement direction 
							// this is to avoide the Bee to Move is opposite direction 
							// Unless & until He comes in for the Second Round
							Temp_BeeState	= eBeeMoveUp;
							Round++;
							break;
						}
						if( ((m_iCurrentColID-1) < 0 ) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID-1] == ICE_BLOCK)|| 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID-1] == DIAMOND_BLOCK)){
							Temp_BeeState	= eBeeMoveUp;
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
				switch (Temp_BeeState){
					case eBeeMoveUp:
						if( ((m_iCurrentRowID+1) >= RowCount) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID+1][m_iCurrentColID] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID+1][m_iCurrentColID] == DIAMOND_BLOCK)){
							Temp_BeeState	= eBeeMoveRight;
							Round++;
						}else{
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID+1)+(m_fRectSize/2));
							if(m_vExpectedPos.x == 0){ 
								m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID))+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
					case eBeeMoveRight:
						if( ((m_iCurrentColID+1) >= ColCount ) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID+1] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID+1] == DIAMOND_BLOCK)){
							Temp_BeeState	= eBeeMoveDown;
							Round++;
						}else{
							m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID+1))+(m_fRectSize/2));
							if(m_vExpectedPos.y == 0){
								m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
					case eBeeMoveDown:
						if( ((m_iCurrentRowID-1) < 0 ) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID-1][m_iCurrentColID] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID-1][m_iCurrentColID] == DIAMOND_BLOCK)){
							Temp_BeeState	= eBeeMoveLeft;
							Round++;
						}else {
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID-1)+(m_fRectSize/2));
							if(m_vExpectedPos.x == 0){ 
								m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID))+(m_fRectSize/2));
							}
							PathSelectionDone	= true;
						}
						break;
					case eBeeMoveLeft:
						if( ((m_iCurrentColID-1) < 0 ) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID-1] == ICE_BLOCK) || 
							( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID-1] == DIAMOND_BLOCK)){
							Temp_BeeState	= eBeeMoveUp;
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
	m_ePreviousBeeState	= m_eBeeState;
	m_eBeeState			= Temp_BeeState;
}

void Bee::Bee_PathFinder1 () {
	int RandDirection_1, RandDirection_2, Cell_Difference;
	RandDirection_1	= rand() % 10;		// Generating Random number in range 0 to 9

	switch(RandDirection_1)	{
		case 0:
		case 2:
		case 5:
		case 7:
		case 9:
			//	Move in Row
			
			RandDirection_2	= rand() % 4;		// Generating Random number in range up to 4
			//	Deciding the Direction Depending on the selection ofRow or Col
			switch(RandDirection_2){
				case 0:
				case 3:
					//	Moving +ve
					m_eBeeState = eBeeMoveRight;
					if((m_iCurrentColID+1) >= ColCount ){
						calculateNewPath();
						return;
					}else{
						if( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID+1] == FREE){
							m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID+1))+(m_fRectSize/2));
							if(m_vExpectedPos.y == 0){
								m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
							}
						}else{
							calculateNewPath();
							return;
						}
					}
					break;

				case 1:
				case 2:
					// Moving -ve
					m_eBeeState = eBeeMoveLeft;
					if((m_iCurrentColID-1) <= 0 ){
						calculateNewPath();
						return;
					}else{
						if( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID-1] == FREE){
							m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID-1))+(m_fRectSize/2));
							if(m_vExpectedPos.y == 0){
								m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
							}
						}else{
							calculateNewPath();
							return;
						}
					}
					break;
			}///	End Of ROW Switch

			break;

		case 1:
		case 3:	
		case 4:
		case 6:
		case 8:
			//	Move in Col
			//srand ( time(NULL) );
			RandDirection_2	= rand() % 4;		// Generating Random number in range up to 4
			//	Deciding the Direction Depending on the selection ofRow or Col
			switch(RandDirection_2){
				case 1:
				case 2:
					//	Moving +ve
					m_eBeeState = eBeeMoveUp;
					if((m_iCurrentRowID+1) >= RowCount ){
						calculateNewPath();
						return;
					}else{
						if( m_pCustomLevel->LevelDesign[m_iCurrentRowID+1][m_iCurrentColID] == FREE){
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID+1)+(m_fRectSize/2));
							if(m_vExpectedPos.x == 0){ 
								m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID))+(m_fRectSize/2));
							}
						}else{
							calculateNewPath();
							return;
						}
					}
					break;

				case 0:
				case 3:
					// Moving -ve
					m_eBeeState = eBeeMoveDown;
					if((m_iCurrentRowID-1) <= 0 ){
						calculateNewPath();
						return;
					}else{
						Cell_Difference = (ColCount-m_iCurrentColID);
						if( m_pCustomLevel->LevelDesign[m_iCurrentRowID-1][m_iCurrentColID] == FREE){
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID-1)+(m_fRectSize/2));
							if(m_vExpectedPos.x == 0){ 
								m_vExpectedPos.x	= ((m_fRectSize+1)*((m_iCurrentColID))+(m_fRectSize/2));
							}
						}else{
							calculateNewPath();
							return;
						}
					}
					break;
			}///	End Of ROW Switch
			break;
	}
}

void Bee::SetNewEndPos () {
	int RandVal	= 0;

	//while ()
	RandVal	= rand() % 40;
	int Counter = 0;
	for (int j = 0; j < RowCount; j++){
		for (int i = 0; i < ColCount; i++){
			if( m_pCustomLevel->LevelDesign[j][i] == FREE)
			{
				if(Counter == RandVal)
				{
					m_vEndPos.x	=((m_fRectSize+1)*(i)+(m_fRectSize/2));
					m_vEndPos.y	=((m_fRectSize+1)*(j)+(m_fRectSize/2));
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

//	CalculateNewPath();
}

void Bee::CalculateCurrentCell() {
	//	Calcualting the Current Row Index for the Bee
	
	int PreviousRowID, PreviousColID;
	PreviousRowID	= m_iCurrentRowID;
	PreviousColID	= m_iCurrentColID;

	for (int j = 0; j < RowCount; j++)
	{
		int PosY	= ((m_fRectSize+1)*(j)+m_fRectSize/2);
		if( abs(mBeePos.y-PosY) < m_fRectSize/2 )
		{
			m_iCurrentRowID	= j;
			break;
		}
	}
	//	Calcualting the Current Col Index for the Bee
	for (int i = 0; i < ColCount; i++)
	{
		int	PosX	 = ((m_fRectSize+1)*(i)+m_fRectSize/2);
		if( abs(mBeePos.x-PosX) < m_fRectSize/2 )
		{
			m_iCurrentColID	= i;
			break;
		}
	}

	//	Setting the Current Bee Postion in the Grid.
	if ( ( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID]	==  MOVING_BLOCK ) ||
		 ( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID]	==  ICE_BLOCK ) ||
		 ( m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID]	==  DIAMOND_BLOCK ) )
	{
	// This is BEE PLUS ICECUBE
		m_eBeeStragicState	= m_eBeeState	= eBeeDead;
		m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID]	=  DEAD_BEE;
		printf("\t\t\tZapping Bee at %d %d\n", m_iCurrentRowID, m_iCurrentColID);
		return;
	}

	if ( ( m_pCustomLevel->LevelDesign[PreviousRowID][PreviousColID] == MOVING_BLOCK) ||
		 ( m_pCustomLevel->LevelDesign[PreviousRowID][PreviousColID]	==  ICE_BLOCK ) ||
		 ( m_pCustomLevel->LevelDesign[PreviousRowID][PreviousColID]	==  DIAMOND_BLOCK ) )
	// This is BEE PLUS ICECUBE
	{
		m_eBeeStragicState	= m_eBeeState	= eBeeDead;
		m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID]	=  DEAD_BEE;
		printf("\t\t\tZapping Bee at %d %d\n", m_iCurrentRowID, m_iCurrentColID);
		return;
	}
	else if (m_pCustomLevel->LevelDesign[PreviousRowID][PreviousColID] == KILLER_BEE)
	{
		m_pCustomLevel->LevelDesign[PreviousRowID][PreviousColID] =  FREE;
	}

	m_pCustomLevel->LevelDesign[m_iCurrentRowID][m_iCurrentColID]		=  KILLER_BEE;
	
	CheckForPenguin();
	
	//	Checking the Direction & If the Bee Has reached his Expected Postion Than set the Course to the New Cell
	if(m_eBeeState == eBeeMoveUp){
		if((m_vExpectedPos.y-mBeePos.y) < 0){
			calculateNewPath ();
		}
	}else if(m_eBeeState == eBeeMoveDown){
		if((mBeePos.y - m_vExpectedPos.y) < 0){
			calculateNewPath ();
		}
	}else if(m_eBeeState == eBeeMoveRight){
		if((m_vExpectedPos.x - mBeePos.x ) < 0){
			calculateNewPath ();
		}
	}else if(m_eBeeState == eBeeMoveLeft){
		if((mBeePos.x - m_vExpectedPos.x) < 0){
			calculateNewPath ();
		}
	}

	//	This will be Called for the Very first time only when the Expected cell/postion is not yet set.
	if( ( m_vExpectedPos.x == 0) && (m_vExpectedPos.y == 0)){
		calculateNewPath ();
	}
}


void Bee::CheckForPenguin () {
	m_fBeeMoveSpeed	= 1;
	m_eBeeStragicState	=	eBeeNormal;

	for ( int j = 0; j < RowCount; j++ ) {
		//	Checking the Bee Current row for Presence of bee
		if( m_pCustomLevel->LevelDesign[j][m_iCurrentColID]	== PENGUIN ){		//	Checking for the Penguin.
			//	Now confirming if the Bee is found above the Bee or below
			if ( j > m_iCurrentRowID){
				//	Bee Found On top Of the Bee. Now Find if there is any brick available between Bee & Bee
				bool IceCubePresent = false;
				for(int i = m_iCurrentRowID; i < j; i++){
					if( (m_pCustomLevel->LevelDesign[i][m_iCurrentColID] == ICE_BLOCK) ||
						(m_pCustomLevel->LevelDesign[i][m_iCurrentColID] == DIAMOND_BLOCK) ){
						IceCubePresent		= true;
					}
				}
				if (!IceCubePresent){
					//m_fBeeMoveSpeed		=	2;
					m_fBeeMoveSpeed		=	1;
					m_eBeeStragicState	=	eBeeAttack;
					if( abs(mBeePos.x - m_vExpectedPos.x) <=m_fBeeMoveSpeed ){
						mBeePos.x		= m_vExpectedPos.x;
						if (abs(mBeePos.y - m_vExpectedPos.y) <=m_fBeeMoveSpeed ) {
							mBeePos.y		= m_vExpectedPos.y;
							m_eBeeState		=	eBeeMoveUp;
							for (int a = 0; a < RowCount; a++){
								int PosY	= ((m_fRectSize+1)*(a)+m_fRectSize/2);
								if( abs(mBeePos.y-PosY) < m_fRectSize/2 ){
									m_iCurrentRowID	= a;
									break;
								}
							}
							//	Calcualting the Current Col Index for the Bee
							for (int a = 0; a < ColCount; a++){
								int	PosX	 = ((m_fRectSize+1)*(a)+m_fRectSize/2);
								if( abs(mBeePos.x-PosX) < m_fRectSize/2 ){
									m_iCurrentColID	= a;
									break;
								}
							}

							m_vExpectedPos.x	= ((m_fRectSize+1)*(m_iCurrentColID)+(m_fRectSize/2));	
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID+1)+(m_fRectSize/2));
						}
					}
					//if( abs(mBeePos.y - m_vExpectedPos.y) <=m_fBeeMoveSpeed ){
					//	m_eBeeState		= eBeeMoveUp;
					//	mBeePos.y		= m_vExpectedPos.y;
					//}
				}
			}else if (j < m_iCurrentRowID){
				//	Bee Found Below the Bee
				bool	IceCubePresent	= false;
				for(int i = m_iCurrentRowID; i > j; i--){		// Checking if there is no ice cube present in between
					if( (m_pCustomLevel->LevelDesign[i][m_iCurrentColID] == ICE_BLOCK) || 
						(m_pCustomLevel->LevelDesign[i][m_iCurrentColID] == DIAMOND_BLOCK) ){
						IceCubePresent	= true;
					}
				}
				if (!IceCubePresent){
					//m_fBeeMoveSpeed		=	2;
					m_fBeeMoveSpeed		=	1;
					m_eBeeStragicState	=	eBeeAttack;
					if( abs(mBeePos.x - m_vExpectedPos.x) <=m_fBeeMoveSpeed ){
						mBeePos.x		= m_vExpectedPos.x;
						if (abs(mBeePos.y - m_vExpectedPos.y) <=m_fBeeMoveSpeed ) {
							mBeePos.y		= m_vExpectedPos.y;
							m_eBeeState		=	eBeeMoveDown;
							for (int a = 0; a < RowCount; a++){
								int PosY	= ((m_fRectSize+1)*(a)+m_fRectSize/2);
								if( abs(mBeePos.y-PosY) < m_fRectSize/2 ){
									m_iCurrentRowID	= a;
									break;
								}
							}
							//	Calcualting the Current Col Index for the Bee
							for (int a = 0; a < ColCount; a++){
								int	PosX	 = ((m_fRectSize+1)*(a)+m_fRectSize/2);
								if( abs(mBeePos.x-PosX) < m_fRectSize/2 ){
									m_iCurrentColID	= a;
									break;
								}
							}

							m_vExpectedPos.x	= ((m_fRectSize+1)*(m_iCurrentColID)+(m_fRectSize/2));	
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID-1)+(m_fRectSize/2));
						}
					}
					//if( abs(mBeePos.y - m_vExpectedPos.y) <=m_fBeeMoveSpeed ){
					//	m_eBeeState		=	eBeeMoveDown;
					//	mBeePos.y		= m_vExpectedPos.y;
					//}
				}
			}
			break;
		}
	}//	End of Row for loop


	for ( int j = 0; j < ColCount; j++ ) {
		//	Checking the Bee Current row for Presence of bee
		if( m_pCustomLevel->LevelDesign[m_iCurrentRowID][j]	== PENGUIN ){		//	Checking for the Penguin.
			if ( j > m_iCurrentColID){
				//	Tht means the Bee Is on the right side
				bool IceCubePresent	= false;
				for(int i = m_iCurrentColID; i < j; i++){
					if( (m_pCustomLevel->LevelDesign[m_iCurrentRowID][i] == ICE_BLOCK) || 
						(m_pCustomLevel->LevelDesign[m_iCurrentRowID][i] == DIAMOND_BLOCK) ){
						IceCubePresent = true;
					}
				}
				if (!IceCubePresent){
					//m_fBeeMoveSpeed		=	2;
					m_fBeeMoveSpeed		=	1;
					m_eBeeStragicState	=	eBeeAttack;
					if( abs(mBeePos.x - m_vExpectedPos.x) <=m_fBeeMoveSpeed ){
						mBeePos.x		= m_vExpectedPos.x;
						if (abs(mBeePos.y - m_vExpectedPos.y) <=m_fBeeMoveSpeed ) {
							mBeePos.y		= m_vExpectedPos.y;
							m_eBeeState		=	eBeeMoveRight;
							for (int a = 0; a < RowCount; a++){
								int PosY	= ((m_fRectSize+1)*(a)+m_fRectSize/2);
								if( abs(mBeePos.y-PosY) < m_fRectSize/2 ){
									m_iCurrentRowID	= a;
									break;
								}
							}
							//	Calcualting the Current Col Index for the Bee
							for (int a = 0; a < ColCount; a++){
								int	PosX	 = ((m_fRectSize+1)*(a)+m_fRectSize/2);
								if( abs(mBeePos.x-PosX) < m_fRectSize/2 ){
									m_iCurrentColID	= a;
									break;
								}
							}

							m_vExpectedPos.x	= ((m_fRectSize+1)*(m_iCurrentColID+1)+(m_fRectSize/2));	
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));
						}
					}
				}
			}else if (j < m_iCurrentColID){
				//	Bee Found on the Left Side
				bool IceCubePresent	= false;
				for(int i = m_iCurrentColID; i > j; i--){
					if( (m_pCustomLevel->LevelDesign[m_iCurrentRowID][i] == ICE_BLOCK) || 
						(m_pCustomLevel->LevelDesign[m_iCurrentRowID][i] == DIAMOND_BLOCK) ) {
						IceCubePresent	= true;
					}
				}
				if (!IceCubePresent){
					//m_fBeeMoveSpeed		=	2;
					m_fBeeMoveSpeed		=	1;
					m_eBeeStragicState	=	eBeeAttack;
					if( abs(mBeePos.x - m_vExpectedPos.x) <=m_fBeeMoveSpeed ){
						mBeePos.x		= m_vExpectedPos.x;
						if (abs(mBeePos.y - m_vExpectedPos.y) <=m_fBeeMoveSpeed ) {
							mBeePos.y		= m_vExpectedPos.y;
							m_eBeeState		=	eBeeMoveLeft;

							for (int a = 0; a < RowCount; a++){
								int PosY	= ((m_fRectSize+1)*(a)+m_fRectSize/2);
								if( abs(mBeePos.y-PosY) < m_fRectSize/2 ){
									m_iCurrentRowID	= a;
									break;
								}
							}
							//	Calcualting the Current Col Index for the Bee
							for (int a = 0; a < ColCount; a++){
								int	PosX	 = ((m_fRectSize+1)*(a)+m_fRectSize/2);
								if( abs(mBeePos.x-PosX) < m_fRectSize/2 ){
									m_iCurrentColID	= a;
									break;
								}
							}

							m_vExpectedPos.x	= ((m_fRectSize+1)*(m_iCurrentColID-1)+(m_fRectSize/2));	
							m_vExpectedPos.y	= ((m_fRectSize+1)*(m_iCurrentRowID)+(m_fRectSize/2));	
						}
					}
				}
			}
			break;
		}
	}//	End of Row for loop
}

void Bee::moveBee(){
//	Moving the Bee in the respective position 
// & if it reaches the Expeced postion of the end of the Level/grid new cell/postion is set when he is suppose to go.
	switch (m_eBeeState )
	{
		case eBeeMoveUp:
		{
			mBeePos.y	+= m_fBeeMoveSpeed;
			if( (mBeePos.y > (MAX_HEIGHT-(m_fRectSize/2))) || (abs(mBeePos.y - m_vExpectedPos.y) > (m_fRectSize+1)) )
			{
				mBeePos.y	-= m_fBeeMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
		case eBeeMoveDown:
		{
			mBeePos.y	-= m_fBeeMoveSpeed;
			if( (mBeePos.y < (MIN_HEIGHT+(m_fRectSize/2))) || (abs(mBeePos.y - m_vExpectedPos.y) > (m_fRectSize+1)) )
			{
				mBeePos.y	+= m_fBeeMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
		case eBeeMoveLeft:
		{
			mBeePos.x	-= m_fBeeMoveSpeed;
			if ( (mBeePos.x < (MIN_WIDTH+(m_fRectSize/2))) || (abs(mBeePos.y - m_vExpectedPos.y) > (m_fRectSize+1)) )
			{
				mBeePos.x	+= m_fBeeMoveSpeed;
				calculateNewPath ();
			}
			break;
		}
		case eBeeMoveRight:
		{
			mBeePos.x	+= m_fBeeMoveSpeed;
			if( (mBeePos.x > (MAX_WIDTH-(m_fRectSize/2))) || (abs(mBeePos.y - m_vExpectedPos.y) > (m_fRectSize+1)) )
			{
				mBeePos.x	-= m_fBeeMoveSpeed;
				calculateNewPath ();
			}
		}
	}
	//	Calculating 
	CalculateCurrentCell();
}

void Bee::renderBee(void){

	if (m_eBeeState == eBeeDead)
	{
		return;
	}
	moveBee();
	float	size	= (m_fRectSize/2);
	glPushMatrix();
		glTranslatef(mBeePos.x,mBeePos.y,0);
		glBegin(GL_QUADS);						// Draw A Quad
			glTexCoord2f (0.0, 0.0);
			glVertex3f (-size, -size, -2.0);
			glTexCoord2f (1.0, 0.0);
			glVertex3f (size, -size, -2.0);
			glTexCoord2f (1.0, 1.0);
			glVertex3f (size, size, -2.0);
			glTexCoord2f (0.0, 1.0);
			glVertex3f (-size, size, -2.0);
		glEnd();								// Done Drawing The Quad
	glPopMatrix();
}

void Bee::setCustLevelObj ( CustomLevel* Level) {
	m_pCustomLevel	= Level;
}