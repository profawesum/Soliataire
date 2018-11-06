

#include <windows.h>


#include "Clock.h"


CClock::CClock()
: m_fTimeElapsed(0.0f)
, m_fDeltaTime(0.0f)
, m_fLastTime(0.0f)
, m_fCurrentTime(0.0f)
{

}

CClock::~CClock()
{

}

bool
CClock::Initialise()
{
	__int64 _TimerFrequency, _currTime;
	QueryPerformanceFrequency((LARGE_INTEGER*)&_TimerFrequency);
	m_SecondsPerCount = 1.0f / static_cast<float>(_TimerFrequency);

	QueryPerformanceCounter((LARGE_INTEGER*)&_currTime);
	m_fCurrentTime = static_cast<float>(_currTime);
	m_fLastTime = static_cast<float>(_currTime);

	return (true);
}

void
CClock::Process()
{
	//Get the time this frame.

	__int64 currTime;

	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_fCurrentTime = static_cast<float>(currTime);

	//Time difference between this frame and the previous frame
	m_fDeltaTime = static_cast<float>((m_fCurrentTime - m_fLastTime)*m_SecondsPerCount);

	//Prepare for the next frame
	m_fLastTime = static_cast<float>(m_fCurrentTime);

	//Force non-negative
	if (m_fDeltaTime < 0.0)
	{
		m_fDeltaTime = 0.0;
	}

	m_fTimeElapsed += static_cast<float>(m_fDeltaTime);
}

float
CClock::GetDeltaTick()
{
	return static_cast<float>(m_fDeltaTime);
}
