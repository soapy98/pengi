#pragma once
#include "Common.h"

class CustomLevel
{
public:
	CustomLevel(void);
	~CustomLevel(void);

	int		mTextureID[ 13 ];			// cannot see MAX_NO_TEXTURES in Common.h!!!!!
	int		LevelDesign[14][10];		//	Storing The Current Layout of the level.
	//float	m_fMoveSpeed;				//	The Speed with which the Ice Cube will move this is wil faster than bee & penguin movement speed.
	//Vec2f	m_vCubeID;

	//Vec2f	m_fDisplacement;
	

	/*
	Moving the given Row & Col of the Ice cube will move him in the Provided Direction 1= Up, 2= Right, 3= Down, 4= Left
	once when the Ice Cube is asked to Move the Vale in the grid will be ched from 1 to 2. 
	This is done so that the Bee wont recognise the Movement of the Ice Cube.
	& when its get in contact it will be killed. 
	& once the ice cube hits the End the value will than again return to 1 creating new path for the bee & penguin to follow.
	*/

	void	DrawLevel ();
};
