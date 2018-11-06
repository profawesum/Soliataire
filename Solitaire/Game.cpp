
#include "Clock.h"
#include "BackBuffer.h"
#include "utils.h"

#include "Game.h"


CGame* CGame::pGame = 0;
int CGame::m_MouseX = 0;
int CGame::m_MouseY = 0;




CGame::CGame()
: pLevel(0)
, pClock(0)
, hInstance(0)
, _hwnd(0)
, pBackbuffer(0)
{
}

CGame::~CGame()
{
	delete pLevel;
	pLevel = 0;

    delete pBackbuffer;
    pBackbuffer = 0;

    delete pClock;
    pClock = 0;
}

bool CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
    hInstance = _hInstance;
    _hwnd = _hWnd;

    pClock = new CClock();
    VALIDATE(pClock->Initialise());
    pClock->Process();

    pBackbuffer = new CBackBuffer();
    VALIDATE(pBackbuffer->Initialise(_hWnd, _iWidth, _iHeight));

	pLevel = new CLevel();
	VALIDATE(pLevel->Initialise(_iWidth, _iHeight));

    return (true);
}

void CGame::Draw()
{

    pBackbuffer->Clear();

	pLevel->Draw();

    pBackbuffer->Present();
}

void CGame::Process(float deltaTime)
{

	pLevel->Process(deltaTime);

}

void CGame::ExecuteOneFrame()
{
    float deltaTime = pClock->GetDeltaTick();

    Process(deltaTime);
    Draw();

    pClock->Process();
}

CGame& CGame::GetInstance()
{
    if (pGame == 0)
    {
        pGame = new CGame();
    }

    return (*pGame);
}

void CGame::DestroyInstance()
{
    delete pGame;
    pGame = 0;
}

CBackBuffer* CGame::GetBackBuffer()
{
    return (pBackbuffer);
}

HINSTANCE CGame::GetAppInstance()
{
    return (hInstance);
}

HWND CGame::GetWindow()
{
    return (_hwnd);
}

void CGame::NewGame()
{
	if (pLevel != nullptr)
	{
		delete pLevel;
		pLevel = 0;
	}
	pLevel = new CLevel();
	pLevel->Initialise(1195, 945);
}

CLevel* CGame::GetLevelInstance()
{
	return (pLevel);
}

void CGame::GameOverWon()
{
	MessageBox(_hwnd, L"You Won!", L"Game Over", MB_OK);
	CGame::NewGame();
}
