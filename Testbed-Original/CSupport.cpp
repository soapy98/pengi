#include "CSupport.h"

// Mainly GL and GLUT Support Functions
CSupport::CSupport()
{
	str = "FPS";
	m_fFps = 0.0;
	m_fLastFPS = 0.0;
	m_fFrames = 0.0;
}
CSupport::~CSupport()
{
}
bool CSupport::IsExtensionSupported(char* extension)
{
	const unsigned char	*pExtensions = NULL;
	const unsigned char	*pStart;
	unsigned char	*pWhere, *pTerminator;
	
	pWhere = (unsigned char *) strchr (extension, ' ');
	if(pWhere || extension == '\0')
		return false;
	pExtensions = glGetString(GL_EXTENSIONS);
	pStart = pExtensions;
	for(;;)
	{
		pWhere = (unsigned char *) strstr ((const char*) pStart, extension);
		if(!pWhere)
			break;
		pTerminator = pWhere + strlen(extension);
		if(pWhere == pStart || *(pWhere - 1) == ' ')
			if(*pTerminator == ' ' || *pTerminator == '\0')
				return true;
		pStart = pTerminator;
	}
	return false;
}
float CSupport::FramesPerSecond()
{
	if(GetTickCount() - m_fLastFPS >= 1000 )
	{
		m_fLastFPS = GetTickCount();
		m_fFps = m_fFrames;
		str = m_fFps;
		m_fFrames = 0;
		//printf("%f", m_fFps);
	}
	m_fFrames++;
	return m_fFps;
}
void CSupport::glPrint(int x, int y, float fps)	
{
	glBindTexture(GL_TEXTURE_2D, 0);			
	glMatrixMode(GL_PROJECTION);						
	glPushMatrix();										
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glOrtho(0,1000,0,1000,-1,1);							
	glMatrixMode(GL_MODELVIEW);							
	glPushMatrix();										
	glLoadIdentity();									
	glRasterPos2d(x,y);
	char c[1000];
	itoa(fps, c, 10);
	for (int i =0 ; i < (int)strlen(c); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c[i] );
	
	glMatrixMode(GL_PROJECTION);						
	glPopMatrix();										
	glMatrixMode(GL_MODELVIEW);	
	glEnable(GL_LIGHTING);
	glPopMatrix();										
}

void CSupport::glPrint(int x, int y, char* string)	
{
	glBindTexture(GL_TEXTURE_2D, 0);			
	glMatrixMode(GL_PROJECTION);						
	glPushMatrix();										
	glLoadIdentity();				
	glDisable(GL_LIGHTING);
	glOrtho(0,1000,0,1000,-1,1);													
	glMatrixMode(GL_MODELVIEW);							
	glPushMatrix();										
	glLoadIdentity();									
	glRasterPos2d(x,y);
	for (int i =0 ; i < (int)strlen(string); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i] );

	glMatrixMode(GL_PROJECTION);						
	glPopMatrix();										
	glMatrixMode(GL_MODELVIEW);							
	glEnable(GL_LIGHTING);
	glPopMatrix();										
}

void CSupport::Draw_FullScreen_Texture( int TextureId )
{
	glBindTexture(GL_TEXTURE_2D,TextureId);
	glMatrixMode(GL_PROJECTION);						
	glPushMatrix();										
	glLoadIdentity();				
	glDisable(GL_LIGHTING);
	glOrtho(0,1000,0,1000,-1,1);													
	glMatrixMode(GL_MODELVIEW);							
	glPushMatrix();										
	glLoadIdentity();									
		
	///	Disp. the texture o whole screen.
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,1.0f);	glVertex3f(1000.0f, 1000.0f,0.50f);
		glTexCoord2f(0.0f,1.0f);	glVertex3f(0.0f, 1000.0f,0.50f);
		glTexCoord2f(0.0f,0.0f);	glVertex3f(0.0f, 0.0f,0.50f);
		glTexCoord2f(1.0f,0.0f);	glVertex3f(1000.0f, 0.0f,0.5f);
	glEnd();

	glMatrixMode(GL_PROJECTION);						
	glPopMatrix();										
	glMatrixMode(GL_MODELVIEW);							
	glEnable(GL_LIGHTING);
	glPopMatrix();

}