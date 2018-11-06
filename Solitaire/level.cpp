

#include "Game.h"
#include "card.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"
#include <iostream>

#include "Level.h"

CGame& rGame = CGame::GetInstance();


CLevel::CLevel()
: card(0)
, background(0)
, width(0)
, height(0)
, m_iHalfDeckSizeX(121.0f / 2.0f)
, m_iHalfDeckSizeY(177.0f / 2.0f)
, cardGapY(45.0f)
, cardGapX(34.0f)
, cardPosition(8)
{
	srand(unsigned(time(NULL))); //Seed random shuffler
}

CLevel::~CLevel()
{
	delete card;
	card = 0;

	delete background;
	background = 0;

	while (vectorOfVectors.size()!=0)
	{
		vectorOfVectors.pop_back();
	}
}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
    width = _iWidth;
    height = _iHeight;

	//Background initialisation
	background = new CBackGround();
	VALIDATE(background->Initialise());

	//Set up pickup pile and shuffle the deck
	for (int i = 1; i <= 52; ++i)
	{
		card = new CCard();
		VALIDATE(card->Initialise((ESprite)(i)));
		card->SetX(45 + m_iHalfDeckSizeX);
		card->SetY(30 + m_iHalfDeckSizeY);
		pickupPileVector.push_back(card);
	}
	std::random_shuffle(pickupPileVector.begin(), pickupPileVector.end());


	//Deal cards to piles 1-7
	DealCards(1, pickupPileVector, boardOne);
	DealCards(2, pickupPileVector, boardTwo);
	DealCards(3, pickupPileVector, boardThree);
	DealCards(4, pickupPileVector, boardFour);
	DealCards(5, pickupPileVector, boardFive);
	DealCards(6, pickupPileVector, boardSix);
	DealCards(7, pickupPileVector, boardSeven);

	//Add all the vectors in the game into a vector of vectors
	vectorOfVectors.push_back(&pickupPileVector);
	vectorOfVectors.push_back(&discardPileVector);
	vectorOfVectors.push_back(&boardOne);
	vectorOfVectors.push_back(&boardTwo);
	vectorOfVectors.push_back(&boardThree);
	vectorOfVectors.push_back(&boardFour);
	vectorOfVectors.push_back(&boardFive);
	vectorOfVectors.push_back(&boardSix);
	vectorOfVectors.push_back(&boardSeven);
	vectorOfVectors.push_back(&spadesVector);
	vectorOfVectors.push_back(&heartsVector);
	vectorOfVectors.push_back(&clubsVector);
	vectorOfVectors.push_back(&diamondsVector);
	vectorOfVectors.push_back(&selectedPile);


	//When starting a new game, set the last cards of each board deck to be flipped open
	for (unsigned int i = 0; i < vectorOfVectors.size(); ++i)
	{
		if (i >= 2 && i <= 8)
		{
			vectorOfVectors[i]->back()->SetFaceUp(true);
		}
	}

	//Set the background position to start from {0,0}
	background->SetX((float)width / 2);
	background->SetY((float)height / 2);

	//FP initialisation
    return (true);
}

void
CLevel::Draw()
{
	background->Draw();

	//Draw all the decks of the game board to the screen
	DrawDecks();
}

void
CLevel::Process(float _fDeltaTick)
{
	background->Process(_fDeltaTick);
	CheckWin();
	ProcessDeck(_fDeltaTick);
}

