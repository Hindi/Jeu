#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
    public:
        Animation();

        //Destructeur
        ~Animation();

        //Initialise l'animation
        void initialize(float x, float y, int frameX, int frameY);

        //Actualise les frame
        void update(sf::RenderWindow &app);

        //Dessine les naimations
        void draw(sf::RenderWindow &app);

        //Accesseurs public
        bool getActive();
        void setActive(bool value);
        int getCurrentFrame(int axis);
        void setCurrentFrame(int axis, int value);
        int getPosition(int axis);
        void setPosition(int axis, int value);
        void setImage(sf::Image &tempImage);
        int getFrameWidth();
        int getFrameHeight();

    protected:
        //Sprite qui contient l'image
        sf::Sprite sprite;

        //Numéro de frame, nombre de frame, ...
        float frameCounter, switchFrame, amountOfFrameX, amountOfFrameY, x,y;

        //Frame en cours
        int currentFrameX, currentFrameY;

        //Animation lancée ou non
        bool active;

        //Comptage temps
        sf::Clock clock;

};
#endif // ANIMATION_H_INCLUDED
