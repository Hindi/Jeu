#include "boss.h"

using namespace std;
using namespace sf;

Boss::Boss(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, std::tr1::shared_ptr<Player> player,
           std::tr1::shared_ptr<Player> player2, bool allowTeleport) :
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, false, player, player2),
            allowTeleport(allowTeleport)

{
    teleportTimer.start();
}

Boss::~Boss()
{
    delete m_animated;
    if(image!= NULL )
    {
        delete image;
    }
    delete m_name;
    delete m_type;
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
    list<tr1::shared_ptr<Adds> >::const_iterator li(m_adds.begin());
    for(; li!= m_adds.end(); li++)
    {
        (*li)->draw();
    }
}

void Boss::draw()
{
    if(teleporting)
    {
        if(teleportFrame % 2 == 1)
            app.Draw(*m_animated);
        teleportFrame++;
    }
    else
        app.Draw(*m_animated);
    this->drawAdds();
}

void Boss::follow()
{
    list<tr1::shared_ptr<Adds> >::const_iterator li(m_adds.begin());
    unsigned short i = 0;
    for(; li!= m_adds.end(); li++)
    {
        (*li)->getAnimation()->SetPosition(Vector2f(m_position.x + i, m_position.y + image->GetHeight()));
        i = image->GetWidth() /1.5;
    }
}

Vector2f Boss::getPosition()
{
    return m_position;
}

bool Boss::canTeleport()
{
    if(allowTeleport && teleportTimer.getTime() > 3)
    {
        return true;
    }
    return false;
}

void Boss::setTeleporting(bool state)
{
    teleporting = state;
    if(state == false)
        teleportTimer.reinitialize();
}


bool Boss::readyToTeleport()
{
    if(teleportTimer.getTime() > 4)
        return true;
    return false;
}

void Boss::teleport()
{
    Vector2f position(rand()%800+1, 200 + rand()%300+1);
    m_animated->SetPosition(Vector2f(position));
    m_position = position;

}

const char* Boss::getType()
{
    return m_type;
}
