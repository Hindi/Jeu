#ifndef TIMER_H
#define TIMER_H
#include <SFML/System.hpp>
#include <iostream>

class Timer {
public:

    Timer();

    //D�marre le timer
    void start();

    //Met le timer en pause
    void pause();

    //Remet le timer � z�ro
    void reinitialize();

    //Renvoie le temps
    float getTime();

    //Mise en pause qui d�pend de l'OS
    void sleep(unsigned pMilliseconds);

private:
    //Etat courant du timer
    enum State {started, paused};
    State m_state;

    //L'horloge utilis�e par le timer
    sf::Clock m_clock;

    //Temps pass�
    float m_elapsedTime;
};

#endif
