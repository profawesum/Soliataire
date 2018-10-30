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
#include <stack>

class Game {


public:

	virtual ~Game();
	void cGame();



	//used for the stacks at the top of the game
	void aceStack();

	//used for the 7 rows, stacking the cards
	void stack();

	//used for the deck of cards remaining
	void deck();

	//The cards from the deck that you can use
	void usableCardFromDeck();

	void initialise();




private:

	//stacks for the ace stacks
	std::stack<int> s_AceStack;
	std::stack<int> s_AceStack2;
	std::stack<int> s_AceStack3;
	std::stack<int> s_AceStack4;

	//stacks for the main rows
	std::stack<int> s_7Stack;
	std::stack<int> s_7Stack2;
	std::stack<int> s_7Stack3;
	std::stack<int> s_7Stack4;
	std::stack<int> s_7Stack5;
	std::stack<int> s_7Stack6;
	std::stack<int> s_7Stack7;

	//stacks for the deck and the usable card
	std::stack<int> s_Deck;
	std::stack<int> s_UsableCard;

};