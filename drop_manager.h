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

        //Destructeur
        ~Drop_manager();

        //Créé un drop
        void createDrop(int score, sf::Vector2f position);

        //Accesseur sur la liste des drops
        std::list <Drop*>* getDrop();

        //Mettent à jour les positions
        void manage();
        void move();
        void draw();

    private:
        //La fenêtre
        sf::RenderWindow &m_app;

        //Liste des drops
        std::list <Drop*> m_droplist;

        Drop *drop;

        //Manager d'image
        image_manager &m_image_manager;

};
#endif // DROP_MANAGER_H_INCLUDED
