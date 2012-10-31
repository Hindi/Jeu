#include "boss.h"

using namespace std;
using namespace sf;

Boss::Boss(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, std::tr1::shared_ptr<Player> player,
           std::tr1::shared_ptr<Player> player2) :
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, false, player, player2)
{

}

Boss::~Boss()
{
    delete m_animated;
    if (image!= NULL )
    {
        delete image;
    }
}

IntRect Boss::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x + image->GetWidth()/4;
    boundingBox.Right = boundingBox.Left + image->GetWidth()-image->GetWidth()/2;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight();

    return boundingBox;
}


IntRect Boss::getWeakBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x + image->GetWidth()/2;
    boundingBox.Right = boundingBox.Left + image->GetWidth()/2;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight()/2;

    return boundingBox;
}

void Boss::drawAdds()
{
    list<tr1::shared_ptr<Adds> >::const_iterator li(m_adds.begin());
    for(; li!= m_adds.end(); li++)
    {
        (*li)->draw();
    }
}

void Boss::draw()
{
    app.Draw(*m_animated);
    this->drawAdds();
}
