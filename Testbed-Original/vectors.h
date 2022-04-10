#pragma once 

#include <float.h>
#include "MathGlobals.h"

class CMatrix4;

//A 2D float Vector
class Vec2f
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		struct
		{
			float s, t;
		};
	};

public:
	Vec2f();
	Vec2f( float X, float Y );

public:
	Vec2f operator+ ( Vec2f& v );
	Vec2f operator- ( Vec2f& v );
	Vec2f operator* ( Vec2f& v );
	Vec2f operator* ( float u );

	void operator+= ( Vec2f& v );
	void operator-= ( Vec2f& v );

	float Dot( Vec2f& v );

	float Length( void );
	float LengthSqr( void );
	Vec2f Normalize( void );

	double AngleBwVectors( Vec2f& Vec );
};

//A 3D float Vector
class Vec3f
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		struct
		{
			float r, g, b;
		};
		struct
		{
			float s, t, r;
		};
	};

public:
	Vec3f();
	Vec3f( float X, float Y, float Z );

public:
	Vec3f operator+ ( Vec3f& v );
	Vec3f operator- ( Vec3f& v );
	Vec3f operator* ( Vec3f& v );
	Vec3f operator* ( float u );

	Vec3f operator* ( CMatrix4& Matrix );

	void operator+= ( Vec3f& v );
	void operator-= ( Vec3f& v );

	bool operator== ( Vec3f& v );

	float Dot( Vec3f& v );
	Vec3f Cross( Vec3f& v );

	float Length( void );
	float LengthSqr( void );	
	Vec3f Normalize( void );
	int   normalize( void );

	double AngleBwVectors( Vec3f& Vec );
	Vec3f  RotateOnAxis( Vec3f &axis, float angle );
	bool InsideTriangle( Vec3f& V1, Vec3f& V2, Vec3f& V3 ); //V1, V2, V3 coplanar to this
};

typedef Vec3f Color3f;

class Vec4f
{
public:
	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
		struct
		{
			Vec3f Vec3;
			float w;
		};
	};

public:
	Vec4f();
	Vec4f( float X, float Y, float Z, float W );
	Vec4f( Vec3f v3f, float W );

public:
	Vec4f operator+ ( Vec4f& v );
	Vec4f operator- ( Vec4f& v );
	Vec4f operator* ( Vec4f& v );
	Vec4f operator* ( float u );

	float Dot( Vec4f& v );
	Vec4f Normalize( void );
};

typedef Vec4f Color4f;

