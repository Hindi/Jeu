#include "enemy.h"

using namespace std;
using namespace sf;


Enemy::Enemy(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, const char* const type, const char* const moveMethod, int moveValue, const int coefSpeed, const int firerate, bool spawner, Player &externPlayer):
            Unit(life, xSpeed,ySpeed, position),
            direction("null"),
            lastShot(0),
            m_scoreExplosion(scoreExplosion),
            m_scoreHit(scoreHit),
            projectileSpeed(10),
            m_coefSpeed(coefSpeed),
            m_fireRate(firerate),
            savedTimerMove(0),
            m_type(type),
            m_moveMethod(moveMethod),
            m_moveValue(moveValue),
            m_spawner(spawner),
            lastSpawn(0),
            m_spawnRate(3),
            player(externPlayer)
{
    m_animated = new Animated;
    timer.start();
    timerMove.start();
    if(m_spawner)
    {
        timerSpawn.start();
    }
    image = new Image();
    *image = image_manager::getInstance()->getImage(filepath);
    m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth(), image->GetHeight()) ));

    m_animated->SetAnim(&m_anim);
    m_animated->Pause();
    m_animated->SetLoop(true);
    m_animated->SetFrameTime(0.2f);
    m_animated->SetPosition(m_position.x, m_position.y);

}

Enemy::~Enemy()
{
    m_projectiles.clear();
    m_vitesses.clear();
    delete m_animated;
    if (image!= NULL )
    {
        delete image;
    }
    delete direction;
    delete m_type;
    delete m_moveMethod;
}

Sprite* Enemy::getSprite()
{
    return &sprite;
}

short Enemy::getScoreHit() const
{
    return m_scoreHit;
}

unsigned short Enemy::getScoreExplosion() const
{
    return m_scoreExplosion;
}

void Enemy::recieveDamages(int dmg)
{
    m_life -= dmg;
    if(m_life < 0)
    {
        m_life = 0;
    }
}

