#pragma once
#include <vector>
#include "glew.h"
#include "glut.h"
#include "vectors.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h >

#include <time.h>
#include <math.h>
#include "CustomLevel.h"
#include "Globals.h"
#include "tgaload.h"

// Modify these three numbers for Experiments in "data/config.txt"
#define	MAX_GAME_PLAY				10
#define	MAX_BEE_COUNT				6			// For Exp 6 bees in the game. 
#define DEFINE_KILLER_BEE_COUNT		3			// For Exp Define 2 Bees to Kill before Game Over
#define	PENGUIN_CONTROLLER			0			// used given controller

// Do NOt Modify this!
#define BEE_KILL_POINTS				100

// For followimg two definitions see last line of this file for "static int StartMode"
// see "void LoadAllObject (){}" in Gult_main.cpp
#define RandomStartMode				0		// Random Configuration of Bee and Penguin Positions
#define ConfigStartMode				1		// Non-Random Configuration of Bee and Penguin Positions
#define DebugStartMode				2		// Debug Configuration of Bee and Penguin Positions (set up to investigate)

// Definitions for Graphics
#define	LeftBorder					-20
#define	RowCount					14
#define	ColCount					10
#define	MAX_HEIGHT					660
#define	MAX_WIDTH					480
#define	MIN_HEIGHT					0
#define	MIN_WIDTH					0


// Identifiers in Code
#define FREE					0
#define ICE_BLOCK				1
#define PENGUIN					2
#define KILLER_BEE				3
#define	MOVING_BLOCK			4
#define	DEAD_BEE				5
#define DIAMOND_BLOCK  			8
#define UNKNOWN					9
#define OUT_OF_BOUNDS			10;

/*
	Note: in CustomLevel.cpp
			1 = Static Ice Block
			0 = Empty Space
			2 = Penguin Postion in the Level
			3 = Bee Postion in the Level
			4 = Moving IceCube
			5 = Dead Bee
			8 = DiamondIceCube

	if the Gap between Bee & the Penguin is less than 3 cell the Bee 
	   Speed will increase as he will switch to attack mode from Normal Mode
*/

#define MAX_NO_TEXTURES 			13
#define TXTR_BEE_UP   				0
#define TXTR_BEE_DOWN   			1
#define TXTR_BEE_RIGHT   			2
#define TXTR_BEE_LEFT   			3
#define TXTR_ICE_BLOCK   			4
#define TXTR_PENGUIN_UP      		5
#define TXTR_PENGUIN_DOWN    		6
#define TXTR_PENGUIN_RIGHT   		7
#define TXTR_PENGUIN_LEFT    		8
#define TXTR_START_IMG   			9
#define TXTR_YOU_WIN			   	10		// Not actually used
#define TXTR_GAME_OVER	    		11
#define TXTR_DIAMOND_BLOCK			12


static int m_fRectSize	= 45;

// Set Print_Verbose to true for lots of text to command window
// Set Print_Verbose to false for minimal text to command window
static bool Print_Verbose	= false;

// static int StartMode	= DebugStartMode;
// Comment above line and uncomment next for Setup0 - Random
static int StartMode	= RandomStartMode;
// Comment above line and uncomment next for Setup1
// static int StartMode	= ConfigStartMode;


