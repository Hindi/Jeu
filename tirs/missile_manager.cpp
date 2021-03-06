#include "missile_manager.h"

using namespace sf;
using namespace std;

Missile_manager *Missile_manager::_singleton= NULL;

Missile_manager::Missile_manager():
        nombreMissiles(7),
        fireDelay(1)
{
    timerCreate.start();
    int i;
    for(i=0; i < nombreMissiles; i++)
    {
        boolPositionLibres[i] = true;
    }
    positionsLibres[0] = Vector2f(+85, -20);
    positionsLibres[1] = Vector2f(-5, -20);
    positionsLibres[2] = Vector2f(-25, +40);
    positionsLibres[3] = Vector2f(90, +85);
    positionsLibres[4] = Vector2f(-5, +90);
    positionsLibres[5] = Vector2f(45, +110);
    positionsLibres[6] = Vector2f(+110, +40);
}

Missile_manager::~Missile_manager()
{
    this->reset();
}


bool Missile_manager::haveMissilesInProgress()
{
    //V�rifie si des projectiles sont en cours de d�placement
    if(m_missiles.empty())
        return false;
    else
        return true;
}

void Missile_manager::createMissile()
{
    if(m_missiles.size() < nombreMissiles && timerCreate.getTime() > fireDelay && player->getMissile())//On v�rifie le nombre de missile et le d�lais de respawn
    {
        Vector2f adapt;
        int i=0;
        for(i; i < nombreMissiles; i++)
        {
            if(boolPositionLibres[i])
            {
                adapt = positionsLibres[i];
                boolPositionLibres[i] = false;
                break;
            }
        }
        Vector2f missilePosition(player->getPosition(0)+adapt.x, player->getPosition(1)+adapt.y);
        std::tr1::shared_ptr<Missile> missile(new Missile("images/projectile2.png", missilePosition, 10, 50, i));
        missile->SetPosition(missilePosition);

        this->addMissile(missile);
        timerCreate.reinitialize();
    }
}

void Missile_manager::moveMissile()
{
    double elapsedTime = app.GetFrameTime();
    list<std::tr1::shared_ptr<Missile> >::iterator lit(m_missiles.begin());

     list<tr1::shared_ptr<Enemy> >::const_iterator li(Population::getInstance()->getPopulation()->begin());
    //***********************************************
    //Cette fonction g�re le d�placement des missiles
    //***********************************************
    if(this->haveMissilesInProgress() && (Population::getInstance()->haveEnnemyInProgress())) //Si des ennemis sont en vie
    {
        for(lit=m_missiles.begin(); lit != m_missiles.end();)
        {
            Vector2f positionMissile = (*lit)->getPosition();//On r�cup�re la position du missile
            Vector2f positionEnnemy, diff;//On cr�� nos conteneurs pour la position ennemis et la diff�rence entre position ennemy et missile
            int currentNorm, norm=10000;

            //*****************************************************************
            //Dans cette partie on calcule quel ennemi chaque missile va cibler
            //*****************************************************************
            for(;li != Population::getInstance()->getPopulation()->end(); li++)//On parcours la liste des ennemis
            {
                diff.x = (*li)->getPositionAxis(0)-positionMissile.x;//on calcul le vecteur diff�rence entre les position ennemis et missile
                diff.y = (*li)->getPositionAxis(1)-positionMissile.y;
                currentNorm = sqrt(diff.x*diff.x + diff.y*diff.y);//On calcule la norme du vecteur
                if(norm > currentNorm && currentNorm < 1500)//Si l'ennemi en cours est plus pr�s du missile que l'ennemi pr�c�dent
                {
                    norm = currentNorm;//On sauvegarde la norme pour pouvoir la comparer � l'ennemi suivant
                    positionEnnemy.x = (*li)->getPositionAxis(0);//On sauvegarde la position de l'ennemi proche
                    positionEnnemy.y = (*li)->getPositionAxis(1);
                    break;
                }
            }

            //***************************************************************
            //Dans cette partie on calcule la vitesse pour atteindre l'ennemi
            //***************************************************************

            if((norm < 500 && !(*lit)->getFocus()) ||(*lit)->getFocus())
            {
                (*lit)->setFocus(true);
                Vector2f distance;
                float facteurSpeed = (*lit)->getSpeed()*elapsedTime*(*lit)->getCoefSpeed();
                distance.x = (positionEnnemy.x - positionMissile.x);
                distance.y = (positionEnnemy.y - positionMissile.y);
                norm = sqrt(distance.x*distance.x + distance.y*distance.y);
                if(norm==0)
                    norm=1;
                distance.x = ((distance.x)/norm)*facteurSpeed;
                distance.y = (distance.y/norm)*facteurSpeed;
                //***********************************
                //On d�place finalement le projectile
                //***********************************
                (*lit)->setPosition(Vector2f(positionMissile.x + distance.x, positionMissile.y + distance.y));
                (*lit)->Move(distance);
            }
            lit++;
        }
    }
}

