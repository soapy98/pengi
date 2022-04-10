#include "Controller.h"
#include <fstream>
#include <iostream>
#include <string>
#include "../PathFinder.h"
#include "../IceCubeNew.h";

using namespace std;

//-----------------------------------------------------------------------------
/* These are defined in Common.h BUT are over-ridden with values in data//config.txt
#define	MAX_GAME_PLAY				10
#define	MAX_BEE_COUNT				6			// For Exp 3 bees in the game. as used in NumofBees
#define DEFINE_KILLER_BEE_COUNT		3			// For Exp Define 2 Bees to Kill before Game Over
// see "void LoadAllObject (){}" in Gult_main.cpp
*/
void ReadConfig() {
	GAME_BeeKillCount	= DEFINE_KILLER_BEE_COUNT;	// Defines when you WIN a round on Bee Kill Count
	GAME_MAX_BEE_COUNT	= MAX_BEE_COUNT;			// Defines number of Bees in Game
	GAME_MAXGAMEPLAY	= MAX_GAME_PLAY;			// Defines number of Rounds to GAME

	ifstream fin("data//config.txt");
	if(fin.is_open())
	{
		string attribute;
		int parameter;
		while (fin >> attribute) {
			fin >> parameter;
			if(parameter >= 0)
			{
				if(attribute == "beekillcount")
				{
					if((parameter > 0)&&(parameter < 7))
						GAME_BeeKillCount = parameter;
					else
						GAME_BeeKillCount	= DEFINE_KILLER_BEE_COUNT;
				}
				else if(attribute == "maxbeecount")
				{
					if((parameter > 0)&&(parameter < 7))
						GAME_MAX_BEE_COUNT =parameter; // = parameter
					else
						GAME_MAX_BEE_COUNT	= MAX_BEE_COUNT;
				}
				else if(attribute == "maxgameplay")
				{
					if(parameter > 0)
						GAME_MAXGAMEPLAY = parameter;
					else
						GAME_MAXGAMEPLAY	= MAX_GAME_PLAY;
				}
			}
		}
		fin.close();
	}
}//ReadConfig

//-----------------------------------------------------------------------------
// Two simple functions to Display and Initialise Game Stats
void Display_game_stats(void)
{
	cout << "\tPlay Count: " << playCount << endl;
	cout << "\tWin Count: " << winCount << endl;
	cout << "\tLose Count: " << loseCount << endl;
	cout << "\tGame Points: " << GamePoints << endl;
	cout << "\tGame Moves: " << NumofMoves << endl;
}

void InitStats( void )
{
	playCount=1;
	winCount = 0;
	loseCount = 0;
	GamePoints = 0;
	NumofMoves = 0;
}

// Display gamebopard to Command Window
void print_gameboard()
{
	int ii, jj;
	for(ii=0;ii<14; ii++)
	{
		printf("\t%d\t\t",(14-ii));
		for(jj=0;jj <10;jj++)
		{
		 printf(" %d",m_pCustLevel->LevelDesign[(13-ii)][jj]);
		}
		printf("\n");
	}
}

void SpecialKey ( int k, int x, int y )
{
	switch( k )
	{
		case GLUT_KEY_UP:
			m_pPenguin->mMovementState = m_pPenguin->ePenguinMoveUp;// m_eBeeState = 0;
			m_pPenguin->PushCube(1, 0);
			break;
		case GLUT_KEY_DOWN:
			m_pPenguin->mMovementState = m_pPenguin->ePenguinMoveDown;
			m_pPenguin->PushCube(-1, 0);
			break;
		case GLUT_KEY_LEFT:
			m_pPenguin->mMovementState = m_pPenguin->ePenguinMoveLeft;
			m_pPenguin->PushCube(0, -1);
			break;
		case GLUT_KEY_RIGHT:
			m_pPenguin->mMovementState = m_pPenguin->ePenguinMoveRight;
			m_pPenguin->PushCube(0, 1);
			break;
	}
}

