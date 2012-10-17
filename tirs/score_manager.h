#ifndef SCORE_MANAGER_H_INCLUDED
#define SCORE_MANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "tr1/memory"

#include "score.h"
#include "../const.h"

class Score_manager
{
    public:

        void addScore(int score, sf::Vector2f position);

        void draw();

        void manage();

        bool haveScoreInProgress();

        static void kill();
        static Score_manager* getInstance();

    private:
        std::list<std::tr1::shared_ptr<Score> > m_scores;

        Score_manager();

        //Destructeur
        ~Score_manager();

        static Score_manager* _singleton;
};


#endif // SCORE_MANAGER_H_INCLUDED