void CLevel::HandleUserClick(float mX, float mY)
{
	EDeckType deckPos = EDeckType::NODECK;
	//m_iW = 121; //WIDTH OF CARD 
	//m_iH = 177; //HEIGHT OF CARD 

	//Card Positions

	//Draw Deck
	if (mY <= 207 && mY >= 30 && mX >=45 && mX <= 166){

		PlayerDrawsCard();
	}
	//DiscardDeck
	else if (mY <= 207 && mY >= 30 && mX >= 206 && mX <= 327){

		PlayerDiscardClick();
	}
	//spades
	else if (mX >= 528 && mX <= 705 && mY >= 30 && mY <= 206){

		SuitPickUp(spadesVector);
	}
	//hearts
	else if (mX >= 689 && mX <= 810 && mY >= 30 && mY <= 206){

		SuitPickUp(heartsVector);
	}
	//clubs
	else if (mX >= 850 && mX <= 971 && mY >= 30 && mY <= 206){

		SuitPickUp(clubsVector);
	}
	//Diamonds
	else if (mX >= 1011 && mX <= 1132 && mY >= 30 && mY <= 206){

		SuitPickUp(diamondsVector);
	}
	//Board 1
	else if (mX < 166 && mX >= 45 && mY >= 236){

		PlayerBoardRowClick(boardOne);
	}
	//Board 2
	else if (mX >= 206 && mX <= 327 && mY >= 236){

		PlayerBoardRowClick(boardTwo);
	}
	//Board 3
	else if (mX >= 367 && mX <= 488 && mY >= 236){

		PlayerBoardRowClick(boardThree);
	}
	//Board 4
	else if (mX >= 528 && mX <= 649 && mY >= 236){

		PlayerBoardRowClick(boardFour);
	}
	//Board 5
	else if (mX >= 689 && mX <= 810 && mY >= 236){

		PlayerBoardRowClick(boardFive);
	}
	//Board 6
	else if (mX >= 850 && mX <= 971 && mY >= 236){

		PlayerBoardRowClick(boardSix);
	}
	//Board 7
	else if (mX >= 1011 && mX <= 1132 && mY >= 236){

		PlayerBoardRowClick(boardSeven);
	}
}

void CLevel::HandleUserRelease(float mX, float mY)
{
	EDeckType deckPos = EDeckType::NODECK;
	
	if (mX >= 528 && mX <= 705 && mY >= 30 && mY <= 206) //SPADES
	{
		ReleaseToSuitDeck(ESuit::SPADES, spadesVector);
		return;
	}
	else if (mX >= 689 && mX <= 810 && mY >= 30 && mY <= 206) //HEARTS
	{
		ReleaseToSuitDeck(ESuit::HEARTS, heartsVector);
		return;
	}
	else if (mX >= 850 && mX <= 971 && mY >= 30 && mY <= 206) //CLUBS
	{
		ReleaseToSuitDeck(ESuit::CLUBS, clubsVector);
		return;
	}
	else if (mX >= 1011 && mX <= 1132 && mY >= 30 && mY <= 206) //DIAMONDS
	{
		ReleaseToSuitDeck(ESuit::DIAMONDS, diamondsVector);
		return;
	}
	else if (mX < 166 && mX >= 45 && mY >= 236)		//B1
	{
		ReleaseToDeck(boardOne);
		return;
	}
	else if (mX >= 206 && mX <= 327 && mY >= 236)	//B2
	{
		ReleaseToDeck(boardTwo);
		return;
	}
	else if (mX >= 367 && mX <= 488 && mY >= 236)	//B3
	{
		ReleaseToDeck(boardThree);
		return;
	}
	else if (mX >= 528 && mX <= 649 && mY >= 236)	//B4
	{
		ReleaseToDeck(boardFour);
		return;
	}
	else if (mX >= 689 && mX <= 810 && mY >= 236)	//B5
	{
		ReleaseToDeck(boardFive);
		return;
	}
	else if (mX >= 850 && mX <= 971 && mY >= 236)	//B6
	{
		ReleaseToDeck(boardSix);
		return;
	}
	else if (mX >= 1011 && mX <= 1132 && mY >= 236)	//B7
	{
		ReleaseToDeck(boardSeven);
		return;
	}

	//ELSE RETURN TO PREVIOUS DECK
	ReleaseToDeck(*previousPile);
}