void KeyPressed( unsigned char k, int x, int y )
{

	
	switch (k) 
	{ 

		case 'q':
		case 'Q':
		case 27: 
				exit(1);
			break; 

		case 'a':
		case 'A':
				//	Print the Current Level Array
				print_gameboard();
				printf("\n--------------\nDONE\n-------------------\n");
			break;

		case 'r':
		case 'R':
				printf("\n-----------------\tNew Game\t----------------------\n");
				InitStats();
				ResetLevel();							//	Reloading Level
				m_eGameState	= eGameStarted;			//	Starting the Game
				InGamePlay = true;
			break;

		case 's':
		case 'S':
				printf("\n-----------------\tNew Game\t----------------------\n");
				InitStats();
				ResetLevel();//LoadAllObject();						//	Loading the Penguin & the Bee
				m_eGameState	= eGameStarted;			//	Starting the Game
				InGamePlay = true;
			break;

/* DONT DO THIS
////******** Changing The Polygon Mode to Point*******************
		case 'p':
		case 'P':
			glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
			break;

		case 'z':
		case 'Z':
			srand ( time(NULL) );
			break;
*/
		case ' ':
			//m_pPenguin->m_ePenguinState	= m_pPenguin->ePenguinCreated;
			break;
	} 
} //KeyPressed

void DummyDisplay( void )
{}

void LoadLight( void )
{
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );

	glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHTING );
}

void Render( void )							// The Code Which we always want to disp.
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//glClearColor(0.25,0.25,0.35,1);
	glClearColor(1,1,1,1);
	
	glMatrixMode( GL_MODELVIEW );	
	glLoadIdentity();

	switch (m_eGameState){
		case eStartScreen:
				displayWelcomeImg();
			break;

		case eGameStarted:
			//Sleep(10);
			drawBee ();
			drawPenguin();
			
			if(m_pCustLevel)
			{
				DrawLevelGrid();
			}
			break;

		case eYouWin:
//			displayGameWinImg();
				if (InGamePlay)
				{								
					winCount++;
					GamePoints += 3*BEE_KILL_POINTS;
					Display_game_stats();
					playCount++;
					if (playCount <= GAME_MAXGAMEPLAY)
					{
						m_eGameState	= eGameStarted;			//	Starting the Game
						ResetLevel();//LoadAllObject();						//	Loading the Penguin & the Bee	
					}
					else
					{
						InGamePlay = false;
						printf("\n-----------------\tGame Over\t----------------------\n");
					}
				}
				else displayGameOverImg();	
			break;

		case eGameOver:
				if (InGamePlay)
				{							
					loseCount++;
					Display_game_stats();
					playCount++;
					if (playCount <= GAME_MAXGAMEPLAY)
					{
						m_eGameState	= eGameStarted;			//	Starting the Game
						ResetLevel();//LoadAllObject();						//	Loading the Penguin & the Bee	
					}
					else
					{
//						displayGameOverImg();	
						InGamePlay = false;
						printf("\n-----------------\tGame Over\t----------------------\n");
					}
				}
				else displayGameOverImg();	
			break;
	}
	glutSwapBuffers();
} //Render

void displayGameWinImg(){
	float	sizeX	= 220;
	float	sizeY	= 180;
//	Display_game_stats();
	glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_YOU_WIN ]);

	glPushMatrix();
		glTranslatef(g_iWinWidth/2,g_iWinHeight/2,0);
		glBegin(GL_QUADS);						// Draw A Quad
			glTexCoord2f (0.0, 0.0);
			glVertex3f (-sizeX, -sizeY, -2.0);
			glTexCoord2f (1.0, 0.0);
			glVertex3f (sizeX, -sizeY, -2.0);
			glTexCoord2f (1.0, 1.0);
			glVertex3f (sizeX, sizeY, -2.0);
			glTexCoord2f (0.0, 1.0);
			glVertex3f (-sizeX, sizeY, -2.0);
		glEnd();							// Done Drawing The Quad
	glPopMatrix();
}

