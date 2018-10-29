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
// Author		: Harrison Orsbourne and co. and vaughan 
// Mail			: your.name@mediadesign.school.nz
//


#include "resource.h"
#include "Card.h"




//constructor - Harry
void Card::cCard(){


}



//Destructor - Harry
Card::~Card(){


}



//call this each time there is a new game - Harry
void Card::setSuit(){

	//Suit 1 = Spades
	//Suit 2 = Clubs
	//Suit 3 = Hearts
	//Suit 4 = Diamonds

	//Set the suit of the cards at the start of the game
	for (int a = 0; a < 4; a++) {
		for (int b = 0; b < 13; b++) {
			//Insert stuff to select suit for each 13 cards
		}
		suit++;
	}
}



//call this each time there is a new game -Harry
void Card::setValue() {
	//set the value of the cards at the start of the game
	for (int a = 0; a < 4; a++) {
		for (int b = 0; b < 13; b++) {
			//Set the value of each card
			//Jack is 11, Queen is 12 and King is 13
			value++;
		}
		//resets it for the next suit
		if (value == 13) {
			value = 1;
		}
	}


}

//use this when you need to get a suit from a card
float Card::getSuit(){

	return suit;

}


//use this when you need to get a value from a card
float Card::getValue(){


	return value;
}

