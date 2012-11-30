#include "octopus.h"

using namespace std;
using namespace sf;

octopus::octopus(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
            Boss(50, 5, 10000, 3, 3, "images/lilith/corps.png", Vector2f(500, -180), "boss", "roundtrip", 1, 30, 2, player, player2, false)
{
    timerMove.start();
}

octopus::~octopus()
{
    //dtor
}

void octopus::fire()
{
    this->firinhMahLasor(5);
}

IntRect octopus::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x;
    boundingBox.Right = boundingBox.Left + image->GetWidth();
    boundingBox.Top = m_position.y ;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight()/1.5;

    return boundingBox;
}

IntRect octopus::getWeakBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x  + image->GetWidth()/2 - 40;
    boundingBox.Right = boundingBox.Left + 70;
    boundingBox.Top = m_position.y + image->GetHeight()-20;
    boundingBox.Bottom = boundingBox.Top + 20;

    return boundingBox;
}
void octopus::move()
{
    if(timerMove.getTime() < 1.5)
    {
        this->moveDown();
        this->follow();
    }
}
