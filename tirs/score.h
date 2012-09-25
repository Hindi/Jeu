#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <sstream>

class Score
{
    public:
        Score(sf::RenderWindow &app);

        //Destructeur
        ~Score();

        void addScore(int score);

    private:
        sf::RenderWindow &m_app;

        sf::Font m_fontCubic;

        sf::String string;

        std::list<sf::String*> m_strings;

};

#endif // SCORE_H_INCLUDED
