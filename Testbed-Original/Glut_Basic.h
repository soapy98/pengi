#include <vector>
#include "vectors.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h >
#include "glew.h"
#include "glut.h"
//#include "tgaload.h"

#include "CSupport.h"
//#include "PickingObjects.h"
//#include "HandleMayaObject.h"

#define RENDER 1
#define SELECT 2

#define MAX_NO_TEXTURES 		9
#define MAX_NO_OF_MAYA_TEXTURES	0	
#define MAX_NO_OBJECTS			0					//	This will define no. of Objects whic can b drawn
#define Max_NO_OF_MAYA_OBJ		1					//	This are The Max No of Maya Objects.
#define MAX_NO_OF_SHADERS		4					//	This defines The Max no. of shaders which vr using
#define MAX_NO_OF_MATERIALS		3					//	This defines The Types of materials used

#define TEXTURE_0   			0
#define TEXTURE_1   			1
#define TEXTURE_2   			2
#define TEXTURE_3   			3
#define TEXTURE_4   			4
#define TEXTURE_5   			5
#define TEXTURE_6   			6
#define TEXTURE_7   			7
#define TEXTURE_8   			8
#define TEXTURE_9   			9
#define TEXTURE_10				10					//	This are for Maya Textures
#define TEXTURE_11				11					//	This are for Maya Textures
#define TEXTURE_12				12					//	This are for Maya Textures

char * Str;

int g_iWinWidth = 640;
int g_iWinHeight = 480;
int ShaderNo;
int ObjectsID;
int	TextureID;
int Rotatex = 0,
	Rotatez = 0,
	Rotatey = 0;

Vec3f m_vGloble_Translate;

bool ModelSizeChange;

float ModelSize;
float RotateX, RotateY, RotateZ ;
Vec3f CurrentCameraPos;					///	This will Set The Camera Position.
Vec3f CurrentCameraLookAt;				///	This will Set The Camera Look at.
Vec3f CurrentLightPos;					///	This will Set The Light Position.

float EyePosition[3]		=	{0,10,0};

////////**************** Setting Light Property ****************///////

float 	LightPosition[4]	= {0, 0, 1000, 1};
float 	Specular [4]		= {0.4902, 0.4887, 0.4887, 1};
float 	Ambient[4]			= {0.3684,0.3684,0.3684,1};
float 	Diffuse[4]			= {1,1,1,1};
float	Spec_Radius,							///	This Will Set The Radius Of The Specular Spot.
		Material_Specular_Val;					/// This defines specular val 
int		Material_ID;							/// This will define The Material type & according We will get the Light effects


GLuint  texture_id [MAX_NO_TEXTURES];				/////	Bed Texture Array
GLuint  texture_id2 [MAX_NO_TEXTURES];				/////	Bed Sheet Texture Array

int		BedTextureID;
int		BedSheetTextureID;
bool	ShowDeveloperName;

GLuint	BumpTexture;
GLfloat *values;

GLuint Shader0, prg_1, prg_2, prg_3, Material_Shader, BumpShader;
GLuint v,f;

char *ReadFile(char *fn);
void DrawObjects( void );
void DrawString( void );

void SetCurrentShader( int index );				
void DrawMayaObj( void );

void SetCameraPosition( Vec3f Pos );
Vec3f GetCameraPosition( void );

void SetLightPosition( Vec3f Pos );
Vec3f GetLightPosition( void );

void SetMaterialProperty(int Material_ID);			// This will set The Current Material type.
int GetMaterialProperty( void );					// This will give The Current Material type.

void Render( void );

///----------- VBO Functions --------------////


Vec3f *VBO_Vertex_Arr;
Vec3f *VBO_Normal_Arr;
Vec2f *VBO_Texture_Arr;
GLuint *buffer;
GLuint *NormalBuffer;
GLuint *TextureBuffer;

void VBO_Init( void );

