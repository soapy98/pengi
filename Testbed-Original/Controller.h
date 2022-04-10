#pragma once
#include "Common.h"
#include "Bee.h"
#include "Penguin.h"
#include "../PenguinNew.h"

char * Str;

int g_iWinWidth =  460;
int g_iWinHeight = 645;

int	TextureID;

enum eGameState{
	eStartScreen = 0,
	eGameStarted,
	eYouWin,
	eGameOver
};
// Following are Global defined in Init to define Game Parameters
int GAME_BeeKillCount;
int GAME_MAX_BEE_COUNT;
int GAME_MAXGAMEPLAY;

eGameState	m_eGameState;

int m_iBeeKillCount;				//	This will keep track of the Number of bees killed by the Penguin

Vec2f	m_fGridPosition[RowCount][ColCount];

GLuint  texture_id [MAX_NO_TEXTURES];				/////	This will load the complete texture set


void Render( void );
void print_gameboard(void);					// This uses printf to disoplay state of gameboard
void DrawBoarder ( void );
void DrawLevelGrid ( void );
void drawoneBee ( Bee local_Bee );
void drawBee ( void );
void drawPenguin ( void );

void displayWelcomeImg( void );
void displayGameOverImg( void );
void displayGameWinImg( void );

void ShiftCubeLeft(int RowID, int ColID);
void ShiftCubeRight(int RowID, int ColID);
void ShiftCubeDown(int RowID, int ColID);
void ShiftCubeUp(int RowID, int ColID);

void LoadAllObject(void);
void ResetLevel(void);
void ReadConfig(void);

Bee*	m_pBees_1;					//	Creating Object for Bees
Bee*	m_pBees_2;					//	Creating Object for Bees
Bee*	m_pBees_3;					//	Creating Object for Bees
Bee*	m_pBees_4;					//	Creating Object for Bees
Bee*	m_pBees_5;					//	Creating Object for Bees
Bee*	m_pBees_6;					//	Creating Object for Bees

PenguinNew*	m_pPenguin;

CustomLevel*	m_pCustLevel;
//
//IceCube*		m_pIceCube_1;
//IceCube*		m_pIceCube_2;
//IceCube*		m_pIceCube_3;
//IceCube*		m_pIceCube_4;
