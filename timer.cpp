#include "timer.h"

using namespace std;

#ifdef _WIN32
    #include <windows.h>
    void Timer::sleep(unsigned pMilliseconds)
    {
        ::Sleep(pMilliseconds);
    }
#else
    #include <unistd.h>
    void Timer::sleep(unsigned pMilliseconds)
    {
        static const unsigned MilliToMicro = 1000;
        ::usleep(pmilliseconds * MilliToMicro);
    }
#endif

Timer::Timer() :m_state(paused), m_elapsedTime(0.0f)
{}

void Timer::start()
{
    if(m_state != started) // On ne lance pas le timer si il est déja lancé
    {
        m_clock.Reset();
        m_state = started;
    }
}

void Timer::pause()
{
    if(m_state != paused) // On ne mets pas en pause le timer si il est déja en pause
    {
        m_state = paused;
        m_elapsedTime += m_clock.GetElapsedTime();
    }
}

void Timer::reinitialize()
{
    m_clock.Reset();
    m_elapsedTime = 0.0f;
}

float Timer::getTime()
{
    float time;

    if(m_state == paused)
    {
        time = m_elapsedTime;
    }
    else
    {
        time = m_clock.GetElapsedTime() + m_elapsedTime;
    }
    return time;
}

