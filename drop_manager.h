#ifndef DROP_MANAGER_H_INCLUDED
#define DROP_MANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "drop.h"
#include "image_manager.h"

class Drop_manager
{
    public:
        Drop_manager(sf::RenderWindow &app, image_manager &image_manager);
        ~Drop_manager();
        void createDrop(int score, sf::Vector2f position);
        std::list <Drop*>* getDrop();
        void manage();
        void move();
        void draw();

    private:
        sf::RenderWindow &m_app;
        std::list <Drop*> m_droplist;
        Drop *drop;
        image_manager &m_image_manager;

};
#endif // DROP_MANAGER_H_INCLUDED
