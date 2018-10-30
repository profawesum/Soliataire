#pragma once
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



class Card {

public:


	float suit;
	float value;

	int cardArray[4][13];



	void cCard();
	virtual ~Card();

	void setCard();
	float getSuit();
	//void setValue();
	float getValue();




};