void CLevel::PlayerBoardRowClick(std::vector<CCard*>& _pileToCheck)
{
	if (selectedPile.empty())
	{
		//Get the number of the card in the deck
		cardPosition = CheckCardRow(_pileToCheck); 

		if (!_pileToCheck.empty())
		{
			//Check if card is faceup - If it is, allow player to pick up cards
			if (_pileToCheck[cardPosition]->GetIsFaceUp()) 
			{
				//Checks through the pile and adds all the cards from the card the player picked into the player's pile
				for (unsigned int i = cardPosition; i < _pileToCheck.size(); ++i)	
				{
					selectedPile.push_back(_pileToCheck[i]);
				}
				int popSize = _pileToCheck.size() - cardPosition;
				//Erase all the cards collected from the pile
				for (int i = 0; i < popSize; ++i)	
				{
					_pileToCheck.pop_back();
				}
			}
			else
			{
				//If the card is the one on the front of the pile, allow user to flip card
				if (_pileToCheck[cardPosition] == _pileToCheck.back()) 
				{
					_pileToCheck[cardPosition]->SetFaceUp(true);
				}
			}
			//Set the previous deck the card was from
			previousPile = &_pileToCheck; 
		}
	}
	
}

int CLevel::CheckCardRow(std::vector<CCard*>& _pileToCheck)
{
	if (!_pileToCheck.empty())
	{
		//Draw from top of deck
		for (unsigned int i = 0; i < _pileToCheck.size(); ++i)	
		{
			if (CGame::m_MouseY >= _pileToCheck[i]->GetY() - m_iHalfDeckSizeY && CGame::m_MouseY <= _pileToCheck[i]->GetY() - m_iHalfDeckSizeY + 30)
			{
				return i;
			}
			//If last element
			else if (_pileToCheck[i] == _pileToCheck[_pileToCheck.size() - 1]) 
			{
				if (CGame::m_MouseY >= _pileToCheck[i]->GetY() - m_iHalfDeckSizeY  && CGame::m_MouseY <= _pileToCheck[i]->GetY() - m_iHalfDeckSizeY + 177)
				{
					return  i;
				}
			}
		}
	}
	return 0;
}



void CLevel::ReleaseCards(std::vector<CCard*>& _pileToReturn)
{
	for (unsigned int i = 0; i < selectedPile.size(); ++i)
	{
		_pileToReturn.push_back(selectedPile[i]);
	}

	while (selectedPile.size() != 0)
	{
		selectedPile.pop_back();
	}
}

void CLevel::ReleaseToSuitDeck(ESuit _suit, std::vector<CCard*>& _pileToReturn)
{
	if (!selectedPile.empty())
	{
		if (_pileToReturn.empty())
		{
			if (selectedPile.back()->GetCardSuit() == _suit  && 
			   (selectedPile.back()->GetCardType() == ESprite::SA ||
				selectedPile.back()->GetCardType() == ESprite::HA || 
				selectedPile.back()->GetCardType() == ESprite::CA || 
				selectedPile.back()->GetCardType() == ESprite::DA ))
			{
				_pileToReturn.push_back(selectedPile.back());
				selectedPile.pop_back();
			}
			else
			{
				ReleaseCards(*previousPile);
			}
		}
		else
		{
			if (selectedPile.size() == 1 && selectedPile.back()->GetCardSuit() == _suit && 
				(int)selectedPile.back()->GetCardType() == (int)_pileToReturn.back()->GetCardType() + 1)
			{
				_pileToReturn.push_back(selectedPile.back());
				selectedPile.pop_back();
			}
			else
			{
				ReleaseCards(*previousPile);
			}

		}
	}

}

void CLevel::ReleaseToDeck(std::vector<CCard*>& _pileToReturn)
{
	if (!selectedPile.empty())
	{
		if (_pileToReturn.empty())
		{
			//If board deck is empty, allow only KINGS to be released into the deck
			if (selectedPile.front()->GetCardType() == ESprite::SK ||
				selectedPile.front()->GetCardType() == ESprite::HK ||
				selectedPile.front()->GetCardType() == ESprite::CK ||
				selectedPile.front()->GetCardType() == ESprite::DK)
			{
				//Continue
				ReleaseCards(_pileToReturn);
			}
			else
			{
				ReleaseCards(*previousPile);
			}
		}
		else //If board deck ISNT empty
		{
			if (!_pileToReturn.back()->GetIsFaceUp())
			{
				ReleaseCards(*previousPile);
			}
			else
			{
				if (ReleaseIsValid(_pileToReturn))
				{
					ReleaseCards(_pileToReturn);
				}
				else
				{
					ReleaseCards(*previousPile);
				}
			}
		}
		
	}
}

