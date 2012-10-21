#ifndef DROP_MANAGER_H_INCLUDED
#define DROP_MANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <tr1/memory>

#include "drop.h"
#include "image_manager.h"
#include "const.h"

class Drop_manager
{
    public:
        //Créé un drop
        void createDrop(int score, sf::Vector2f position);

        //Accesseur sur la liste des drops
        std::list <std::tr1::shared_ptr<Drop> >* getDrop();

        //Mettent à jour les positions
        void manage();
        void move();
        void draw();

        static void kill();
        static Drop_manager* getInstance();

        void reset();

    private:
        //Liste des drops
        std::list <std::tr1::shared_ptr<Drop> > m_droplist;

        Drop_manager();

        //Destructeur
        ~Drop_manager();

        static Drop_manager* _singleton;

};


#endif // DROP_MANAGER_H_INCLUDED
