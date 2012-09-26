#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "../timer.h"

class Score
{
    public:
        Score(sf::RenderWindow &app, int score, sf::Vector2f position);

        //Destructeur
        ~Score();

        void draw();

        Timer getTime();

        bool isOld();

        sf::String getString();

        sf::String string;

    private:
        sf::RenderWindow &m_app;

        sf::Font m_fontCubic;


        int const m_score;

        sf::Vector2f m_position;

        Timer timer;
};

#endif // SCORE_H_INCLUDED
