


#include "BackBuffer.h"

CBackBuffer::CBackBuffer()
: m_hWnd(0)
, m_hDC(0)
, m_hSurface(0)
, m_hOldObject(0)
, width(0)
, height(0)
{

}

CBackBuffer::~CBackBuffer()
{
    SelectObject(m_hDC, m_hOldObject);

    DeleteObject(m_hSurface);
    DeleteObject(m_hDC);
}

bool
CBackBuffer::Initialise(HWND _hWnd, int _iWidth, int _iHeight)
{
    m_hWnd = _hWnd;

    width = _iWidth;
    height = _iHeight;

    HDC hWindowDC = ::GetDC(m_hWnd);

    m_hDC = CreateCompatibleDC(hWindowDC);

    m_hSurface = CreateCompatibleBitmap(hWindowDC, width, height);

    ReleaseDC(m_hWnd, hWindowDC);

    m_hOldObject = static_cast<HBITMAP>(SelectObject(m_hDC, m_hSurface));

    HBRUSH brushWhite = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
    HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(m_hDC, brushWhite));

    Rectangle(m_hDC, 0, 0, width, height);

    SelectObject(m_hDC, oldBrush);

    return (true);
}

void
CBackBuffer::Clear()
{
    HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(GetBFDC(), GetStockObject(LTGRAY_BRUSH)));

    Rectangle(GetBFDC(), 0, 0, GetWidth(), GetHeight());

    SelectObject(GetBFDC(), hOldBrush);
}

HDC
CBackBuffer::GetBFDC() const
{
    return (m_hDC);
}

int 
CBackBuffer::GetWidth() const
{
    return (width);
}

int 
CBackBuffer::GetHeight() const
{
    return (height);
}

void 
CBackBuffer::Present()
{
    HDC hWndDC = ::GetDC(m_hWnd);

    BitBlt(hWndDC, 0, 0, width, height, m_hDC, 0, 0, SRCCOPY);

    ReleaseDC(m_hWnd, hWndDC);
}
