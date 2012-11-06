#include "lilith.h"

using namespace std;
using namespace sf;

Lilith::Lilith(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2) :
            Boss(10, 5, 10000, 5, 5, "images/lilith/corps.png", Vector2f(500, 500), "boss", "don'tmove", 1, 50, 2, player, player2, true),
            m_level(1)
{

}

Lilith::~Lilith()
{

}

void Lilith::fire()
{
    this->VFire();
    this->firinhMahLasor();
}

IntRect Lilith::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x;
    boundingBox.Right = boundingBox.Left + image->GetWidth();
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight()/1.5;

    return boundingBox;
}


IntRect Lilith::getWeakBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x  + image->GetWidth()/2 - 3;
    boundingBox.Right = boundingBox.Left + 3;
    boundingBox.Top = m_position.y + image->GetHeight()-20;
    boundingBox.Bottom = boundingBox.Top + 10;

    return boundingBox;
}

void Lilith::move()
{
    this->follow();
}
