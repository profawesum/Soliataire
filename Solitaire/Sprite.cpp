

#include <iostream>
#include <map>
#include <string>


#include "Game.h"
#include "BackBuffer.h"
#include "utils.h"
#include "resource.h"

#include "Sprite.h"


HDC CSprite::s_hSharedSpriteDC = 0;
int CSprite::s_iRefCount = 0;

CSprite::CSprite(ESprite _eType)
: m_eSpriteType(_eType)
, m_iFramePositionW(8)
, m_iFramePositionH(0) //The Y position where the sprite is located on the sprite sheet
, m_iX(0)
, m_iY(0)
{
	m_iW = 121; //WIDTH OF CARD 
	m_iH = 177; //HEIGHT OF CARD 

	int _gap = 4;

	switch (_eType)
	{
	#pragma region "Hearts"
		case ESprite::H2:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 0) + (_gap * 1);
			break;
		}
		case ESprite::H3:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 1) + (_gap * 2);
			break;
		}
		case ESprite::H4:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 2) + (_gap * 3);
			break;
		}
		case ESprite::H5:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 3) + (_gap * 4);
			break;
		}
		case ESprite::H6:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 4) + (_gap * 5);
			break;
		}
		case ESprite::H7:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 5) + (_gap * 6);
			break;
		}
		case ESprite::H8:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 6) + (_gap * 7);
			break;
		}
		case ESprite::H9:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 7) + (_gap * 8);
			break;
		}
		case ESprite::H10:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 8) + (_gap * 9);
			break;
		}
		case ESprite::HJ:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 9) + (_gap * 10);
			break;
		}
		case ESprite::HQ:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 10) + (_gap * 11);
			break;
		}
		case ESprite::HK:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 11) + (_gap * 12);
			break;
		}
		case ESprite::HA:
		{
			m_iFramePositionH = (m_iH * 0) + (_gap * 1);
			m_iFramePositionW = (m_iW * 12) + (_gap * 13);
			break;
		}
	#pragma endregion 
	#pragma region "Diamonds"
		case ESprite::D2:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 0) + (_gap * 1);
			break;
		}
		case ESprite::D3:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 1) + (_gap * 2);
			break;
		}
		case ESprite::D4:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 2) + (_gap * 3);
			break;
		}
		case ESprite::D5:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 3) + (_gap * 4);
			break;
		}
		case ESprite::D6:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 4) + (_gap * 5);
			break;
		}
		case ESprite::D7:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 5) + (_gap * 6);
			break;
		}
		case ESprite::D8:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 6) + (_gap * 7);
			break;
		}
		case ESprite::D9:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 7) + (_gap * 8);
			break;
		}
		case ESprite::D10:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 8) + (_gap * 9);
			break;
		}
		case ESprite::DJ:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 9) + (_gap * 10);
			break;
		}
		case ESprite::DQ:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 10) + (_gap * 11);
			break;
		}
		case ESprite::DK:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 11) + (_gap * 12);
			break;
		}
		case ESprite::DA:
		{
			m_iFramePositionH = (m_iH * 1) + (_gap * 2);
			m_iFramePositionW = (m_iW * 12) + (_gap * 13);
			break;
		}
	#pragma endregion 
	#pragma region "CLUBS"
		case ESprite::C2:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 0) + (_gap * 1);
			break;
		}
		case ESprite::C3:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 1) + (_gap * 2);
			break;
		}
		case ESprite::C4:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 2) + (_gap * 3);
			break;
		}
		case ESprite::C5:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 3) + (_gap * 4);
			break;
		}
		case ESprite::C6:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 4) + (_gap * 5);
			break;
		}
		case ESprite::C7:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 5) + (_gap * 6);
			break;
		}
		case ESprite::C8:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 6) + (_gap * 7);
			break;
		}
		case ESprite::C9:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 7) + (_gap * 8);
			break;
		}
		case ESprite::C10:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 8) + (_gap * 9);
			break;
		}
		case ESprite::CJ:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 9) + (_gap * 10);
			break;
		}
		case ESprite::CQ:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 10) + (_gap * 11);
			break;
		}
		case ESprite::CK:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 11) + (_gap * 12);
			break;
		}
		case ESprite::CA:
		{
			m_iFramePositionH = (m_iH * 2) + (_gap * 3);
			m_iFramePositionW = (m_iW * 12) + (_gap * 13);
			break;
		}
