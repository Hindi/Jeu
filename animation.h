#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
    public:
        Animation();
        ~Animation();
        void initialize(float x, float y, int frameX, int frameY);
        void update(sf::RenderWindow &app);
        void draw(sf::RenderWindow &app);
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
        sf::Sprite sprite;
        float frameCounter, switchFrame, amountOfFrameX, amountOfFrameY;
        int currentFrameX, currentFrameY;
        float x,y;
        bool active;
        sf::Clock clock;

};
#endif // ANIMATION_H_INCLUDED
