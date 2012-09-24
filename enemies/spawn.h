#ifndef SPAWN_H_INCLUDED
#define SPAWN_H_INCLUDED

#include <list>
#include <string>
#include <SFML/Graphics.hpp>

#include "../animation.h"
#include "../Animated.hpp"
#include "../image_manager.h"
#include "../tirs/projectile_manager.h"

#include "../unit.h"

class Spawn : public Unit
{
    public:
        Spawn(image_manager &imageManager, sf:: Vector2f position, sf::RenderWindow &app, Projectile_manager &projectile_manager);

        //Destructeur
        ~Spawn();

        //Pour tirer
        void fire();

        //Pour bouger
        void move();

        //Pour aficherl 'objet à l'écran
        void draw();

    private:
        sf::RenderWindow &m_app;

        //L'image du spawn
        sf::Image *image;

        //Le manager d'image
        image_manager &m_imageManager;

        //Position courante
        sf:: Vector2f m_position;

        //Variables d'animation
        Animated *m_animated;
        Anim m_anim;

};

#endif // SPAWN_H_INCLUDED
