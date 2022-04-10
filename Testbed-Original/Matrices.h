#pragma once 

#include <memory.h>
#include "MathGlobals.h"
#include "vectors.h"

const int XAXIS = 1;
const int YAXIS = 2;
const int ZAXIS = 3;

class CMatrix3;

//a 4x3 matrix struct
struct Matrix4x3
{
	union
	{
		float m4x3[4][3];
		struct
		{
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
			float _41, _42, _43;
		};
		struct
		{
			Vec3f Row1;
			Vec3f Row2;
			Vec3f Row3;
			Vec3f Trans;
		};
	};
};

//A 4 by 4 Homogeneous Matrix
class CMatrix4
{
public:
	union //Can access matrix elements as, a 4 by 4 matrix, or a linear 16 entry array,
			// by individual element names
	{
		float m16[16];
		float m4x4[4][4];
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		struct
		{
			Vec3f Row1_3x3; float _14;
			Vec3f Row2_3x3; float _24;
			Vec3f Row3_3x3; float _34;
			Vec3f Trans; float _44;
		};
		struct
		{
			Vec4f Row1;
			Vec4f Row2;
			Vec4f Row3;
			Vec4f Row4;
		};
	};

public:
	CMatrix4();

public:
	CMatrix4 operator+ ( CMatrix4& Matrix );
	CMatrix4 operator- ( CMatrix4& Matrix );
	CMatrix4 operator* ( CMatrix4& Matrix );
	CMatrix4 operator* ( float Factor );

	void ToInverse( CMatrix4& Matrix ); 		//Inverse for transformations
	CMatrix4 Inverse( void );					//Inverse for transformations
	CMatrix4 Inverse( float* pDeterminant );	//general Inverse
	CMatrix4 Transpose( void );

	void LoadIdentity( void );

	void LoadTranslationMatrix( float x, float y, float z );
	void LoadTranslationMatrix( Vec3f* pVector3 );

	void LoadRotationMatrix( int PrimaryAxisID, float Angle );
							//PrimaryAxisID XAXIS, YAXIS, ZAXIS
	void LoadRotationMatrix( Vec3f *pDirection );
	void LoadRotationMatrix( float xDir, float yDir, float zDir );
							//Direction is pointer to a normalized vector

	void LoadScalingMatrix( float x, float y, float z );
	void LoadScalingMatrix( float Scale );
	void LoadScalingMatrix( Vec3f *pVector3 );
};

//A 3 by 3 Homogeneous Matrix
class CMatrix3
{
public:
	union //Can access matrix elements as, a 3 by 3 matrix, or a linear 9 entry array,
			// by individual element names
	{
		float m9[9];
		float m3x3[3][3];
		struct
		{
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		struct
		{
			Vec2f Row1_2x2; float _13;
			Vec2f Row2_2x2; float _23;
			Vec2f Trans; float _33;
		};
		struct
		{
			Vec3f Row1;
			Vec3f Row2;
			Vec3f Row3;
		};
	};

public:
	CMatrix3();

public:
	CMatrix3 operator+ ( CMatrix3& Matrix );
	CMatrix3 operator- ( CMatrix3& Matrix );
	CMatrix3 operator* ( CMatrix3& Matrix );
	CMatrix3 operator* ( float Factor );

	void ToInverse2D( CMatrix3& Matrix );		//Inverse for transformations
	CMatrix3 Inverse2D( void );					//Inverse for transformations
	CMatrix3 Inverse( float* pDeterminant );	//general Inverse
	CMatrix3 Transpose( void );

	void LoadIdentity( void );

	void LoadTranslationMatrix( float x, float y );
	void LoadTranslationMatrix( Vec2f* pVector3 );

	void LoadRotationMatrix3D( int PrimaryAxisID, float Angle );
							//PrimaryAxisID XAXIS, YAXIS, ZAXIS
	void LoadRotationMatrix3D( Vec3f *pDirection );
	void LoadRotationMatrix3D( float xDir, float yDir, float zDir );
							//Direction is pointer to a normalized vector

	void LoadRotationMatrix2D( float Angle );

	void LoadScalingMatrix3D( float x, float y, float z );
	void LoadScalingMatrix3D( float Scale );
	void LoadScalingMatrix3D( Vec3f *pVector3 );

	void LoadScalingMatrix2D( float x, float y );
	void LoadScalingMatrix2D( float Scale );
	void LoadScalingMatrix2D( Vec2f *pVector3 );
};
