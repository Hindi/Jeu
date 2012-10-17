#include "drop_manager.h"

using namespace std;
using namespace sf;

Drop_manager* Drop_manager::_singleton = NULL;

Drop_manager::Drop_manager()
{

}

Drop_manager::~Drop_manager()
{
    m_droplist.clear();
}

//Créé un objet drop et l'ajoute dansl al iste des drops
void Drop_manager::createDrop(int score, sf::Vector2f position)
{
    std::tr1::shared_ptr<Drop> drop(new Drop(score, position));
    m_droplist.push_back(drop);
}

std::list <std::tr1::shared_ptr<Drop> >* Drop_manager::getDrop()
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
    list<std::tr1::shared_ptr<Drop> >::const_iterator lit(m_droplist.begin());
    for(; lit!= m_droplist.end(); lit++)
    {
        //Calcul de la nouvelle position pour chaque drop
        Vector2f position = (*lit)->getPosition();
        Vector2f speed(0, (*lit)->getSpeed()*app.GetFrameTime());
        Vector2f newPosition(position.x + speed.x, position.y + speed.y);
        //Déplacement de chaque drop
        (*lit)->move(newPosition, speed);
    }
}

//Dessine l'objet
void Drop_manager::draw()
{
    list<std::tr1::shared_ptr<Drop> >::const_iterator lit(m_droplist.begin());
    for(; lit!= m_droplist.end(); lit++)
    {
        app.Draw((*lit)->getSprite());
    }
}

Drop_manager* Drop_manager::getInstance()
  {
    if (NULL == _singleton)
      {
        std::cout << "drop manager : creating singleton." << std::endl;
        _singleton =  new Drop_manager;
      }

    return _singleton;
  }

void Drop_manager::kill ()
  {
    if (NULL != _singleton)
      {
        delete _singleton;
        _singleton = NULL;
      }
  }
