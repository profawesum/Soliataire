
#pragma once
#if !defined(__EENUMS_H__)
#define __EENUMS_H__

enum class ESprite //S->H->C->D [suit hierarchy of poker]
{
	SA = 1, S2, S3, S4, S5, S6, S7, S8, S9, S10, SJ, SQ, SK,	//SPADES	//1-13
	HA, H2, H3, H4, H5, H6, H7, H8, H9, H10, HJ, HQ, HK,		//HEARTS	//14-26
	CA, C2, C3, C4, C5, C6, C7, C8, C9, C10, CJ, CQ, CK,		//CLUBS		//27-39
	DA, D2, D3, D4, D5, D6, D7, D8, D9, D10, DJ, DQ, DK,		//DIAMONDS	//40-52
	BACKGROUND, CARDBACK, NONE
};

enum class EDeckType
{
	NODECK,
	B1 = 1,			//Far left board deck
	B2,
	B3,
	B4,
	B5,
	B6,
	B7,
	S1,		//4 Piles at the top of the screen
	S2,
	S3,
	S4,
	PICKUPDECK,		//Pile of cards to pick up from. 24 cards
	DISCARDDECK,	//A pile of discarded cards next to the pickup deck
	PLAYERHOLDDECK	//An invisible deck that will pick up cards when the player selects a pile
};

enum class ESuit
{
	SPADES,
	HEARTS,
	CLUBS,
	DIAMONDS,
	MULTI
};

enum class EBDeck //Board decks from left to right
{
	NOTBOARD, //Not a board deck
	B1 = 1, //Far left board deck
	B2,
	B3,
	B4,
	B5,
	B6,
	B7, //Far right board deck
};

#endif    // __EENUMS_H__