void displayGameOverImg(){
	float	sizeX	= 220;
	float	sizeY	= 180;
//	Display_game_stats();
	glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_GAME_OVER ]);

	glPushMatrix();
		glTranslatef(g_iWinWidth/2,g_iWinHeight/2,0);
		glBegin(GL_QUADS);						// Draw A Quad
			glTexCoord2f (0.0, 0.0);
			glVertex3f (-sizeX, -sizeY, -2.0);
			glTexCoord2f (1.0, 0.0);
			glVertex3f (sizeX, -sizeY, -2.0);
			glTexCoord2f (1.0, 1.0);
			glVertex3f (sizeX, sizeY, -2.0);
			glTexCoord2f (0.0, 1.0);
			glVertex3f (-sizeX, sizeY, -2.0);
		glEnd();							// Done Drawing The Quad
	glPopMatrix();
}

void displayWelcomeImg(){
	float	sizeX	= 220;
	float	sizeY	= 180;

	glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_START_IMG ]);

	glPushMatrix();
		glTranslatef(g_iWinWidth/2,g_iWinHeight/2,0);
		glBegin(GL_QUADS);						// Draw A Quad
			glTexCoord2f (0.0, 0.0);
			glVertex3f (-sizeX, -sizeY, -2.0);
			glTexCoord2f (1.0, 0.0);
			glVertex3f (sizeX, -sizeY, -2.0);
			glTexCoord2f (1.0, 1.0);
			glVertex3f (sizeX, sizeY, -2.0);
			glTexCoord2f (0.0, 1.0);
			glVertex3f (-sizeX, sizeY, -2.0);
		glEnd();							// Done Drawing The Quad
	glPopMatrix();
}

void drawPenguin () {
	if(m_pPenguin)
	{
		//if (m_pPenguin->m_ePenguinStragicState	!= m_pPenguin->ePenguinDead)
		if (true)
		{
			glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_PENGUIN_UP ]);
			switch (m_pPenguin->mMovementState){
				case m_pPenguin->ePenguinMoveUp:
					glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_PENGUIN_UP ]);
					break;

				case m_pPenguin->ePenguinMoveDown:
					glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_PENGUIN_DOWN ]);
					break;

				case m_pPenguin->ePenguinMoveRight:
					glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_PENGUIN_RIGHT ]);
					break;

				case m_pPenguin->ePenguinMoveLeft:
					glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_PENGUIN_LEFT ]);
					break;
			}
			m_pPenguin->RenderPenguin();
		}
	}
	///**	std::this_thread::sleep_for (std::chrono::seconds(1));
	Sleep(20);
	NumofMoves++;
}

void drawoneBee(Bee *local_Bee)
{
	if ( (local_Bee->m_eBeeState != local_Bee->eBeeDead) )
	{
		switch (local_Bee->m_eBeeState)
		{
			case local_Bee->eBeeMoveUp:
				glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_BEE_UP ]);
				break;
			case local_Bee->eBeeMoveDown:
				glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_BEE_DOWN ]);
				break;
			case local_Bee->eBeeMoveRight:
				glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_BEE_RIGHT ]);
				break;
			case local_Bee->eBeeMoveLeft:
				glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_BEE_LEFT ]);
				break;
		}
		local_Bee->renderBee();
		if (m_pPenguin)
		{
			if( (abs(m_pPenguin->mPenguinPos.x - local_Bee->mBeePos.x) <= (m_fRectSize/2) )
				&& (abs(m_pPenguin->mPenguinPos.y - local_Bee->mBeePos.y) <= (m_fRectSize/2) ) )
			{
				m_pPenguin->mStrategy = m_pPenguin->eStrategyDead;
				m_eGameState = eGameOver;
			}
		}
	}
}

void drawBeeGameWon()
{
//	printf("\n----------------------------------------------------\n YOU WON THE GAME \n----------------------------------------------------\n");
	m_eGameState	= eYouWin;
}

