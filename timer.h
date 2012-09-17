#ifndef TIMER_H
#define TIMER_H
#include <SFML/System.hpp>
#include <iostream>

class Timer {
public:

    Timer();

    //Démarre le timer
    void start();

    //Met le timer en pause
    void pause();

    //Remet le timer à zéro
    void reinitialize();

    //Renvoie le temps
    float getTime();

    //Mise en pause qui dépend de l'OS
    void sleep(unsigned pMilliseconds);

private:
    //Etat courant du timer
    enum State {started, paused};
    State m_state;

    //L'horloge utilisée par le timer
    sf::Clock m_clock;

    //Temps passé
    float m_elapsedTime;
};

#endif