bool CLevel::ReleaseIsValid(std::vector<CCard*>& _pileToReturn)
{
	if (!selectedPile.empty())
	{
		int sSpades = 0;
		int sHearts = 0;
		int sClubs = 0;
		int sDiamonds = 0;
		int playerSuit = (int)(selectedPile.front()->GetCardType());

		switch (_pileToReturn.back()->GetCardSuit())
		{
			case ESuit::SPADES:
			{
				sHearts = (int)(_pileToReturn.back()->GetCardType()) + 12;
				sDiamonds = (int)(_pileToReturn.back()->GetCardType()) + 38;
				if (playerSuit == sHearts || playerSuit == sDiamonds)
				{
					return true;
				}
				break;
			}
			case ESuit::HEARTS:
			{
				sSpades = (int)(_pileToReturn.back()->GetCardType()) - 14;
				sClubs = (int)(_pileToReturn.back()->GetCardType()) + 12;
				if (playerSuit == sSpades || playerSuit == sClubs)
				{
					return true;
				}
				break;
			}
			case ESuit::CLUBS:
			{
				sHearts = (int)(_pileToReturn.back()->GetCardType()) - 14;
				sDiamonds = (int)(_pileToReturn.back()->GetCardType()) + +12;
				if (playerSuit == sHearts || playerSuit == sDiamonds)
				{
					return true;
				}
				break;
			}
			case ESuit::DIAMONDS:
			{
				sSpades = (int)(_pileToReturn.back()->GetCardType()) - 40;
				sClubs = (int)(_pileToReturn.back()->GetCardType()) - 14;
				if (playerSuit == sSpades || playerSuit == sClubs)
				{
					return true;
				}
				break;

			}
		}
	}
	return false;
}

/*********
* DealCards: Deal Cards with a specified number from the pickup deck
**********/
void CLevel::DealCards(int _numCards, std::vector<CCard*>& _fromDeck, std::vector<CCard*>& _toDeck)
{
	unsigned int size = _fromDeck.size() - _numCards;		//Calculate number of cards to draw until
	for (unsigned int i = _fromDeck.size(); i > size; --i)	//Draw from top of deck
	{
		_toDeck.push_back(_fromDeck[i-1]);					//Add card fromDeck toDeck
		_fromDeck.pop_back();								//Remove the card from pickup pile
	}
}

