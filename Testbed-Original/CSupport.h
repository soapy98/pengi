#pragma once 

#include <stdio.h>
#include <string>
#include <string.h>

#include <string.h>
#include <windows.h>
#include "glut.h"

class CSupport
{
private:
	float m_fLastFPS;
	float m_fFps;
	float m_fFrames;
	std::string str;
public:
	CSupport();
	~CSupport();

	bool IsExtensionSupported(char*);
	float FramesPerSecond();	
	void glPrint(int ,int, float );
	void glPrint(int ,int, char* );

	void Draw_FullScreen_Texture( int TextureId );							///	This will Display Texture on the whole screen
	void Draw_Texture( int PosX, int PosY, int Width, int Height);			///	This will Draw The Texture at the given pos & given size.
	void glDrawTexture( int x,int y,int TextureId, bool Transparent);		///	This will Display Texture on the screen but with Transparensy
};
