#include "vectors.h"
#include "Matrices.h"

//Members Vec2f
Vec2f::Vec2f()
{
	x = 0;
	y = 0;
}

Vec2f::Vec2f( float X, float Y )
{
	x = X; y = Y;
}

Vec2f Vec2f::operator+ ( Vec2f& v )
{
	return Vec2f( x+v.x, y+v.y );
}

Vec2f Vec2f::operator- ( Vec2f& v )
{
	return Vec2f( x-v.x, y-v.y );
}

Vec2f Vec2f::operator* ( Vec2f& v )
{
	return Vec2f( x*v.x, y*v.y );
}

Vec2f Vec2f::operator* ( float u )
{
	return Vec2f( x*u, y*u );
}

void Vec2f::operator+= ( Vec2f& v )
{
	x += v.x; y += v.y;
}

void Vec2f::operator-= ( Vec2f& v )
{
	x -= v.x; y -= v.y;
}

float Vec2f::Dot( Vec2f& v )
{
	return ( x*v.x + y*v.y );
}

float Vec2f::Length( void )
{
	return ::sqrtf( x*x + y*y  );
}

float Vec2f::LengthSqr( void )
{
	return (x*x + y*y);
}

Vec2f Vec2f::Normalize( void )
{
	float Mag = ::sqrtf( x*x + y*y );

	if( Mag == 0 ) return Vec2f(0,0);

	return Vec2f( x/Mag, y/Mag );
}

double Vec2f::AngleBwVectors( Vec2f& Vec )
{
	float dotProduct = this->Dot(Vec);

	float vectorsMagnitude = this->Length() * Vec.Length();

	double angle = ::acos( dotProduct / vectorsMagnitude );

	if(_isnan(angle))
		return 0.0;
	
	return( angle );
}

//Members Vec3f
Vec3f::Vec3f()
{
	x = 0, y = 0, z =0;
}

Vec3f::Vec3f( float X, float Y, float Z )
{
	x = X; y = Y; z = Z;
}

Vec3f Vec3f::operator+ ( Vec3f& v )
{
	return Vec3f( x+v.x, y+v.y, z+v.z );
}

Vec3f Vec3f::operator- ( Vec3f& v )
{
	return Vec3f( x-v.x, y-v.y, z-v.z );
}

Vec3f Vec3f::operator* ( Vec3f& v )
{
	return Vec3f( x*v.x, y*v.y, z*v.z );
}

Vec3f Vec3f::operator* ( float u )
{
	return Vec3f( x*u, y*u, z*u );
}

Vec3f Vec3f::operator* ( CMatrix4& Matrix )
{
	float w = x*Matrix._14 + y*Matrix._24 + z*Matrix._34 + Matrix._44;
	return Vec3f( (x*Matrix._11 + y*Matrix._21 + z*Matrix._31 + Matrix._41)/w,
					(x*Matrix._12 + y*Matrix._22 + z*Matrix._32 + Matrix._42)/w,
					  (x*Matrix._13 + y*Matrix._23 + z*Matrix._33 + Matrix._43)/w );
}

void Vec3f::operator+= ( Vec3f& v )
{
	x += v.x; y += v.y; z += v.z;
}

void Vec3f::operator-= ( Vec3f& v )
{
	x -= v.x; y -= v.y; z -= v.z;
}

bool Vec3f::operator== ( Vec3f& v )
{
	if( MathGlobals::bFloatsEqual(v.x, x) &&
			MathGlobals::bFloatsEqual(v.y, y) &&
				MathGlobals::bFloatsEqual(v.z, z) )
		return true;

	return false;
}

float Vec3f::Dot( Vec3f& v )
{
	return ( x*v.x + y*v.y + z*v.z );
}

Vec3f Vec3f::Cross( Vec3f& v )
{
	return Vec3f( (y*v.z - z*v.y), (z*v.x - x*v.z), (x*v.y - y*v.x) );
}

