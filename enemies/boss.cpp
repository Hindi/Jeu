#include "boss.h"

using namespace std;
using namespace sf;

Boss::Boss(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, std::tr1::shared_ptr<Player> player,
           std::tr1::shared_ptr<Player> player2, bool allowTeleport) :
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, false, player, player2, allowTeleport)


{
}

Boss::~Boss()
{
    delete m_name;
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

void Boss::addsMove()
{

}

void Boss::drawAdds()
{
    this->addsMove();
    list<tr1::shared_ptr<Adds> >::const_iterator li(m_adds.begin());
    for(; li!= m_adds.end(); li++)
    {
        (*li)->draw();
    }
}

void Boss::draw()
{
    this->drawAdds();
    if(teleporting)
    {
        if(teleportFrame % 2 == 1)
            app.Draw(*m_animated);
        teleportFrame++;
    }
    else
        app.Draw(*m_animated);
}


Vector2f Boss::getPosition()
{
    return m_position;
}

void Boss::pushAdds(std::tr1::shared_ptr<Adds> add)
{
    m_adds.push_back(add);
}

void Boss::setTeleporting(bool state)
{
    list<tr1::shared_ptr<Adds> >::const_iterator li(m_adds.begin());
    teleporting = state;
    for(; li!= m_adds.end(); li++)
    {
        (*li)->setTeleporting(true);
    }
}

void Boss::follow()
{
    list<tr1::shared_ptr<Adds> >::const_iterator li(m_adds.begin());
    unsigned short i = 0;
    for(; li!= m_adds.end(); li++)
    {
        (*li)->getAnimation()->SetPosition(Vector2f(m_position.x + 45 + i, m_position.y + image->GetHeight()/1.65));
        (*li)->setPosition(Vector2f(m_position.x + i, m_position.y + image->GetHeight()/1.65));
        i = image->GetWidth()/3.5;
    }

}
