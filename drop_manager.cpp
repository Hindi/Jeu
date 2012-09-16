#include "drop_manager.h"

using namespace std;
using namespace sf;

Drop_manager::Drop_manager(RenderWindow &app, image_manager &image_manager):
            m_app(app),
            m_image_manager(image_manager)
{

}

Drop_manager::~Drop_manager()
{

}

void Drop_manager::createDrop(int score, sf::Vector2f position)
{
    drop = new Drop(score, m_image_manager, position);
    m_droplist.push_back(drop);
}

std::list <Drop*>* Drop_manager::getDrop()
{
    return &m_droplist;
}

void Drop_manager::manage()
{
    this->move();
    this->draw();
}

void Drop_manager::move()
{
    list<Drop*>::const_iterator lit(m_droplist.begin());
    for(; lit!= m_droplist.end(); lit++)
    {
        Vector2f position = (*lit)->getPosition();
        Vector2f speed(0, (*lit)->getSpeed()*m_app.GetFrameTime());
        Vector2f newPosition(position.x + speed.x, position.y + speed.y);
        (*lit)->move(newPosition, speed);
    }


}
void Drop_manager::draw()
{
    list<Drop*>::const_iterator lit(m_droplist.begin());
    for(; lit!= m_droplist.end(); lit++)
    {
        m_app.Draw((*lit)->getSprite());
    }
}