float Vec3f::Length( void )
{
	return ::sqrtf( x*x + y*y + z*z );
}

float Vec3f::LengthSqr( void )
{
	return (x*x + y*y + z*z);
}

Vec3f Vec3f::Normalize( void )
{
	float Mag = ::sqrtf( x*x + y*y + z*z );

	if( Mag == 0 ) return Vec3f(0,0,0);

	return Vec3f( x/Mag, y/Mag, z/Mag );
}

int Vec3f::normalize( void )
{
	float len = this->Dot( *this );
	if( len < 0.000000000001f )
		return 1;

	len = 1.0f / ( ::sqrtf(len) );

    x *= len;
    y *= len;
    z *= len;

	return 0;
}

double Vec3f::AngleBwVectors( Vec3f& Vec )
{
	float dotProduct = this->Dot(Vec);

	float vectorsMagnitude = this->Length() * Vec.Length();

	double angle = ::acos( dotProduct / vectorsMagnitude );

	if(_isnan(angle))
		return 0.0;
	
	return( angle );
}

Vec3f Vec3f::RotateOnAxis( Vec3f &axis, float angle )
{
	Vec3f nv;
//	axis = axis.Normalize();
	float theta = float((-angle / 180.0f) * PI);

	float	cosTheta = (float)cos( theta ),
			sinTheta = (float)sin( theta ),
			dot = this->Dot( axis );
		
	Vec3f cross = axis.Cross( *this );
			
	nv.x = cosTheta*(x - dot*axis.x)
				+ sinTheta*cross.x
					+ dot*axis.x;

	nv.y = cosTheta*(y - dot*axis.y)
				+ sinTheta*cross.y
					+ dot*axis.y;

	nv.z = cosTheta*(z - dot*axis.z)
				+ sinTheta*cross.z
					+ dot*axis.z;

	return nv;
}

bool Vec3f::InsideTriangle( Vec3f& V1, Vec3f& V2, Vec3f& V3 )
{
	double Angle = MathGlobals::Absolute((V2-(*this)).AngleBwVectors(V1-(*this)));
	Angle += MathGlobals::Absolute((V3-(*this)).AngleBwVectors(V2-(*this)));
	Angle += MathGlobals::Absolute((V1-(*this)).AngleBwVectors(V3-(*this)));

	if( Angle >= 2*PI*MATCH_FACTOR ) return true;

	return false;
}

//Member functions : Vec4f
Vec4f::Vec4f()
{
	x = 0.0; y = 0.0; z = 0.0; w = 1.0;
}

Vec4f::Vec4f( float X, float Y, float Z, float W )
{
	x = X; y = Y; z = Z; w = W;
}

Vec4f::Vec4f( Vec3f v3f, float W )
{
	x = v3f.x;
	y = v3f.y;
	z = v3f.z;
	w = W;
}

Vec4f Vec4f::operator+ ( Vec4f& v )
{
	return Vec4f( x+v.x, y+v.y, z+v.z, w+v.w );
}

Vec4f Vec4f::operator- ( Vec4f& v )
{
	return Vec4f( x-v.x, y-v.y, z-v.z, w-v.w );
}

Vec4f Vec4f::operator* ( Vec4f& v )
{
	return Vec4f( x*v.x, y*v.y, z*v.z, w*v.w );
}

Vec4f Vec4f::operator* ( float u )
{
	return Vec4f( x*u, y*u, z*u, w*u );
}

float Vec4f::Dot( Vec4f& v )
{
	return (x*v.x + y*v.y + z*v.z + w*v.w);
}

Vec4f Vec4f::Normalize( void )
{
	float Mag = ::sqrtf( x*x + y*y + z*z + w*w );

	if( Mag == 0 ) return Vec4f(0,0,0,0);

	return Vec4f( x/Mag, y/Mag, z/Mag, z/Mag );
}

//
