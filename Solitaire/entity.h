

#pragma once

#if !defined(__ENTITY_H__)
#define __ENTITY_H__

// Local Includes
#include "EEnums.h"

// Prototypes
class CSprite;

class CEntity
{
public:
	CEntity();
	virtual ~CEntity();

	virtual bool Initialise();
	virtual bool Initialise(ESprite enemyType);

	virtual void Draw() = 0;
	virtual void Process(float _fDeltaTick);

	void SetX(float _f);
	void SetY(float _f);

	float GetX() const;
	float GetY() const;

	void SetHeight(float _f);
	void SetWidth(float _f);

	float GetHeight() const;
	float GetWidth() const;

	ESprite GetCardType();
	void FlipOpenCard(bool _open, CEntity& e);
	bool IsCollidingWith(CEntity& e);

protected:
	CSprite* m_pSprite;
	CSprite* m_pSpriteBack;
	CSprite* m_pSpriteFront;
	ESprite m_eSpriteType;

	float m_fX;
	float m_fY;
	float m_fWidth;
	float m_fHeight;

private:
	CEntity(const CEntity& _kr);
	CEntity& operator= (const CEntity& _kr);

};


#endif // __ENTITY_H__
