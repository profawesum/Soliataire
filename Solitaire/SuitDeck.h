

#pragma once
#include "deck.h"
class CSuitDeck : public CDeck
{
public:
	CSuitDeck(EDeckType _deckType, ESuit _suit);
	virtual ~CSuitDeck();

	ESuit GetSuit();
	bool CanCardBeAdded(CCard& _cardToCheck);
	bool IsComplete();

protected:

private:
	ESuit m_eDeckSuit;
};

