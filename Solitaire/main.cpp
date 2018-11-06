

#include <windows.h>
#include <windowsx.h>

#include "Game.h"
#include "Clock.h"
#include "utils.h"
#include "resource.h"

#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

CGame& game = CGame::GetInstance();
HMENU g_hMenu;

LRESULT CALLBACK
WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
    switch (_uiMsg)
    {

	case WM_COMMAND:
	{
		switch (LOWORD(_wParam)) {
		
		//start new game with drawing 1 card
		case ID_NEWGAME_DRAW1: {
			//starts new game
			game.draw3 = 0;
			game.NewGame();
			break;
		}
		//start new game with drawing 3 cards
		case ID_NEWGAME_DRAW3: {
			//starts new game
			game.draw3 = 1;
			game.NewGame();
			break;
		}
		//show the instructions
		case ID_ABOUT_INSTRUCTIONS: {
		
			break;
		}
		//quits the game
		case ID_QUIT: {

			PostQuitMessage(0);
			break;

		}
		default:
			break;
		}
	
	}
		case WM_LBUTTONDOWN:
		{
			float _iMouseX = static_cast<float>(LOWORD(_lParam));
			float _iMouseY = static_cast<float>(HIWORD(_lParam));
			game.GetLevelInstance()->HandleUserClick(_iMouseX, _iMouseY);

			return (0);
		}
		break;
		case WM_LBUTTONUP:
		{
			// Simply validate the window.

			float _iMouseX = static_cast<float>(LOWORD(_lParam));
			float _iMouseY = static_cast<float>(HIWORD(_lParam));
			game.GetLevelInstance()->HandleUserRelease(_iMouseX, _iMouseY);

			return (0);
		}
		break;
		case WM_MOUSEMOVE:
		{
			// Simply validate the window.
			int _iMouseX = static_cast<int>(LOWORD(_lParam));
			int _iMouseY = static_cast<int>(HIWORD(_lParam));
			CGame::m_MouseX = _iMouseX;
			CGame::m_MouseY = _iMouseY;

			return (0);
		}
		break;
        case WM_DESTROY:
        {
            PostQuitMessage(0);

            return(0);
        }
        break;

        default:break;
    } 

    return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

HWND 
CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, LPCWSTR _pcTitle)
{
    WNDCLASSEX winclass;

    winclass.cbSize = sizeof(WNDCLASSEX);
    winclass.style = CS_HREDRAW | CS_VREDRAW;
    winclass.lpfnWndProc = WindowProc;
    winclass.cbClsExtra = 0;
    winclass.cbWndExtra = 0;
    winclass.hInstance = _hInstance;
    winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(WHITE_BRUSH));
    winclass.lpszMenuName = NULL;
    winclass.lpszClassName = WINDOW_CLASS_NAME;
    winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&winclass))
    {
        // Failed to register.
        return (0);
    }

    HWND hwnd; 
	g_hMenu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1));

    hwnd = CreateWindowEx(NULL,
                  WINDOW_CLASS_NAME,
                  _pcTitle,
				  WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE, 
				  (GetSystemMetrics(SM_CXSCREEN) - _iWidth)/2, (GetSystemMetrics(SM_CYSCREEN) - _iHeight)/2, //Window position
                  _iWidth, _iHeight,
                  NULL,
                  g_hMenu,
                  _hInstance,
                  NULL);
    
    if (!hwnd)
    {
        // Failed to create.
        return (0);
    }

    return (hwnd);
}

int WINAPI
WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    const int kiWidth = 1195;
    const int kiHeight = 945;


    HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Solitaire");


    if (!game.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
    {
        // Failed
        return (0);
    }

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            game.ExecuteOneFrame();
        }
    }

    CGame::DestroyInstance();

    return (static_cast<int>(msg.wParam));
}