void Missile_manager::drawMissile()
{
    if(this->haveMissilesInProgress())
    {
        list<std::tr1::shared_ptr<Missile> >::const_iterator lit(m_missiles.begin());
        for(; lit!=m_missiles.end(); lit++)
        {
            app.Draw(**lit);//Dessine les projectiles ennemi
        }

    }
}

void Missile_manager::manage()
{
    this->createMissile();
    this->moveMissile();
    this->followPlayer();
    this->drawMissile();
}

void Missile_manager::addMissile(std::tr1::shared_ptr<Missile> missile)
{
    m_missiles.push_back(missile);
}


list<std::tr1::shared_ptr<Missile> >* Missile_manager::getMissile()
{
    return &m_missiles;
}

void Missile_manager::followPlayer()
{
    list<std::tr1::shared_ptr<Missile> >::iterator lit(m_missiles.begin());
    for(; lit != m_missiles.end(); lit++)
    {
        double elapsedTime = app.GetFrameTime();
        if(!(*lit)->getFocus() || (!Population::getInstance()->haveEnnemyInProgress()))
        {
            //***************************************
            //On initialise les variables de position
            //***************************************
            Vector2f positionMissile((*lit)->getPosition());//Position actuelle du missile
            int ringPosition((*lit)->getListPosition());//Sa place dans le cercle autour du joueur
            Vector2f positionInitiale(this->positionsLibres[ringPosition]);//Les coordonn�es associ�es � cette place (en relatif par rapport � la position du joueur)
            Vector2f positionPlayer(player->getPosition(0), player->getPosition(1));//Position actuelle du joueur
            double coefSpeed((*lit)->getCoefSpeed()*elapsedTime*10);
            if(positionMissile.x != positionPlayer.x + positionInitiale.x || positionMissile.y != positionPlayer.y + positionInitiale.y)
            {
                //**********************************
                //On calcule la vitesse pour revenir
                //**********************************
                Vector2f diff(positionPlayer.x+positionInitiale.x - positionMissile.x, positionPlayer.y+positionInitiale.y - positionMissile.y);
                int norm = sqrt(diff.x*diff.x + diff.y*diff.y);
                (*lit)->setPosition(Vector2f(positionPlayer.x+positionInitiale.x, positionPlayer.y+positionInitiale.y));
                (*lit)->Move(diff);
            }
        }
    }
}


void Missile_manager::setPositionLibre(int position, bool mode)
{
    boolPositionLibres[position] = mode;
}

Missile_manager* Missile_manager::getInstance()
  {
    if (NULL == _singleton)
      {
        std::cout << "missile manager : creating singleton." << std::endl;
        _singleton =  new Missile_manager;
      }

    return _singleton;
  }

void Missile_manager::kill ()
  {
    if (NULL != _singleton)
      {
        delete _singleton;
        _singleton = NULL;
      }
  }

void Missile_manager::setPlayer(std::tr1::shared_ptr<Player> externPlayer)
{
    player = externPlayer;
}

void Missile_manager::reset()
{
    m_missiles.clear();
}
