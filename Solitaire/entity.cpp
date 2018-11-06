


#include "resource.h"
#include "Sprite.h"
#include "utils.h"

#include "entity.h"

CEntity::CEntity()
: m_fX(0.0f)
, m_fY(0.0f)
, m_fWidth(121.0f)
, m_fHeight(177.0f)

{

}

CEntity::~CEntity()
{
    delete m_pSprite;
    m_pSprite = 0;
}

/********************
* CEntity Initialiser: Initialises entity with specified sprite,
* @parameter: _spriteType - Sprite to be initialised with entity
* @return bool
*********************/
bool CEntity::Initialise()
{
    return (true);
}

/********************
* CEntity Initialiser: Initialises entity with specified sprite,
* @parameter: _spriteType - Sprite to be initialised with entity
* @return bool
*********************/
bool CEntity::Initialise(ESprite _eType)
{
	m_pSpriteFront = new CSprite(_eType);
	m_pSprite = m_pSpriteFront;

	m_eSpriteType = _eType;
	VALIDATE(m_pSpriteFront->Initialise());
	if (_eType != ESprite::BACKGROUND && _eType != ESprite::NONE)
	{
		m_pSpriteBack = new CSprite(ESprite::CARDBACK);
		VALIDATE(m_pSpriteBack->Initialise());
		m_pSprite = m_pSpriteBack;
	}

	return (true);
}

void CEntity::Draw()
{
	m_pSprite->Draw();
}

/************
* Process: Calls the sprite's process function
*************/
void
CEntity::Process(float _fDeltaTick)
{
    m_pSprite->SetX(static_cast<int>(m_fX));
    m_pSprite->SetY(static_cast<int>(m_fY));

    m_pSprite->Process(_fDeltaTick);
}

/************
* IsCollidingWith: Checks if the current entity is colliding with another
* @parameter: e - Entity to check collision with
* @return true if entities are colliding
*************/
bool CEntity::IsCollidingWith(CEntity& e)
{
	bool colliding = false;
	
	int e1 = m_pSprite->GetWidth() / 2;
	int e1X = m_pSprite->GetX();
	int e1Y = m_pSprite->GetY();

	int e2 = e.m_pSprite->GetWidth() / 2;
	int e2X = e.m_pSprite->GetX();
	int e2Y = e.m_pSprite->GetY();

	int collision = e1 + e2;
	int actualdistance = static_cast<int> (sqrt(pow((e2X - e1X), 2) + pow((e2Y - e1Y), 2)));

	if (actualdistance < collision)
	{
		colliding = true;
	}

	return colliding;
}

ESprite CEntity::GetCardType()
{
	return m_eSpriteType;
}

/************
* GetHeight: Gets the height of the entity/sprite
* @return m_pSprite->GetHeight() - height of sprite
*************/
float  CEntity::GetHeight() const
{
    return (static_cast<float>(m_pSprite->GetHeight()));
}

/************
* SetHeight: Sets the height of the entity
* @parameter: _f - the height of the entity
*************/
void CEntity::SetHeight(float _f)
{
	m_fHeight = _f;
}

/************
* SetWidth: Sets the width of the entity
* @parameter: _f - Sets the width of the entity
*************/
void CEntity::SetWidth(float _f)
{
	m_fWidth = _f;
}

/************
* GetWidth: Gets the width of the entity/sprite
* @return m_pSprite->GetWidth() - width of sprite
*************/
float CEntity::GetWidth() const
{
	return (static_cast<float>(m_pSprite->GetWidth()));
}

/************
* SetX: Sets the X position of the entity
* @parameter: _f - the X position of the entity. Adds half the width of the sprite 
*************/
void CEntity::SetX(float _f)
{
	m_fX = _f;
}

/************
* SetY: Sets the Y position of the entity
* @parameter: _f - the X position of the entity
*************/
void CEntity::SetY(float _f)
{
	m_fY = _f;
}

/************
* GetX: Gets the X position of the entity
* @return m_fX - entity x position
*************/
float CEntity::GetX() const
{
	return (m_fX);
}

/************
* GetY: Gets the Y position of the entity
* @return m_fY - entity Y position
*************/
float CEntity::GetY() const
{
	return (m_fY);
}


/************
* FlipOpenCard: Flips open the 
* @return m_pSprite->GetWidth() - width of sprite
*************/
void CEntity::FlipOpenCard(bool _open, CEntity& e)
{
	//Switch sprites
	if (_open)
	{
		//if true, set current sprite as front of card
		e.m_pSpriteFront->SetX(e.m_pSprite->GetX()); //Fixes first time draw at 0,0
		e.m_pSpriteFront->SetY(e.m_pSprite->GetY());
		e.m_pSprite = e.m_pSpriteFront;
	}
	else
	{
		//if false, set current sprite as back of card
		e.m_pSprite = e.m_pSpriteBack;
	}
}
