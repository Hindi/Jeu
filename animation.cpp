#include "animation.h"

using namespace sf;
using namespace std;

Animation::Animation()
{

}

Animation::~Animation()
{

}

int Animation::getFrameWidth()
{
    return sprite.GetImage()->GetWidth() / amountOfFrameX;
}

int Animation::getFrameHeight()
{
    return sprite.GetImage()->GetHeight() / amountOfFrameY;
}

void Animation::initialize(float x, float y, int frameX, int frameY)
{
    frameCounter = 0;
    switchFrame = 3;
    this->x = x;
    this->y = y;
    amountOfFrameY = frameY;
    amountOfFrameX = frameX;
    active = false;
}

void Animation::update(RenderWindow &app)
{
    if(active)
        frameCounter += 10*(float)app.GetFrameTime();
    else
        frameCounter += clock.GetElapsedTime();

    if(frameCounter >= switchFrame)
    {
        frameCounter = 0;
        clock.Reset();
        currentFrameX += getFrameWidth();
    }
    if(currentFrameX >= sprite.GetImage()->GetWidth())
        currentFrameX = 0;
    sprite.SetSubRect(IntRect(currentFrameX, currentFrameY*getFrameHeight(), currentFrameX + getFrameWidth(),currentFrameY*getFrameHeight() + getFrameHeight()));
    sprite.SetPosition(x,y);
}

void Animation::draw(RenderWindow &app)
{
    app.Draw(sprite);
}

bool Animation::getActive()
{
    return active;
}

void Animation::setActive(bool value)
{
    active = value;
}

int Animation::getCurrentFrame(int axis)
{
    if(axis == 1)
        return currentFrameX;
    else
        return currentFrameY;
}

void Animation::setCurrentFrame(int axis, int value)
{
    //Axe 1 : x, les autre : y
    //value : Les valeurs commencent à zéro et sont croissante en descendant l'image.
    if(axis == 1)
        currentFrameX = value;
    else
        currentFrameY = value;
}

int Animation::getPosition(int axis)
{
    if(axis == 1)
        return x;
    else
        return y;
}

void Animation::setPosition(int axis, int value)
{
    //Axe 1 : x, les autre : y
    if(axis == 1)
        x = value;
    else
        y = value;
}

void Animation::setImage(Image &tempImage)
{
    sprite.SetImage(tempImage);
}