bool Enemy::isDead()
{
    if(m_life == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//********************************
//****Fonctions de d�placement****
//********************************
void Enemy::roundTrip()
{
    if(strcmp(direction, "left") == 0)
        moveLeft();
    else
        moveRight();
    if(savedTimerMove > m_moveValue)
    {
        if(strcmp(direction, "left") == 0)
        {
            direction = "right";
            timerMove.reinitialize();
        }
        else
        {
            direction = "left";
            timerMove.reinitialize();
        }
    }
    savedTimerMove = timerMove.getTime();
}

void Enemy::moveUp()
{
    if (m_animated->GetAnim() != &m_anim)
    {
        m_animated->SetAnim(&m_anim);
        m_animated->SetLoop(true);
    }
    m_position.y -= m_ySpeed * app.GetFrameTime() * coefSpeed;
    m_animated->SetPosition(m_position.x, m_position.y);
    if(m_animated->IsPaused())
        m_animated->Play();
}

void Enemy::moveDown()
{
    if (m_animated->GetAnim() != &m_anim)
    {
        m_animated->SetAnim(&m_anim);
        m_animated->SetLoop(true);
    }
    m_position.y += m_ySpeed * app.GetFrameTime() * coefSpeed;
    m_animated->SetPosition(m_position.x, m_position.y);
    if(m_animated->IsPaused())
        m_animated->Play();
}

void Enemy::moveLeft()
{
    if (m_animated->GetAnim() != &m_anim)
    {
        m_animated->SetAnim(&m_anim);
        m_animated->SetLoop(false);
    }
    m_position.x -= m_xSpeed * app.GetFrameTime() * coefSpeed;
    m_animated->SetPosition(m_position.x, m_position.y);
    if(m_animated->IsPaused())
        m_animated->Play();
}

void Enemy::moveRight()
{
    if (m_animated->GetAnim() != &m_anim)
    {
        m_animated->SetLoop(false);
        m_animated->SetAnim(&m_anim);
    }
    m_position.x += m_xSpeed * app.GetFrameTime() * coefSpeed;
    m_animated->SetPosition(m_position.x, m_position.y);
    if(m_animated->IsPaused())
        m_animated->Play();
}

void Enemy::dontMove()
{
    if (m_animated->GetAnim() != &m_anim)
    {
        m_animated->SetAnim(&m_anim);
        m_animated->SetLoop(true);
    }
    if(m_animated->IsPaused())
        m_animated->Play();
}


void Enemy::move()
{
    if(strcmp(m_moveMethod, "roundtrip") == 0)
        this->roundTrip();
    else if(strcmp(m_moveMethod, "left") == 0)
        this->moveLeft();
    else if(strcmp(m_moveMethod, "right") == 0)
        this->moveRight();
    else if(strcmp(m_moveMethod, "down") == 0)
        this->moveDown();
    else if(strcmp(m_moveMethod, "up") == 0)
        this->moveUp();
    else if(strcmp(m_moveMethod, "don't move") == 0)
        this->dontMove();
    else if(strcmp(m_moveMethod, "spawnMove") == 0)
        this->spawnMove();
    else
        this->moveDown();
}

void Enemy::spawnMove()
{
    Vector2f speed;
    if(timerMove.getTime() > m_moveValue)
    {
        m_angleMove = rand() % 360 + 1;
        timerMove.reinitialize();
    }
    speed.x = app.GetFrameTime() * m_xSpeed * m_coefSpeed * cos(m_angleMove);
    speed.y = app.GetFrameTime() * m_ySpeed * m_coefSpeed * sin(m_angleMove);
    m_position += speed;
    m_animated->SetPosition(m_position);
}

int Enemy::getPositionAxis(int axis)
{
    if(axis == 0)
        return m_position.x;
    else
        return m_position.y;
}


Vector2f Enemy::getPosition()
{
    return m_position;
}

void Enemy::setPosition(int axis, int value)
{
    if(axis == 1)
        m_position.x = value;
    else
        m_position.y = value;
}

//********************************
//**Fin fonctions de d�placement**
//********************************

void Enemy::draw()
{
    //animation->draw(app);
    app.Draw(*m_animated);
}


//********************************
//**********Animations************
//********************************

Animated* Enemy::getAnimation()
{
    return m_animated;
}

Animated* Enemy::getAnimationExplosion()
{
    return m_animatedExplosion;
}

//********************************
//********Fin animations**********
//********************************

//********************************
//**********Projectiles***********
//********************************

void Enemy::fireFocus()
{
    Vector2f distance;
    int indistinctness = rand() % 100 + 1;
    //On r�cup�re les coordonn�es du joueur
    playerPosition.x = player.getPosition(0);
    playerPosition.y = player.getPosition(1);
    distance.x = (playerPosition.x - m_position.x);
    distance.y = (playerPosition.y - m_position.y);
    int norm = sqrt(distance.x*distance.x + distance.y*distance.y);
    //On calcule la vitesse du projectile
    distance.x = ((distance.x+indistinctness)/norm)*projectileSpeed;
    distance.y = ((distance.y+indistinctness)/norm)*projectileSpeed;
    //La position de d�part du projectile
    Vector2f positionProjectile(m_position);
    positionProjectile.x += (image->GetWidth()/2)-18;
    positionProjectile.y += image->GetHeight()-20;
    const string filepath = "images/projectile3.png";
    std::tr1::shared_ptr<Projectile> projectile(new Projectile(filepath, positionProjectile, Vector2f(distance.x, distance.y), m_coefSpeed, true));
    projectile->setPosition(positionProjectile);
    //On le rajoute � la liste des projectiles g�r�e par le projectile manager.
    Projectile_manager::getInstance()->addEnemyProjectile(projectile);
    lastShot = timer.getTime();
}

void Enemy::fireCircle()
{
    //La position de d�part du projectile
    Vector2f positionProjectile(m_position);
    positionProjectile.x += (image->GetWidth()/2)-20;
    positionProjectile.y += image->GetHeight()/2-20;
    const string filepath = "images/projectile2.png";

    std::tr1::shared_ptr<Projectile> projectile(new Projectile(filepath, positionProjectile, Vector2f(16, 0), m_coefSpeed));
    projectile->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile);
    std::tr1::shared_ptr<Projectile> projectile1(new Projectile(filepath, positionProjectile, Vector2f(-16, 0), m_coefSpeed));
    projectile1->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile1);
    std::tr1::shared_ptr<Projectile> projectile2(new Projectile(filepath, positionProjectile, Vector2f(0, 16), m_coefSpeed));
    projectile2->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile2);
    std::tr1::shared_ptr<Projectile> projectile3(new Projectile(filepath, positionProjectile, Vector2f(0, -16), m_coefSpeed));
    projectile3->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile3);
    std::tr1::shared_ptr<Projectile> projectile4(new Projectile(filepath, positionProjectile, Vector2f(11, 11), m_coefSpeed));
    projectile4->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile4);
    std::tr1::shared_ptr<Projectile> projectile5(new Projectile(filepath, positionProjectile, Vector2f(-11, 11), m_coefSpeed));
    projectile5->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile5);
    std::tr1::shared_ptr<Projectile> projectile6(new Projectile(filepath, positionProjectile, Vector2f(11, -11), m_coefSpeed));
    projectile6->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile6);
    std::tr1::shared_ptr<Projectile> projectile7(new Projectile(filepath, positionProjectile, Vector2f(-11, -11), m_coefSpeed));
    projectile7->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile7);

    std::tr1::shared_ptr<Projectile> projectile8(new Projectile(filepath, positionProjectile, Vector2f(-7, -14), m_coefSpeed));
    projectile8->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile8);
    std::tr1::shared_ptr<Projectile> projectile9(new Projectile(filepath, positionProjectile, Vector2f(-5, -15), m_coefSpeed));
    projectile9->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile9);
    std::tr1::shared_ptr<Projectile> projectile10(new Projectile(filepath, positionProjectile, Vector2f(7, -14), m_coefSpeed));
    projectile10->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile10);
    std::tr1::shared_ptr<Projectile> projectile11(new Projectile(filepath, positionProjectile, Vector2f(5, -15), m_coefSpeed));
    projectile11->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile11);
    std::tr1::shared_ptr<Projectile> projectile12(new Projectile(filepath, positionProjectile, Vector2f(7, 14), m_coefSpeed));
    projectile12->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile12);
    std::tr1::shared_ptr<Projectile> projectile13(new Projectile(filepath, positionProjectile, Vector2f(5, 15), m_coefSpeed));
    projectile13->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile13);
    std::tr1::shared_ptr<Projectile> projectile14(new Projectile(filepath, positionProjectile, Vector2f(-7, 14), m_coefSpeed));
    projectile14->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile14);
    std::tr1::shared_ptr<Projectile> projectile15(new Projectile(filepath, positionProjectile, Vector2f(-5, 15), m_coefSpeed));
    projectile15->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile15);

    std::tr1::shared_ptr<Projectile> projectile16(new Projectile(filepath, positionProjectile, Vector2f(-14, -7), m_coefSpeed));
    projectile16->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile16);
    std::tr1::shared_ptr<Projectile> projectile17(new Projectile(filepath, positionProjectile, Vector2f(-15, -5), m_coefSpeed));
    projectile17->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile17);
    std::tr1::shared_ptr<Projectile> projectile18(new Projectile(filepath, positionProjectile, Vector2f(14, -7), m_coefSpeed));
    projectile18->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile18);
    std::tr1::shared_ptr<Projectile> projectile19(new Projectile(filepath, positionProjectile, Vector2f(15, -5), m_coefSpeed));
    projectile19->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile19);
    std::tr1::shared_ptr<Projectile> projectile20(new Projectile(filepath, positionProjectile, Vector2f(14, 7), m_coefSpeed));
    projectile20->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile20);
    std::tr1::shared_ptr<Projectile> projectile21(new Projectile(filepath, positionProjectile, Vector2f(15, 5), m_coefSpeed));
    projectile21->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile21);
    std::tr1::shared_ptr<Projectile> projectile22(new Projectile(filepath, positionProjectile, Vector2f(-14, 7), m_coefSpeed));
    projectile22->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile22);
    std::tr1::shared_ptr<Projectile> projectile23(new Projectile(filepath, positionProjectile, Vector2f(-15, 5), m_coefSpeed));
    projectile23->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile23);

    //On le rajoute � la liste des projectiles g�r�e par le projectile manager.
    lastShot = timer.getTime();
}

