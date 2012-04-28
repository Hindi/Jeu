#ifndef POPULATION_H_INCLUDED
#define POPULATION_H_INCLUDED
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include "enemy.h"

//Permet de stocker et gérer les ennemis

class Population
{
    public:
        Population(sf::RenderWindow &app);
        virtual ~Population();
        void createEnemy(int score,int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, sf::RenderWindow &app, sf::IntRect subRect);
        std::list<Enemy*>* getPopulation();
        bool haveEnnemyInProgress();
        void drawPopulation();
        void checkPopulation();

    protected:
        sf::RenderWindow &m_app;
        std::list<Enemy*> m_enemies;
};

#endif // POPULATION_H_INCLUDED
