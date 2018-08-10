#ifndef FACE_H
#define FACE_H

class Face
{
public:

	//Constructors/Destructors
	Face();
	~Face();

	//Variables to be filled by the obj file
	int v0_, v1_, v2_;
	int vt0_, vt1_, vt2_;
	int vn0_, vn1_, vn2_;
};

#endif

