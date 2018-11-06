
#if !defined(__CLOCK_H__)
#define __CLOCK_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes
class CClock
{
    // Member Functions
public:
    CClock();
    ~CClock();

    bool Initialise();

    void Process();

    float GetDeltaTick();

protected:

private:
    CClock(const CClock& _kr);
    CClock& operator= (const CClock& _kr);

    // Member Variables
public:

protected:
    float m_fTimeElapsed;
    float m_fDeltaTime;
    float m_fLastTime;
	double m_fCurrentTime;
	double m_SecondsPerCount;
	int m_iFrameCount = 0;

private:

};

#endif    // __CLOCK_H__
