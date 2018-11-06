
#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__


#include <algorithm>
#include <string>
#include <vector>
#include <ctime>

#include "card.h"

class CFPSCounter;
class CBackGround;

class CLevel
{
public:
    CLevel();
    virtual ~CLevel();

    virtual bool Initialise(int _iWidth, int _iHeight);
    virtual void Draw();
    virtual void Process(float _fDeltaTick);

	void DrawDecks();
	void ProcessDeck(float _fDeltaTick);

	void PlayerDrawsCard();
	void PlayerDiscardClick();
	void SuitPickUp(std::vector<CCard*>& _pileToReturn);

	void CheckWin();

	void ReleaseCards(std::vector<CCard*>& _pileToReturn);
	void ReleaseToSuitDeck(ESuit _suit, std::vector<CCard*>& _pileToReturn);
	void ReleaseToDeck(std::vector<CCard*>& _pileToReturn);
	bool ReleaseIsValid(std::vector<CCard*>& _pileToReturn);
	void HandleUserClick(float _x, float _y);
	void HandleUserRelease(float _x, float _y);

	void PlayerBoardRowClick(std::vector<CCard*>& _pileToCheck);
	int CheckCardRow(std::vector<CCard*>& _pileToCheck);

	//Used when setting up the game
	void DealCards(int _numCards, std::vector<CCard*>& _fromDeck, std::vector<CCard*>& _toDeck);


protected:	


	std::vector<CCard*>::const_iterator it; //Iterator for vectors


	std::vector<std::vector<CCard*>*>::const_iterator vectIt; //Vector Iterator for vectors

	//stores all the vectors
	std::vector<std::vector<CCard*>*> vectorOfVectors;
	//points to the last pile that card was picked from
	std::vector<CCard*>* previousPile;


	//card pointer
	CCard* card;
	//background pointer
	CBackGround* background;

	//Cards the player has selected
	std::vector<CCard*> selectedPile;

	//Draw Pile
	std::vector<CCard*> pickupPileVector;
	//Discard Pile, The Pile Next To The Draw pile
	std::vector<CCard*> discardPileVector;

	//Ace - King Piles for each suit
	std::vector<CCard*> spadesVector;	
	std::vector<CCard*> heartsVector;
	std::vector<CCard*> clubsVector;
	std::vector<CCard*> diamondsVector;

	//The 7 Stacks that the cards reveal from
	std::vector<CCard*>  boardOne;			
	std::vector<CCard*>  boardTwo;
	std::vector<CCard*>  boardThree;
	std::vector<CCard*>  boardFour;
	std::vector<CCard*>  boardFive;
	std::vector<CCard*>  boardSix;
	std::vector<CCard*>  boardSeven;

	std::string mouseX;
	std::string mouseY;
	std::string temp;

	int width;
	int height;
	bool m_bClicking;

	std::string cPos;
	int cardPosition;

	float cardGapY;
	float cardGapX;
	const float m_iHalfDeckSizeX;
	const float m_iHalfDeckSizeY;

private:
    CLevel(const CLevel& _kr);
    CLevel& operator= (const CLevel& _kr);

};

#endif    // __LEVEL_H__
