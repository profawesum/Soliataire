
#include "utils.h"


#include "card.h"

CCard::CCard()
: m_bFacingUp(false)
//, m_fCollisionBoundaryX(0)
//, m_fCollisionBoundaryY(0)
{
}

CCard::~CCard()
{
	
}

/*********
* Initialise: Initialises the card
* @parameter _spriteType - type of card to declare 
			(determine by Enum ESprites which are also used by 
			the spriteclass to distinguish between cards.)
* @return: true
**********/
bool
CCard::Initialise(ESprite _spriteType)
{
	m_eSpriteType = _spriteType;
    VALIDATE(CEntity::Initialise(_spriteType));

	//Assign suit types for each card
	if ((int)m_eSpriteType >= 1 && (int)m_eSpriteType <= 13)
	{
		m_eCardSuit = ESuit::SPADES;
	}
	else if ((int)m_eSpriteType >= 12 && ((int)m_eSpriteType <= 26))
	{
		m_eCardSuit = ESuit::HEARTS;
	}
	else if ((int)m_eSpriteType >= 27 && ((int)m_eSpriteType <= 39))
	{
		m_eCardSuit = ESuit::CLUBS;
	}
	else if ((int)m_eSpriteType >= 40 && ((int)m_eSpriteType <= 52))
	{
		m_eCardSuit = ESuit::DIAMONDS;
	}

    return (true);
}

/*********
* Draw: Draws a card if called
**********/
void
CCard::Draw()
{
     CEntity::Draw();
}

/*********
* Process: Processes any card activity that occurs
**********/
void
CCard::Process(float _fDeltaTick)
{
    CEntity::Process(_fDeltaTick);
}

/*********
* SetHidden: Sets the card to either it's back or face
* @parameter: _b - true for back, false for face
**********/
void
CCard::SetFaceUp(bool _b)
{
	FlipOpenCard(_b, *this);
	m_bFacingUp = _b;
}

/*********
* IsHidden: Getter to check whether card is hidden or not
* @return: m_bHidden - wether the card is hidden or not
**********/
bool
CCard::GetIsFaceUp() const
{
    return (m_bFacingUp);
}

bool CCard::GetIsRedSuit()
{
	if (GetCardSuit() == ESuit::DIAMONDS || GetCardSuit() == ESuit::HEARTS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*********
* GetCardSuit: Gets the suit of the card
* @return: m_eCardSuit - the suit
**********/
ESuit CCard::GetCardSuit()
{
	return m_eCardSuit;
}
