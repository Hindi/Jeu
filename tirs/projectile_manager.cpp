#include "projectile_manager.h"

using namespace std;
using namespace sf;

Projectile_manager::Projectile_manager():
            m_app(app)
{

}

Projectile_manager::~Projectile_manager()
{
    list<Projectile*>::iterator lit(m_enemyProjectiles.begin());
    for(;lit != m_enemyProjectiles.end(); lit++)
    {
        delete *lit;
    }
    list<Projectile*>::iterator li(m_playerProjectiles.begin());
    for(;li != m_playerProjectiles.end(); li++)
    {
        delete *li;
    }
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
    double elapsedTime = m_app.GetFrameTime();

    //****************************************
    //On bouge les projectiles ennemis
    //****************************************
    if(this->haveEnemyProjectilesInProgress())
    {
        list<Projectile*>::iterator lit(m_enemyProjectiles.begin());
        for(; lit!=m_enemyProjectiles.end(); )//On parcours la liste des projectiles ennemi
        {
            Vector2f speed((*lit)->getSpeed(0)*elapsedTime*(*lit)->getCoefSpeed(),((*lit)->getSpeed(2))*elapsedTime*(*lit)->getCoefSpeed());//On calcule le vecteur vitesse
            (*lit)->Move(speed);//On déplace chacun des projectile
            Vector2f position((*lit)->getPosition());
            position.x += speed.x;
            position.y += speed.y;
            (*lit)->setPosition(position);
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
        list<Projectile*>::iterator li(m_playerProjectiles.begin());
        for(; li!=m_playerProjectiles.end(); )//On parcours la liste des projectiles joueur
        {
            //cout << (*li)->getSpeed(0) << " " << (*li)->getSpeed(1) << endl;
            Vector2f speed((*li)->getSpeed(0)*elapsedTime*(*li)->getCoefSpeed(),((*li)->getSpeed(2))*elapsedTime*(*li)->getCoefSpeed());//On calcule le vecteur vitesse
            //(*li)->Move(speed);//On déplace chacun des projectile
            Vector2f position((*li)->GetPosition());
            position.x += speed.x;
            position.y += speed.y;
            (*li)->SetPosition(position);
            (*li)->setPosition(position);
            if((*li)->GetPosition().y  < 0)//On vérifie sa position
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
        list<Projectile*>::const_iterator lit(m_enemyProjectiles.begin());
        for(; lit!=m_enemyProjectiles.end(); lit++)
        {
            m_app.Draw(**lit);//Dessine les projectiles ennemi
        }
    }
    if(this->havePlayerProjectilesInProgress())
    {
        list<Projectile*>::const_iterator li(m_playerProjectiles.begin());
        for(; li!=m_playerProjectiles.end(); li++)
        {
            m_app.Draw(**li);//Dessine les projectiles du joueur
        }
    }


}

void Projectile_manager::addEnemyProjectile(Projectile* projectile)
{
    m_enemyProjectiles.push_back(projectile);
}

void Projectile_manager::addPlayerProjectile(Projectile* projectile)
{
    m_playerProjectiles.push_back(projectile);
}


list<Projectile*>* Projectile_manager::getEnemyProjectiles()
{
    return &m_enemyProjectiles;
}

list<Projectile*>* Projectile_manager::getPlayerProjectiles()
{
    return &m_playerProjectiles;
}

void Projectile_manager::animationFollow()
{
    list<Projectile*>::const_iterator lit(m_enemyProjectiles.begin());
    for(; lit != m_enemyProjectiles.end(); lit++)
    {

    }
}