/*********
* DrawDeck: Draws the specified deck of cards 
**********/
void CLevel::DrawDecks()
{
	int counter = 0;
	//Iterate through list of all vectors
	for (auto vec = vectorOfVectors.begin(); vec < vectorOfVectors.end(); ++vec)	
	{
		if (!(*vec)->empty())								//Only draw if deck isnt empty
		{
			if (counter == 0)								//PickUp Deck======================
			{
				(*vec)->back()->SetFaceUp(false);

				(*vec)->back()->SetX(45 + m_iHalfDeckSizeX);	//Set the new width of the card
				(*vec)->back()->SetY(30 + m_iHalfDeckSizeY);	//Set the new height of the card

				(*vec)->back()->Draw();							//Draw card onto screen
			}
			else if (counter == 1)							//Discard Deck=====================
			{
				(*vec)->back()->SetFaceUp(true);

				(*vec)->back()->SetX(206 + m_iHalfDeckSizeX);	//Set the new width of the card
				(*vec)->back()->SetY(30 + m_iHalfDeckSizeY);	//Set the new height of the card

				(*vec)->back()->Draw();							//Draw card onto screen
			}
			else if (counter == 2)							//B1 Deck=====================
			{
				it = (*vec)->begin();							//Start the iterator for each card in that deck
				while (it != (*vec)->end())						//If iterator has not reached the end of the vector
				{
					(*it)->SetX(45 + m_iHalfDeckSizeX);
					(*it)->SetY(235 + m_iHalfDeckSizeY);						//Set the new height of the card
					it++;										//Increase iterator
				}
			}
			else if (counter == 3)							//B2 Deck=====================
			{
				it = (*vec)->begin();							//Start the iterator for each card in that deck
				while (it != (*vec)->end())						//If iterator has not reached the end of the vector
				{
					(*it)->SetX(206 + m_iHalfDeckSizeX);
					(*it)->SetY(235 + m_iHalfDeckSizeY);
					it++;										//Increase iterator
				}
			}
			else if (counter == 4)							//B3 Deck=====================
			{
				it = (*vec)->begin();							//Start the iterator for each card in that deck
				while (it != (*vec)->end())						//If iterator has not reached the end of the vector
				{
					(*it)->SetX(367 + m_iHalfDeckSizeX);
					(*it)->SetY(235 + m_iHalfDeckSizeY);
					it++;										//Increase iterator
				}
			}
			else if (counter == 5)							//B4 Deck=====================
			{
				it = (*vec)->begin();							//Start the iterator for each card in that deck
				while (it != (*vec)->end())						//If iterator has not reached the end of the vector
				{
					(*it)->SetX(528 + m_iHalfDeckSizeX);
					(*it)->SetY(235 + m_iHalfDeckSizeY);
					it++;										//Increase iterator
				}
			}
			else if (counter == 6)							//B5 Deck=====================
			{
				it = (*vec)->begin();							//Start the iterator for each card in that deck
				while (it != (*vec)->end())						//If iterator has not reached the end of the vector
				{
					(*it)->SetX(689 + m_iHalfDeckSizeX);
					(*it)->SetY(235 + m_iHalfDeckSizeY);
					it++;										//Increase iterator
				}
			}
			else if (counter == 7)							//B6 Deck=====================
			{
				it = (*vec)->begin();							//Start the iterator for each card in that deck
				while (it != (*vec)->end())						//If iterator has not reached the end of the vector
				{
					(*it)->SetX(850 + m_iHalfDeckSizeX);
					(*it)->SetY(235 + m_iHalfDeckSizeY);
					it++;										//Increase iterator
				}
			}
			else if (counter == 8)							//B7 Deck=====================
			{
				it = (*vec)->begin();							//Start the iterator for each card in that deck
				while (it != (*vec)->end())						//If iterator has not reached the end of the vector
				{
					(*it)->SetX(1011 + m_iHalfDeckSizeX);
					(*it)->SetY(235 + m_iHalfDeckSizeY);
					it++;										//Increase iterator
				}
			}
			else if(counter == 9)							//Spade Deck=====================
			{
				(*vec)->back()->SetFaceUp(true);

				(*vec)->back()->SetX(528 + m_iHalfDeckSizeX);	//Set the new width of the card
				(*vec)->back()->SetY(30 + m_iHalfDeckSizeY);	//Set the new height of the card

				(*vec)->back()->Draw();							//Draw card onto screen
			}
			else if (counter == 10)							//Heart Deck=====================
			{
				(*vec)->back()->SetFaceUp(true);

				(*vec)->back()->SetX(689 + m_iHalfDeckSizeX);	//Set the new width of the card
				(*vec)->back()->SetY(30 + m_iHalfDeckSizeY);	//Set the new height of the card

				(*vec)->back()->Draw();							//Draw card onto screen
			}
			else if (counter == 11)							//Club Deck=====================
			{
				(*vec)->back()->SetFaceUp(true);

				(*vec)->back()->SetX(850 + m_iHalfDeckSizeX);	//Set the new width of the card
				(*vec)->back()->SetY(30 + m_iHalfDeckSizeY);	//Set the new height of the card

				(*vec)->back()->Draw();							//Draw card onto screen
			}
			else if (counter == 12)							//Diamond Deck=====================
			{
				(*vec)->back()->SetFaceUp(true);

				(*vec)->back()->SetX(1011 + m_iHalfDeckSizeX);	//Set the new width of the card
				(*vec)->back()->SetY(30 + m_iHalfDeckSizeY);	//Set the new height of the card

				(*vec)->back()->Draw();							//Draw card onto screen
			}
			else if (counter == 13)
			{
				(*vec)->front()->SetX(static_cast<float>(CGame::m_MouseX));
				(*vec)->front()->SetY(static_cast<float>(CGame::m_MouseY));

				it = (*vec)->begin();							//Start the iterator for each card in that deck
				float height = (*vec)->front()->GetY();			//Get the current height of the cards
				while (it != (*vec)->end())						//If iterator has not reached the end of the vector
				{
					(*it)->SetX((*vec)->front()->GetX());						//Set the new height of the card
					(*it)->SetY(height);						//Set the new height of the card
					height += 30.0f;							//Give a 30px gap height between cards
					(*it)->Draw();								//Draw card onto screen
					it++;										//Increase iterator
				}
			}


			if (counter >= 2 && counter <= 8)			//Board Decks=====================
			{
				it = (*vec)->begin();							//Start the iterator for each card in that deck
				float height = (*vec)->front()->GetY();			//Get the current height of the cards
				while (it != (*vec)->end())						//If iterator has not reached the end of the vector
				{
					(*it)->SetY(height);						//Set the new height of the card
					height += 30.0f;							//Give a 30px gap height between cards
					(*it)->Draw();								//Draw card onto screen
					it++;										//Increase iterator
				}
			}
		}
		++counter;
	}
}

