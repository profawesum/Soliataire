//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Harrison Orsbourne and co.
// Mail			: your.name@mediadesign.school.nz
//


#pragma once



#include <windows.h>

class Sprite {


public:

	bool initialise();
	void draw();



private:

	HBITMAP m_hSprite;

};