// There can be amaximum of SIX Bees so take care of them here
void drawBee () 
{
	if(m_pBees_1)
	{
		drawoneBee( m_pBees_1 );
		if (m_pBees_1->m_eBeeState == m_pBees_1->eBeeDead){
			m_pBees_1->~Bee();
			m_pBees_1	= NULL;
			m_iBeeKillCount--;
			GamePoints += BEE_KILL_POINTS;
			if (m_iBeeKillCount == 0)
				drawBeeGameWon();
			else
				m_pBees_1	= new Bee(m_pCustLevel);						//	Creating NEW Bee Object.
		}
	}

	if(m_pBees_2)
	{
		drawoneBee( m_pBees_2 );
		if (m_pBees_2->m_eBeeState == m_pBees_2->eBeeDead){
			m_pBees_2->~Bee();
			m_pBees_2	= NULL;
			GamePoints += BEE_KILL_POINTS;
			m_iBeeKillCount--;
			if (m_iBeeKillCount == 0)
				drawBeeGameWon();
			else
				m_pBees_2	= new Bee(m_pCustLevel);						//	Creating New Bee Object
		}
	}

	if(m_pBees_3)
	{
		drawoneBee( m_pBees_3 );
		if (m_pBees_3->m_eBeeState == m_pBees_3->eBeeDead){
			m_pBees_3->~Bee();
			m_pBees_3	= NULL;
			GamePoints += BEE_KILL_POINTS;
			m_iBeeKillCount--;
			if (m_iBeeKillCount == 0)
				drawBeeGameWon();
			else
				m_pBees_3	= new Bee(m_pCustLevel);						//	Creating New Bee Object
		}
	}

	if(m_pBees_4)
	{
		drawoneBee( m_pBees_4 );
		if (m_pBees_4->m_eBeeState == m_pBees_4->eBeeDead){
			m_pBees_4->~Bee();
			m_pBees_4	= NULL;
			GamePoints += BEE_KILL_POINTS;
			m_iBeeKillCount--;
			if (m_iBeeKillCount == 0)
				drawBeeGameWon();
			else
				m_pBees_4	= new Bee(m_pCustLevel);						//	Creating New Bee Object
		}
	}

	if(m_pBees_5)
	{
		drawoneBee( m_pBees_5 );
		if (m_pBees_5->m_eBeeState == m_pBees_5->eBeeDead){
			m_pBees_5->~Bee();
			m_pBees_5	= NULL;
			GamePoints += BEE_KILL_POINTS;
			m_iBeeKillCount--;
			if (m_iBeeKillCount == 0)
				drawBeeGameWon();
			else
				m_pBees_5	= new Bee(m_pCustLevel);						//	Creating New Bee Object
		}
	}

	if(m_pBees_6)
	{
		drawoneBee( m_pBees_6 );
		if (m_pBees_6->m_eBeeState == m_pBees_6->eBeeDead){
			m_pBees_6->~Bee();
			m_pBees_6	= NULL;
			GamePoints += BEE_KILL_POINTS;
			m_iBeeKillCount--;
			if (m_iBeeKillCount == 0)
				drawBeeGameWon();
			else
				m_pBees_6	= new Bee(m_pCustLevel);						//	Creating New Bee Object
		}
	}
} //drawBee

