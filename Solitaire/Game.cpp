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

#include "Game.h"
#include "Card.h"
#include <stack>

Game *game;
Card *card;
int gamemode;


//destructor
Game::~Game(){

	 
}

//constructor
void Game::cGame(){


}

//used for the stacks at the top of the game
void Game::aceStack(){


		//checking the suit of the card that is wanting to be placed
		if (s_AceStack.top() == card->getSuit()) {
			if (card->getValue() > s_AceStack.top()) {
				
			}
		}
		
		
		if (s_AceStack2.top() == card->getSuit()) {
			if (s_AceStack2.top()) {

			}
		}
		
		
		if (s_AceStack3.top() == card->getSuit()) {
			if (s_AceStack3.top()) {

			}
		}
		
		
		if (s_AceStack4.top() == card->getSuit()) {
			if (s_AceStack4.top()) {

			}
		}

	//check to see if the the cards are the same suit
	//check to see if the value is 1 greater than what is already there

}

//used for the 7 rows, stacking the cards
void Game::stack(){



	//checks to see if the move is a legal move
	if (card->getSuit() == 1 || card->getSuit() == 3) {



	}
	if (card->getSuit() == 2 || card->getSuit() == 4) {



	}

	//make sure that each stack knows what is below it
	//if the player moves something then call this function
	//if there is an empty space then flip over the card with the empty space after the player has made a legal move



}

void Game::deck(){




	//use a stack to see what is the top card of the deck, when drawing
}


void Game::usableCardFromDeck(){


	//draw 1 card mode
	if (gamemode == 1) {
	
		if (s_Deck.size() != NULL) {
			//sets the float data to the top card of the deck
			float data = s_Deck.top();
			//makes the top card of the usable card stack to the value of data
			s_UsableCard.push(data);
			//removes the top card of the deck
			s_Deck.pop();


			//TODO: move the bitmap to the right place
			
		}
	
	}
	//draw 3 card mode
	else {

		if (s_Deck.size() != NULL) {

			for (int a = 0; a < 3; a++) {
					
				float data = s_Deck.top();
				s_UsableCard.push(data);
				s_Deck.pop();


				//TODO: place the bitmaps to the right place
		
			}
		}
	}

	//inversing the stack once the deck has run out
	if (s_Deck.size() == NULL) {
		//keep going until the usable card stack has emptied
		while (s_UsableCard.size() != NULL) {

			float data = s_UsableCard.top();
			s_Deck.push(data);
			s_UsableCard.pop();


			//TODO: return the bitmaps to the original deck place
		
		}
	}
}
