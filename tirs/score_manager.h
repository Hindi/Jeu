#ifndef SCORE_MANAGER_H_INCLUDED
#define SCORE_MANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "score.h"
#include "../const.h"

class Score_manager
{
    public:
        Score_manager();

        //Destructeur
        ~Score_manager();

        void addScore(int score, sf::Vector2f position);

        void draw();

        void manage();

        bool haveScoreInProgress();

    private:
        Score *m_score;

        std::list<Score*> m_scores;
};

#endif // SCORE_MANAGER_H_INCLUDED
