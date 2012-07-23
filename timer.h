#ifndef TIMER_H
#define TIMER_H
#include <SFML/System.hpp>
#include <iostream>

class Timer {
public:

    Timer();

    void start();
    void pause();
    void reinitialize();
    float getTime();
    void sleep(unsigned pMilliseconds);

private:
    enum State {started, paused};

    sf::Clock m_clock;

    State m_state;
    float m_elapsedTime;
};

#endif
