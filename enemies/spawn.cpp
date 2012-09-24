#include "spawn.h"

using namespace std;
using namespace sf;

Spawn::Spawn(image_manager &imageManager, Vector2f position, RenderWindow &app, Projectile_manager &projectile_manager):
            Unit(5, 5, 5, position, app, projectile_manager),
            m_imageManager(imageManager),
            m_app(app)
{
    image = new Image();
    *image = m_imageManager.getImage("images/Etoile1.png");
    m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth(), image->GetHeight()) ));
    m_animated = new Animated();
    m_animated->SetAnim(&m_anim);
    m_animated->Pause();
    m_animated->SetLoop(true);
    m_animated->SetFrameTime(0.2f);
    m_animated->SetPosition(m_position.x, m_position.y);
}

Spawn::~Spawn()
{

}


void Spawn::fire()
{

}

void Spawn::move()
{

}

void Spawn::draw()
{
    m_app.Draw(*m_animated);
}
