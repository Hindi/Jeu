#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "../timer.h"
#include "../const.h"

class Score
{
    public:
        Score(unsigned short score, sf::Vector2f position);

        //Destructeur
        ~Score();

        void draw();

        Timer getTime();

        bool isOld();

        sf::String getString();

        void move();

    private:

        sf::Font m_fontCubic;

        sf::String string;

        unsigned short const m_score;

        sf::Vector2f m_position;

        Timer timer;
};

#endif // SCORE_H_INCLUDED
