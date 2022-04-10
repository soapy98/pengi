#pragma once
#include "Common.h"

class Bee
{
private:
	
	Vec2f	m_vEndPos;
	Vec2f	m_vExpectedPos;
	float	m_fBeeMoveSpeed;
public:
	Vec2f	mBeePos;
	int		m_iCurrentRowID;
	int		m_iCurrentColID;

	CustomLevel*	m_pCustomLevel;

	enum mBeeStates{
		eBeeCreated = 0,
		eBeeMoveUp,
		eBeeMoveDown,
		eBeeMoveRight,
		eBeeMoveLeft,
		eBeeAttack,
		eBeeNormal,
		eBeeDead,
		eBeeChangeDirection
	};
	mBeeStates	m_eBeeState;
	mBeeStates	m_ePreviousBeeState;
	mBeeStates	m_eBeeStragicState;

public:
	Bee(void);
	Bee(CustomLevel* TempLevel);
	~Bee(void);

	void	setBeePosition ( int X, int Y );
	void	setBeePos(Vec2f pos);
	Vec2f	getBeePos( void );
	void	moveBee(void);
	void	renderBee(void);
	void	SetNewEndPos(void);
	void	calculateNewPath(void);
	void	CalculateCurrentCell(void);
	void	pathFinding ();
	void	Bee_PathFinder1();
	void	Bee_PathFinder2();

	void	setCustLevelObj (CustomLevel* Level);
	void	CheckForPenguin ();
};
