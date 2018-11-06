

#pragma once

#if !defined(__CARD_H__)
#define __CARD_H__

// Library Includes
#include <ctime>

// Local Includes
#include "entity.h"
#include "sprite.h"

class CCard : public CEntity
{
	// Member Variables
public:
	CCard();
	virtual ~CCard();

	virtual bool Initialise(ESprite _spriteType);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void SetFaceUp(bool _b);
	bool GetIsFaceUp() const;

	bool GetIsRedSuit();

	ESuit GetCardSuit();
protected:

	ESprite m_eSpriteType;
	ESuit m_eCardSuit;
	bool m_bFacingUp;

	//Deck holding this card
	EDeckType m_eDeckType;
	EBDeck m_eBoardDeckType;

private:
	CCard(const CCard& _kr);
	CCard& operator= (const CCard& _kr);
};


#endif    // __CARD_H__

