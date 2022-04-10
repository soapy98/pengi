#pragma once 

#include <math.h>

//constants
const double PI = 22.0f/7.0;
const double RadToDeg = 180.0/PI;
const double DegToRad = PI/180.0;
const float  EPSILON = 0.01f;
const double EPSILONd = 0.01;
const double MATCH_FACTOR = 0.99;

//Math globals
class MathGlobals
{
public:
	static float	Absolute( float num );
	static double	Absolute( double num );
	static bool		bFloatsEqual( float A, float B );
	static bool		bDoublesEqual( double A, double B );
};

