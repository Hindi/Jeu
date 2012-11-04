#include "adds.h"

using namespace std;
using namespace sf;

Adds::Adds(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position,
            const char* type, const char* moveMethod, int moveValue, const int coefSpeed, const int firerate, bool spawner, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2, bool allowTeleport):
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, spawner, player, player2, allowTeleport),
            m_maxLife(5)
{
    image = new Image();
    *image = image_manager::getInstance()->getImage("images/enemy.png");
    m_animated = new Animated;
    m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth(), image->GetHeight()) ));
    m_animated->SetAnim(&m_anim);
    m_animated->SetLoop(false);
    m_animated->Play();
    m_animated->SetPosition(position.x, position.y);
}

Adds::~Adds()
{
    delete image;
    delete m_animated;
}


void Adds::draw()
{
    if(teleporting)
    {
        if(teleportFrame % 2 == 1)
            app.Draw(*m_animated);
        teleportFrame++;
    }
    else
        app.Draw(*m_animated);
}

void Adds::teleport()
{
    teleporting = false;
    teleportTimer.reinitialize();
    teleportFrame = 0;
}
