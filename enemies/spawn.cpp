#include "spawn.h"

using namespace std;
using namespace sf;

Spawn::Spawn(image_manager &imageManager, Vector2f position, RenderWindow &app, Projectile_manager &projectile_manager):
            Unit(5, 1, 1, position, app, projectile_manager),
            m_imageManager(imageManager),
            m_app(app),
            moveRate(2),
            fireRate(1),
            m_position(position),
            m_angleMove(0),
            lastMove(0),
            lastShot(0)
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

    timerMove.start();
    timerFire.start();
}

Spawn::~Spawn()
{

}


void Spawn::fire()
{
    if(timerFire.getTime() - lastShot > fireRate)
    {
        lastShot = timerFire.getTime();
        Vector2f distance(10, 10);
        Vector2f position(m_animated->GetPosition().x, m_animated->GetPosition().y);
        cout << position.x << position.y << endl;
        projectile = new Projectile("images/projectile2.png", position, Vector2f(100, 200), coefSpeed, m_imageManager);
        m_projectile_manager.addEnemyProjectile(projectile);
    }
}

void Spawn::move()
{
    Vector2f speed;
    if(timerMove.getTime() - lastMove > moveRate)
    {
        m_angleMove = rand() % 360 + 1;
        lastMove = timerMove.getTime();
    }
    speed.x = m_app.GetFrameTime() * m_xSpeed * coefSpeed * cos(m_angleMove);
    speed.y = m_app.GetFrameTime() * m_ySpeed * coefSpeed * sin(m_angleMove);
    m_position += speed;
    m_animated->SetPosition(m_position);
    this->fire();
}

void Spawn::draw()
{
    m_app.Draw(*m_animated);
}
