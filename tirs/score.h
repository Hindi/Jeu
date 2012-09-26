#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class Score
{
    public:
        Score(sf::RenderWindow &app, int score, sf::Vector2f position);

        //Destructeur
        ~Score();

        void draw();

    private:
        sf::RenderWindow &m_app;

        sf::Font m_fontCubic;

        sf::String string;

        int const m_score;

        sf::Vector2f m_position;
};

#endif // SCORE_H_INCLUDED
