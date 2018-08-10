#ifndef FUNCS_H
#define FUNCS_H

#include <string>
#include <vector>

class Funcs
{
public:

	//Linear interpolation function
	static float lerp(float s, float e, float t)
	{ 
		return s + (e - s)*t;
	}

	//Bilinear interpolation function
	static float blerp(float c00, float c10, float c01, float c11, float tx, float ty) 
	{
		return lerp(lerp(c00, c10, tx), lerp(c01, c11, tx), ty);
	}

private:

	//Constructors/Destructors not to be used,
	//class is for misc static functions only
	Funcs();
	~Funcs();
};

#endif