void Enemy::VFire()
{
    Vector2f positionProjectile(m_position);
    positionProjectile.x += (image->GetWidth()/2)-20;
    positionProjectile.y += image->GetHeight()/2-20;
    const string filepath = "images/projectile2.png";

    for(int i=0; i<=16; i+=2)
    {
        std::tr1::shared_ptr<Projectile> projectile(new Projectile(filepath, positionProjectile, Vector2f(-16 + i, i), m_coefSpeed));
        projectile->setPosition(positionProjectile);
        Projectile_manager::getInstance()->addEnemyProjectile(projectile);

        std::tr1::shared_ptr<Projectile> projectile1(new Projectile(filepath, positionProjectile, Vector2f(16 - i, i), m_coefSpeed));
        projectile1->setPosition(positionProjectile);
        Projectile_manager::getInstance()->addEnemyProjectile(projectile1);
    }
}

list<std::tr1::shared_ptr<Projectile> >* Enemy::getProjectiles()
{
    //Retourne la r�f�rence de la liste des projectiles
    return &m_projectiles;
}

bool Enemy::canFire()
{
    //Cr�� un interval de temps entre chaque tir
    if(timer.getTime() - lastShot > m_fireRate)
    {
        timer.reinitialize();
        return true;
    }
    else
        return false;
}

//********************************
//*********Fin projectiles********
//********************************

const char* const  Enemy::getType()
{
    return m_type;
}

void Enemy::startTimer()
{
    timer.start();
}

void Enemy::pauseTimer()
{
    timer.pause();
    timerSpawn.pause();
    timerMove.pause();
}


IntRect Enemy::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x + image->GetWidth()/4;
    boundingBox.Right = boundingBox.Left + image->GetWidth()-image->GetWidth()/2;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight();

    return boundingBox;
}

bool Enemy::isSpawner()
{
    if(m_spawner)
        return true;
    else
        return false;
}

float Enemy::getSpawnTime()
{
    return timerSpawn.getTime();
}

float Enemy::getLastSpawnTime()
{
    return lastSpawn;
}

void Enemy::upDateLastSpawnTime()
{
    lastSpawn = timerSpawn.getTime();
}

short Enemy::getSpawnRate() const
{
    return m_spawnRate;
}


void Enemy::freeze()
{
    m_coefSpeed /= 3;
}

void Enemy::unfreeze()
{
    m_coefSpeed *= 3;
}
