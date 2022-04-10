#pragma once
#include "Common.h"
#include "IceCube.h"

// How far Penguin can sense
// used in CheckDownforBee, CheckUpforBee, CheckLeftforBee, CheckRightforBee
#define SENSE_LIMIT		10 //5

class Penguin
{
public:
	CustomLevel*	m_pCustomLevel;

	Penguin(void);
	Penguin(CustomLevel* TempLevel);
	~Penguin(void);

public:	

	int m_knownWorld[RowCount][ColCount];
	std::vector<std::pair<int, int>> path; 

	IceCube*		m_pIceCube_1;
	IceCube*		m_pIceCube_2;
	IceCube*		m_pIceCube_3;
	IceCube*		m_pIceCube_4;

	Vec2f	mPenguinPos;
	Vec2f	m_vEndPos;
	Vec2f	m_vExpectedPos;
	float	m_fPenguinMoveSpeed;

	int		m_iCurrentRowID;
	int		m_iCurrentColID;

	GLuint  IceCube_texture_id;

	enum mPenguinStates{
		ePenguinCreated = 0,
		ePenguinMoveUp,
		ePenguinMoveDown,
		ePenguinMoveRight,
		ePenguinMoveLeft,
		ePenguinAttack,
		ePenguinNormal,
		ePenguinRun,
		ePenguinDead
	};
	mPenguinStates	m_ePenguinState;
	mPenguinStates	m_ePreviousPenguinState;
	mPenguinStates	m_ePenguinStragicState;
	mPenguinStates	m_ePreviousPenguinStragicState;

	void	setPenguinPosition ( int X, int Y );
	void	movePenguin_Normal(void);
	void	movePenguin_Attack(void);
	void	movePenguin_Run(void);
	void	movePenguin(void);
	void	calculateNewPosition(void);
	int		CheckUpforBee();
	int		CheckDownforBee();
	int		CheckLeftforBee();
	int		CheckRightforBee();

	void	renderPenguin(void);
	void	CalculateCurrentCell(void);
	void	CheckForBees ( void );
	void	calculateNewPath( void );		// Pseudo AI Control - Random Numbers!
	void	MyPenguinController( void );	// THIS IS the Top-Level ACW Function!
	void	PathFinding1 ();				// Pseudo AI Control - Random Numbers!
	void	PathFinding2 ();				// Pseudo AI Control - Random Numbers!
	void	Move_PenguinPositiveRow ();
	void	Move_PenguinNegativeRow ();
	void	Move_PenguinPositiveColumn ();
	void	Move_PenguinNegativeColumn ();

	void	CheckInUpDirection();
	void	CheckInDownDirection();
	void	CheckInLeftDirection();
	void	CheckInRightDirection();

	void	ShiftIceCubeUp (IceCube *localCube, int RowID, int ColID, int IceBlockType); 
	void	ShiftCubeUp (int RowID, int ColID, int IceBlockType);
	void	ShiftIceCubeDown (IceCube *localCube, int RowID, int ColID, int IceBlockType); 
	void	ShiftCubeDown ( int RowID, int ColID, int IceBlockType );
	void	ShiftIceCubeRight (IceCube *localCube, int RowID, int ColID, int IceBlockType); 
	void	ShiftCubeRight (int RowID, int ColID, int IceBlockType);
	void	ShiftIceCubeLeft (IceCube *localCube, int RowID, int ColID, int IceBlockType); 
	void	ShiftCubeLeft (int RowID, int ColID, int IceBlockType);
	void	setIceCubeTextureID(GLint textureID);

	std::vector<std::pair<int, int>> aStarPath(int sourceRow, int sourceCol, int destRow, int destCol);
};
