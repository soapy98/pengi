#include "MathGlobals.h"

float MathGlobals::Absolute( float num )
{
	if(num < 0.0f)
		return (0.0f - num);

	return num;
}

double MathGlobals::Absolute( double num )
{
	if(num < 0.0)
		return (0.0 - num);

	return num;
}

bool MathGlobals::bFloatsEqual( float A, float B )
{
	if( ::fabsf(A-B) < EPSILON ) return true;

	return false;
}

bool MathGlobals::bDoublesEqual( double A, double B )
{
	if( ::fabs(A-B) < EPSILONd ) return true;

	return false;
}

//