void renderBitmapString
(
		float x, 
		float y, 
		float z, 
		void *font, 
		char *string) {  
  char *c;
  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

void renderSpacedBitmapString (
			float x, 
			float y,
			int spacing, 
			void *font,
			char *string) {
  char *c;
  int x1=x;
  for (c=string; *c != '\0'; c++) {
	glRasterPos2f(x1,y);
    	glutBitmapCharacter(font, *c);
	x1 = x1 + glutBitmapWidth(font,*c) + spacing;
  }
}

void DrawLevelGrid () {
	glBindTexture(GL_TEXTURE_2D,texture_id [ TXTR_ICE_BLOCK ]);
	m_pCustLevel->DrawLevel();
}

void DrawBoarder () {

	glPushMatrix();
		glScalef(2, g_iWinWidth/2, 1);
		glutSolidCube(10);
	glPopMatrix();
	
	//	Right
	glPushMatrix();
		glTranslatef(g_iWinWidth,0,0);
		glScalef(2, g_iWinWidth/2, 1);
		glutSolidCube(10);
	glPopMatrix();

	// Top 
	glPushMatrix();
		glTranslatef(0,0,0);
		glScalef(g_iWinHeight/2, 2, 1);
		glutSolidCube(10);
	glPopMatrix();
	
	//	TOP
	glPushMatrix();
		glTranslatef(0,g_iWinHeight,0);
		glScalef(g_iWinHeight/2, 2, 1);
		glutSolidCube(10);
	glPopMatrix();
}

void Reshape( int w, int h )
{
	g_iWinWidth = w;
	g_iWinHeight = h;
	glViewport( 0, 0, w, h );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0, g_iWinWidth, 0, g_iWinHeight,0.1,20);
}

void Init( void )			// initial variables are defined here
{
/////**************************** Generating Grid Base Cells ***************/////
	m_eGameState	= eStartScreen;

	m_iBeeKillCount	= GAME_BeeKillCount; // Defines when you WIN a round on Bee Kill Count

	glEnable( GL_TEXTURE_2D );
	
	texture_id [ TXTR_BEE_UP ]			= tgaLoadAndBind ( ".\\Images/BeeUp.tga",TGA_DEFAULT);
	texture_id [ TXTR_BEE_DOWN ]		= tgaLoadAndBind ( ".\\Images/BeeDown_new.tga",TGA_DEFAULT);
	texture_id [ TXTR_BEE_RIGHT ]		= tgaLoadAndBind ( ".\\Images/BeeRight.tga",TGA_DEFAULT);
	texture_id [ TXTR_ICE_BLOCK ]		= tgaLoadAndBind ( ".\\Images/iceBlock.tga",TGA_DEFAULT);
	texture_id [ TXTR_BEE_LEFT ]		= tgaLoadAndBind ( ".\\Images/BeeLeft.tga",TGA_DEFAULT);
	texture_id [ TXTR_PENGUIN_UP    ]	= tgaLoadAndBind ( ".\\Images/PenguinUp.tga",TGA_DEFAULT);
	texture_id [ TXTR_PENGUIN_DOWN  ]	= tgaLoadAndBind ( ".\\Images/PenguinDown.tga",TGA_DEFAULT);
	texture_id [ TXTR_PENGUIN_RIGHT ]	= tgaLoadAndBind ( ".\\Images/PenguinRight.tga",TGA_DEFAULT);
	texture_id [ TXTR_PENGUIN_LEFT  ]	= tgaLoadAndBind ( ".\\Images/PenguinLeft.tga",TGA_DEFAULT);

	texture_id [ TXTR_START_IMG   ]		= tgaLoadAndBind ( ".\\Images/UIScreens/start_up.tga",TGA_DEFAULT);
	texture_id [ TXTR_YOU_WIN	 ]		= tgaLoadAndBind ( ".\\Images/UIScreens/YouWin.tga",TGA_DEFAULT);
	texture_id [ TXTR_GAME_OVER	 ]		= tgaLoadAndBind ( ".\\Images/UIScreens/GAME_OVER.tga",TGA_DEFAULT);
	texture_id [ TXTR_DIAMOND_BLOCK ]	= tgaLoadAndBind ( ".\\Images/DiamondBlock.tga",TGA_DEFAULT);

	glAlphaFunc(GL_GEQUAL,0.125);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glCullFace(GL_FRONT_FACE);
	glEnable(GL_BLEND);

	LoadLight();	

	InitStats();
	InGamePlay = true;
	srand ( time(NULL) );
} //Init

