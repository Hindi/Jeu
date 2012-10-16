#include "projectile_manager.h"

using namespace std;
using namespace sf;

Projectile_manager* Projectile_manager::_singleton=NULL;

Projectile_manager::Projectile_manager()
{

}

Projectile_manager::~Projectile_manager()
{

}

bool Projectile_manager::haveEnemyProjectilesInProgress()
{
    //Vérifie si des projectiles sont en cours de déplacement
    if(m_enemyProjectiles.empty())
        return false;
    else
        return true;
}

bool Projectile_manager::havePlayerProjectilesInProgress()
{
    //Vérifie si des projectiles sont en cours de déplacement
    if(m_playerProjectiles.empty())
        return false;
    else
        return true;
}


void Projectile_manager::moveProjectile()
{
    //Déplace les projectiles et les détruit s'ils sortent de l'écran
    double elapsedTime = app.GetFrameTime();

    //****************************************
    //On bouge les projectiles ennemis
    //****************************************
    if(this->haveEnemyProjectilesInProgress())
    {
        list<std::tr1::shared_ptr<Projectile> >::iterator lit(m_enemyProjectiles.begin());
        for(; lit!=m_enemyProjectiles.end(); )//On parcours la liste des projectiles ennemi
        {
            Vector2f speed((*lit)->getSpeed(0)*elapsedTime*(*lit)->getCoefSpeed(),((*lit)->getSpeed(2))*elapsedTime*(*lit)->getCoefSpeed());//On calcule le vecteur vitesse
            (*lit)->move(speed);
            if((*lit)->getPosition().y  > 1500 || (*lit)->getPosition().y  < -50 || (*lit)->getPosition().x  < -50 || (*lit)->getPosition().x > 1300)//On vérifie sa position
            {
                lit = m_enemyProjectiles.erase(lit);//S'il est sorti de l'écran on le supprime
            }
            else
            {
                lit++;//Sinon on passe au suivant
            }
        }
    }


    //****************************************
    //On bouge les projectiles du joueur
    //****************************************
    if(this->havePlayerProjectilesInProgress())
    {
        list<std::tr1::shared_ptr<Projectile> >::iterator li(m_playerProjectiles.begin());
        for(; li!=m_playerProjectiles.end(); )//On parcours la liste des projectiles joueur
        {
            //cout << (*li)->getSpeed(0) << " " << (*li)->getSpeed(1) << endl;
            Vector2f speed((*li)->getSpeed(0)*elapsedTime*(*li)->getCoefSpeed(),((*li)->getSpeed(2))*elapsedTime*(*li)->getCoefSpeed());//On calcule le vecteur vitesse
            (*li)->move(speed);
            if((*li)->getPosition().y  < 0)//On vérifie sa position
            {
                li = m_playerProjectiles.erase(li);//S'il est sorti de l'écran on le supprime
            }
            else
            {
                li++;//Sinon on passe au suivant
            }
        }
    }
}

void Projectile_manager::drawProjectile()
{
    //cout << m_playerProjectiles.size() << endl;
    //Dessine les projectiles pour qu'ils soient affichés à l'écran
    if(this->haveEnemyProjectilesInProgress())
    {
        list<std::tr1::shared_ptr<Projectile> >::const_iterator lit(m_enemyProjectiles.begin());
        for(; lit!=m_enemyProjectiles.end(); lit++)
        {
            (*lit)->draw();//Dessine les projectiles ennemi
        }
    }
    if(this->havePlayerProjectilesInProgress())
    {
        list<std::tr1::shared_ptr<Projectile> >::const_iterator li(m_playerProjectiles.begin());
        for(; li!=m_playerProjectiles.end(); li++)
        {
            (*li)->draw();//Dessine les projectiles du joueur
        }
    }


}

void Projectile_manager::addEnemyProjectile(std::tr1::shared_ptr<Projectile>  projectile)
{
    m_enemyProjectiles.push_back(projectile);
}

void Projectile_manager::addPlayerProjectile(std::tr1::shared_ptr<Projectile>  projectile)
{
    m_playerProjectiles.push_back(projectile);
}


list<std::tr1::shared_ptr<Projectile> >* Projectile_manager::getEnemyProjectiles()
{
    return &m_enemyProjectiles;
}

list<std::tr1::shared_ptr<Projectile> >* Projectile_manager::getPlayerProjectiles()
{
    return &m_playerProjectiles;
}


Projectile_manager* Projectile_manager::getInstance()
  {
    if (NULL == _singleton)
      {
        std::cout << "projectile manager : creating singleton." << std::endl;
        _singleton =  new Projectile_manager;
      }

    return _singleton;
  }

void Projectile_manager::kill ()
  {
    if (NULL != _singleton)
      {
        delete _singleton;
        _singleton = NULL;
      }
  }

void Projectile_manager::freeze()
{
    list<std::tr1::shared_ptr<Projectile> >::const_iterator lit(m_enemyProjectiles.begin());
    for(; lit!=m_enemyProjectiles.end(); lit++)
    {
        (*lit)->freeze();//Dessine les projectiles ennemi
    }
}

void Projectile_manager::unfreeze()
{
    list<std::tr1::shared_ptr<Projectile> >::const_iterator lit(m_enemyProjectiles.begin());
    for(; lit!=m_enemyProjectiles.end(); lit++)
    {
        (*lit)->unfreeze();//Dessine les projectiles ennemi
    }
}