#pragma endregion 
	#pragma region "SPADES"
		case ESprite::S2:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 0) + (_gap * 1);
			break;
		}
		case ESprite::S3:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 1) + (_gap * 2);
			break;
		}
		case ESprite::S4:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 2) + (_gap * 3);
			break;
		}
		case ESprite::S5:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 3) + (_gap * 4);
			break;
		}
		case ESprite::S6:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 4) + (_gap * 5);
			break;
		}
		case ESprite::S7:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 5) + (_gap * 6);
			break;
		}
		case ESprite::S8:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 6) + (_gap * 7);
			break;
		}
		case ESprite::S9:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 7) + (_gap * 8);
			break;
		}
		case ESprite::S10:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 8) + (_gap * 9);
			break;
		}
		case ESprite::SJ:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 9) + (_gap * 10);
			break;
		}
		case ESprite::SQ:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 10) + (_gap * 11);
			break;
		}
		case ESprite::SK:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 11) + (_gap * 12);
			break;
		}
		case ESprite::SA:
		{
			m_iFramePositionH = (m_iH * 3) + (_gap * 4);
			m_iFramePositionW = (m_iW * 12) + (_gap * 13);
			break;
		}
	#pragma endregion 
		case ESprite::BACKGROUND:
		{
			m_iW = 1000;
			m_iH = 800;
			break;
		}
		case ESprite::CARDBACK:
		{
			m_iFramePositionH = (m_iH * 4) + (_gap * 5);
			m_iFramePositionW = (m_iW * 0) + (_gap * 1);
			break;
		}
		case ESprite::NONE:
		{
			m_iFramePositionH = (m_iH * 4) + (_gap * 5);
			m_iFramePositionW = (m_iW * 1) + (_gap * 2);
			m_iW = 10; //WIDTH OF player 
			m_iH = 10; //HEIGHT OF player 
			break;
		}
		default:
			break;
	}

    ++s_iRefCount;
}

CSprite::CSprite()
{

}

CSprite::~CSprite()
{
	DeleteObject(m_hSprite);
	DeleteObject(m_hMask);

	--s_iRefCount;

	if (s_iRefCount == 0)
	{
		DeleteDC(s_hSharedSpriteDC);
		s_hSharedSpriteDC = 0;
	}
}

bool
CSprite::Initialise()
{
    HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();

    if (!s_hSharedSpriteDC)
    {
        s_hSharedSpriteDC = CreateCompatibleDC(NULL);
    }

	int iSprite = 0;
	int iMask = 0;

	if(m_eSpriteType == ESprite::BACKGROUND)
	{
		iSprite = IDB_BACKGROUND;
		iMask = IDB_BACKGROUNDMASK;
	}
	else
	{
		iSprite = IDB_CARDS;
		iMask = IDB_CARDSMASK;
	}

	m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(iSprite));
	VALIDATE(m_hSprite);

	m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(iMask));
	VALIDATE(m_hMask);

	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
	GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);

	if (m_eSpriteType == ESprite::BACKGROUND)
	{
		m_iW = m_bitmapSprite.bmWidth;
		m_iH = m_bitmapSprite.bmHeight;
	}
    return (true);
}

void
CSprite::Draw()
{
	//Sizes of sprites
	int iW = GetWidth();
	int iH = GetHeight();
	//Positions of sprites
	int iX = m_iX - (iW / 2);
	int iY = m_iY - (iH / 2);	

    CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

    HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

    BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, m_iFramePositionW, m_iFramePositionH, SRCAND);

    SelectObject(s_hSharedSpriteDC, m_hSprite);

    BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, m_iFramePositionW, m_iFramePositionH, SRCPAINT);

    SelectObject(s_hSharedSpriteDC, hOldObj);
}

void
CSprite::Process(float _fDeltaTick)
{
	//Sprite doesnt have anything to process but AnimatedSprite does.
}

int
CSprite::GetWidth() const
{
    return m_iW;
}

int
CSprite::GetHeight() const
{
    return m_iH;
}

int 
CSprite::GetX() const
{
    return (m_iX);
}

int 
CSprite::GetY() const
{
    return (m_iY);
}

void 
CSprite::SetX(int _i)
{
    m_iX = _i;
}

void 
CSprite::SetY(int _i)
{
    m_iY = _i;
}

void 
CSprite::TranslateRelative(int _iX, int _iY)
{
    m_iX += _iX;
    m_iY += _iY;
}

void 
CSprite::TranslateAbsolute(int _iX, int _iY)
{
    m_iX = _iX;
    m_iY = _iY;
}