void LoadAllObject ()
{
	int NumofBees;
	m_pCustLevel	= new CustomLevel();			///	Creating the Obj for the Grid/Level
	PathFinder::SetLevel(m_pCustLevel);

	//srand ( time(NULL) );
	for(NumofBees=1; NumofBees <= GAME_MAX_BEE_COUNT; NumofBees++)
	{
		switch(NumofBees)
		{
		case 1:
			m_pBees_1	= new Bee(m_pCustLevel);			//	Creating First Bee Object.
			break;
		case 2:
			m_pBees_2	= new Bee(m_pCustLevel);			//	Creating 2nd Bee Object
			break;
		case 3:
			m_pBees_3	= new Bee(m_pCustLevel);			//	Creating 3rd Bee Object
			break;
		case 4:
			m_pBees_4	= new Bee(m_pCustLevel);			//	Creating 4th Bee Object
			break;
		case 5:
			m_pBees_5	= new Bee(m_pCustLevel);			//	Creating 5th Bee Object
			break;
		case 6:
			m_pBees_6	= new Bee(m_pCustLevel);			//	Creating 6th Bee Object
			break;
		}
	}
	m_pPenguin = new PenguinNew(m_pCustLevel);		//	Creating Penguin GameObject

	if (StartMode==ConfigStartMode)				// Define Startup Positions
	{
			printf("***** Non-Random Start-Up Positions *****\n");
			m_pPenguin->SetPenguinPosition(4, 7);
			m_pBees_1->setBeePosition(1, 2);
			m_pBees_2->setBeePosition(9, 5);
			m_pBees_3->setBeePosition(7, 9);
	}
	if (StartMode==DebugStartMode)				// DEfine DEBUG Startup Positions
	{
			printf("***** Non-Random Start-Up Positions for Debug Purposes*****\n");
			m_pPenguin->SetPenguinPosition(2, 1);
			m_pBees_1->setBeePosition(6, 1);
			m_pBees_2->setBeePosition(7, 1);
			m_pBees_3->setBeePosition(9, 1);
	}
	//m_pPenguin->setIceCubeTextureID(texture_id [ TXTR_ICE_BLOCK ]);

// Uncomment this to SEE a Display of Game-Board as Integer
//	print_gameboard();

} //LoadAllObject

void ResetLevel(){
	m_iBeeKillCount	= GAME_BeeKillCount;
	if(m_pBees_1){
		m_pBees_1->~Bee();
		m_pBees_1 = NULL;
	}

	if(m_pBees_2){
		m_pBees_2->~Bee();
		m_pBees_2 = NULL;
	}

	if(m_pBees_3){
		m_pBees_3->~Bee();
		m_pBees_3 = NULL;
	}

	if(m_pBees_4){
		m_pBees_4->~Bee();
		m_pBees_4 = NULL;
	}

	if(m_pBees_5){
		m_pBees_5->~Bee();
		m_pBees_5 = NULL;
	}

	if(m_pBees_6){
		m_pBees_6->~Bee();
		m_pBees_6 = NULL;
	}

	if(m_pPenguin){
		m_pPenguin->~PenguinNew();
		m_pPenguin = NULL;
	}

	if(m_pCustLevel){
		m_pCustLevel->~CustomLevel();
		m_pCustLevel = NULL;
	}
	printf("\n\n\tGame Round Number: %d\n", playCount);
	LoadAllObject();
} //ResetLevel


int main( int argc, char* argv )		// main fun.
{
	glutInitWindowSize( g_iWinWidth, g_iWinHeight );
	glutInitWindowPosition( 0, 0 );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInit( &argc, &argv );

	glutCreateWindow( "Pengi the killer bee : MSc 08968 ACW" );

	glutKeyboardFunc( KeyPressed );
	glutSpecialFunc( SpecialKey );

	glutIdleFunc( Render );
	glutReshapeFunc( Reshape );
	glutDisplayFunc( Render );

	if ( glewInit() != GLEW_OK )
	{
		printf("\n Error with the glewInit.");
	}
	ReadConfig();	// read game data file config.txt
	Init();
	Sleep(1000);
	glutMainLoop();

	return 1;
} //main
