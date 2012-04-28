#include "timer.h"

Timer::Timer() : m_elapsedTime(0.0f), m_state(paused)
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