/*********
* ProcessDeck: Processes the specified deck of cards
**********/
void CLevel::ProcessDeck(float _fDeltaTick)
{
	//Iterate through list of all vectors
	for (auto vec = vectorOfVectors.begin(); vec < vectorOfVectors.end(); ++vec)	
	{
		it = (*vec)->begin();						//Start the iterator for each card in that deck
		if (!(*vec)->empty())
		{
			while (it != (*vec)->end())					//If iterator has not reached the end of the vector
			{
				(*it)->Process(_fDeltaTick);			//Set the new height of the card
				it++;									//Increase iterator
			}
		}
	}
}

//Drawing a card from the main deck
void CLevel::PlayerDrawsCard()
{
	if (!pickupPileVector.empty())
	{
		//draws 3 cards at a time
		if (rGame.draw3 == 1) {
			for (int a = 0; a < 3; a++) {
				//checks to see if the pickupPileVector is empty if so breaks out of drawing the cards
				if (pickupPileVector.empty()) {
					break;
				}
				discardPileVector.push_back(pickupPileVector.back());
				pickupPileVector.back()->SetX(206 + m_iHalfDeckSizeX);	//Set the new width of the card
				pickupPileVector.back()->SetY(30 + m_iHalfDeckSizeY);	//Set the new width of the card
				pickupPileVector.pop_back();
			}
		}
		//draws one card at a time
		else {
			discardPileVector.push_back(pickupPileVector.back());
			pickupPileVector.back()->SetX(206 + m_iHalfDeckSizeX);	//Set the new width of the card
			pickupPileVector.back()->SetY(30 + m_iHalfDeckSizeY);	//Set the new width of the card
			pickupPileVector.pop_back();
		}
	}
	else
	{
		while (discardPileVector.size() != 0)
		{
				discardPileVector.front()->SetFaceUp(false);
				pickupPileVector.push_back(discardPileVector.front());
				discardPileVector.front() = std::move(discardPileVector.back());
				discardPileVector.pop_back();
			}
		}

		if (!pickupPileVector.empty())
		{
			it = pickupPileVector.begin();	
			while (it != pickupPileVector.end())
			{
				(*it)->SetX(45 + m_iHalfDeckSizeX);
				(*it)->SetY(30 + m_iHalfDeckSizeY);
				it++;
			}
		}
	}

void CLevel::PlayerDiscardClick()
{
	if (!discardPileVector.empty())
	{
		selectedPile.push_back(discardPileVector.back());
		discardPileVector.pop_back();
		previousPile = &discardPileVector;
	}
}

void CLevel::SuitPickUp(std::vector<CCard*>& _pileToReturn)
{
	if (!_pileToReturn.empty())
	{
		selectedPile.push_back(_pileToReturn.back());
		_pileToReturn.pop_back();
		previousPile = &_pileToReturn;
	}
}

void CLevel::CheckWin()
{
	if (!spadesVector.empty() && !heartsVector.empty()
		&& !clubsVector.empty() && !diamondsVector.empty())
	{
		if(spadesVector.size() == 13 &&
			heartsVector.size() == 13 &&
			clubsVector.size() == 13 &&
			diamondsVector.size() == 13)
		{
			CGame::GetInstance().GameOverWon();
		}
	}
}