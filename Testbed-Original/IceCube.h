#pragma once
#include "Common.h"

#define LOCAL_IceCube_TXEXTURE 0
#define LOCAL_Diamond_TXEXTURE 1

class IceCube
{
public:

	enum mMoveDirection{
		eMoveUp = 0,
		eMoveDown,
		eMoveRight,
		eMoveLeft,
		eMoveCreated,
		eDone
	};
	mMoveDirection	m_eMoveDirection;
	int				m_iCurrentIceID;
	int				mTextureID[2]; // This declration needs LOCAL DEfinitions to Access it
	

	CustomLevel*	m_pCustomLevel;
	void	setCustLevelObj (CustomLevel* Level);

	IceCube(void);
	IceCube( Vec2f StartPos, Vec2f EndPos, int CurrentRowID, int CurrentColID);
	~IceCube(void);

	Vec2f	m_vPosition;
	Vec2f	m_vEndPosition;

	int		m_iCurrentRowID;
	int		m_iCurrentColID;

	int		m_iEndRowID;
	int		m_iEndColID;

	float	m_fMoveSpeed;

	void	MoveIceCube();
	void	DrawIceCube();
	

	Vec2f	getCurrentPos();
	Vec2f	getCurrentCellID();

	void	CalculateCurrentCellID ();
	void	setDirection ( mMoveDirection MoveDir);
	void	setEndCellID (int RowID, int ColID);

};
