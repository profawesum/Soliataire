

#include "resource.h"
#include "utils.h"
#include "backbuffer.h"
#include "game.h"


#include "background.h"


CBackGround::CBackGround()
{

}

CBackGround::~CBackGround()
{

}

bool
CBackGround::Initialise()
{
	VALIDATE(CEntity::Initialise(ESprite::BACKGROUND));

	return (true);
}

void
CBackGround::Draw()
{
	CEntity::Draw();
}

void
CBackGround::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}
