#include "enemy.h"

using namespace std;
using namespace sf;


Enemy::Enemy(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, const char* const type, const std::string &moveMethod, int moveValue, const int coefSpeed,
             const int firerate, bool spawner, std::tr1::shared_ptr<Player> externPlayer, std::tr1::shared_ptr<Player> externPlayer2, bool allowTeleport):
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
            player(externPlayer), player2(externPlayer2),
            allowTeleport(allowTeleport),
            teleporting(false)
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
    if(strcmp(m_type, "spawn") == 0)
    {
        m_anim.PushFrame(Frame(image, sf::Rect<int>(image->GetWidth()/2, 0, image->GetWidth(), image->GetHeight()) ));
        m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth()/2, image->GetHeight()) ));
        m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth()/2, image->GetHeight()) ));
        m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth()/2, image->GetHeight()) ));
        m_animated->Scale(0.75, 0.75);
        m_animated->SetLoop(true);
    }
    else
        m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth(), image->GetHeight()) ));

    m_animated->Play();
    m_animated->SetAnim(&m_anim);
    m_animated->SetFrameTime(0.5);
    m_animated->SetPosition(m_position.x, m_position.y);

    if(allowTeleport)
        teleportTimer.start();

}

Enemy::~Enemy()
{
    this->reset();
}


void Enemy::changeImage(const string &filepath, int frameNumber)
{
    m_anim.reset();
    *image = image_manager::getInstance()->getImage(filepath);
    for(int i=0; i < frameNumber; i++)
    {
        m_anim.PushFrame(Frame(image, sf::Rect<int>(image->GetWidth()*i/frameNumber, 0, image->GetWidth()*(i+1)/frameNumber, image->GetHeight())));
    }
    m_animated->SetAnim(&m_anim);
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
    else if(m_position.x < -50 || m_position.x > 1366 || m_position.y < -250|| m_position.y > 900)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//********************************
//****Fonctions de déplacement****
//********************************
void Enemy::roundtripLeft()
{
    int distance(100);
    int tempo;
    tempo = distance/(m_xSpeed*coefSpeed*0.1);
    cout << tempo << endl;
    if(strcmp(direction.data(), "left") == 0)
        moveRight();
    else
        moveLeft();
    if(savedTimerMove > tempo)
    {
        if(strcmp(direction.data(), "left") == 0)
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

void Enemy::roundtripRight()
{
    int distance(100);
    int tempo;
    tempo = distance/(m_xSpeed*coefSpeed*0.1);
    if(strcmp(direction.data(), "left") == 0)
        moveLeft();
    else
        moveRight();
    if(savedTimerMove > tempo)
    {
        if(strcmp(direction.data(), "left") == 0)
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
    const char* buffer = m_moveMethod.data();
    if(strcmp(buffer, "roundtripLeft") == 0)
        this->roundtripLeft();
    else if(strcmp(buffer, "roundtripRight") == 0)
        this->roundtripRight();
    else if(strcmp(buffer, "left") == 0)
        this->moveLeft();
    else if(strcmp(buffer, "right") == 0)
        this->moveRight();
    else if(strcmp(buffer, "down") == 0)
        this->moveDown();
    else if(strcmp(buffer, "up") == 0)
        this->moveUp();
    else if(strcmp(buffer, "don'tmove") == 0)
        this->dontMove();
    else if(strcmp(buffer, "spawnMove") == 0)
        this->spawnMove();
    else if(strcmp(buffer, "follow") == 0)
        this->follow();
    else
        this->moveDown();

    delete buffer;
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

void Enemy::follow()
{

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

void Enemy::setPosition(Vector2f position)
{
    m_position = position;
}

//********************************
//**Fin fonctions de déplacement**
//********************************

void Enemy::draw()
{
    m_animated->anim(app.GetFrameTime());
    if(teleporting)
    {
        if(teleportFrame % 2 == 1)
            app.Draw(*m_animated);
        teleportFrame++;
    }
    else
    {
        app.Draw(*m_animated);
    }
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
void Enemy::fire()
{

}

void Enemy::fireFocus()
{
    Vector2f distance1, distance2, position1, position2;
    int indistinctness = rand() % 100 + 1;
    int norm;
    //On récupère les positions des deux joueurs
    position1 = player->getPosition();
    position2 = player2->getPosition();

    //On calcule leur deux normes
    distance1.x = (position1.x - m_position.x);
    distance1.y = (position1.y - m_position.y);
    int norm1 = sqrt(distance1.x*distance1.x + distance1.y*distance1.y);

    distance2.x = (position2.x - m_position.x);
    distance2.y = (position2.y - m_position.y);
    int norm2 = sqrt(distance2.x*distance2.x + distance2.y*distance2.y);

    if(norm1 > norm2)
    {
        distance1 = distance2;
        norm = norm2;
    }
    else
        norm = norm1;

    //On calcule la vitesse du projectile
    distance1.x = ((distance1.x+indistinctness)/norm)*projectileSpeed;
    distance1.y = ((distance1.y+indistinctness)/norm)*projectileSpeed;

    //La position de départ du projectile
    Vector2f positionProjectile(m_position);
    positionProjectile.y += image->GetHeight()-10;
    const string filepath = "images/projectile4.png";

    std::tr1::shared_ptr<Projectile> projectile(new Projectile(filepath, positionProjectile, distance1, m_coefSpeed, true));
    projectile->setPosition(positionProjectile);

    //On le rajoute à la liste des projectiles gérée par le projectile manager.
    Projectile_manager::getInstance()->addEnemyProjectile(projectile);
    lastShot = timer.getTime();
}

void Enemy::fireCircle()
{
    //La position de départ du projectile
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

    //On le rajoute à la liste des projectiles gérée par le projectile manager.
    lastShot = timer.getTime();
}

void Enemy::fireCircle2()
{
    //La position de départ du projectile
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

    std::tr1::shared_ptr<Projectile> projectile24(new Projectile(filepath, positionProjectile, Vector2f(16, 2), m_coefSpeed));
    projectile24->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile24);
    std::tr1::shared_ptr<Projectile> projectile25(new Projectile(filepath, positionProjectile, Vector2f(-16, 2), m_coefSpeed));
    projectile25->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile25);
    std::tr1::shared_ptr<Projectile> projectile26(new Projectile(filepath, positionProjectile, Vector2f(2, 16), m_coefSpeed));
    projectile26->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile26);
    std::tr1::shared_ptr<Projectile> projectile27(new Projectile(filepath, positionProjectile, Vector2f(8, 13), m_coefSpeed));
    projectile27->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile27);
    std::tr1::shared_ptr<Projectile> projectile28(new Projectile(filepath, positionProjectile, Vector2f(-8, 13), m_coefSpeed));
    projectile28->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile28);
    std::tr1::shared_ptr<Projectile> projectile29(new Projectile(filepath, positionProjectile, Vector2f(13, -8), m_coefSpeed));
    projectile29->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile29);
    std::tr1::shared_ptr<Projectile> projectile30(new Projectile(filepath, positionProjectile, Vector2f(13, 8), m_coefSpeed));
    projectile30->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile30);
    std::tr1::shared_ptr<Projectile> projectile31(new Projectile(filepath, positionProjectile, Vector2f(-13, -8), m_coefSpeed));
    projectile31->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile31);

    std::tr1::shared_ptr<Projectile> projectile32(new Projectile(filepath, positionProjectile, Vector2f(9, 12), m_coefSpeed));
    projectile32->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile32);
    std::tr1::shared_ptr<Projectile> projectile33(new Projectile(filepath, positionProjectile, Vector2f(-9, 12), m_coefSpeed));
    projectile33->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile33);
    std::tr1::shared_ptr<Projectile> projectile34(new Projectile(filepath, positionProjectile, Vector2f(12, -9), m_coefSpeed));
    projectile34->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile34);
    std::tr1::shared_ptr<Projectile> projectile35(new Projectile(filepath, positionProjectile, Vector2f(12, 9), m_coefSpeed));
    projectile35->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile35);

    std::tr1::shared_ptr<Projectile> projectile36(new Projectile(filepath, positionProjectile, Vector2f(10, 11), m_coefSpeed));
    projectile36->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile36);
    std::tr1::shared_ptr<Projectile> projectile37(new Projectile(filepath, positionProjectile, Vector2f(-10, 11), m_coefSpeed));
    projectile37->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile37);
    std::tr1::shared_ptr<Projectile> projectile38(new Projectile(filepath, positionProjectile, Vector2f(11, -10), m_coefSpeed));
    projectile38->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile38);
    std::tr1::shared_ptr<Projectile> projectile39(new Projectile(filepath, positionProjectile, Vector2f(11, 10), m_coefSpeed));
    projectile39->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile39);
    std::tr1::shared_ptr<Projectile> projectile40(new Projectile(filepath, positionProjectile, Vector2f(-11, -10), m_coefSpeed));
    projectile40->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile40);

    std::tr1::shared_ptr<Projectile> projectile41(new Projectile(filepath, positionProjectile, Vector2f(2, 17), m_coefSpeed));
    projectile41->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile41);
    std::tr1::shared_ptr<Projectile> projectile42(new Projectile(filepath, positionProjectile, Vector2f(-2, 17), m_coefSpeed));
    projectile42->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile42);
    std::tr1::shared_ptr<Projectile> projectile43(new Projectile(filepath, positionProjectile, Vector2f(17, -2), m_coefSpeed));
    projectile43->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile43);
    std::tr1::shared_ptr<Projectile> projectile44(new Projectile(filepath, positionProjectile, Vector2f(17, 2), m_coefSpeed));
    projectile44->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile44);
    std::tr1::shared_ptr<Projectile> projectile45(new Projectile(filepath, positionProjectile, Vector2f(-17, -2), m_coefSpeed));
    projectile45->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile45);


    //On le rajoute à la liste des projectiles gérée par le projectile manager.
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

void Enemy::fireSpawner()
{
    const string filepath = "images/projectile.png";
    Vector2f positionProjectile(m_position);
    positionProjectile.x += -10;
    positionProjectile.y += 65;
    std::tr1::shared_ptr<Projectile> projectile(new Projectile(filepath, positionProjectile, Vector2f(0, 10), m_coefSpeed));
    projectile->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile);
    positionProjectile.x += 50;
    std::tr1::shared_ptr<Projectile> projectile2(new Projectile(filepath, positionProjectile, Vector2f(0, 10), m_coefSpeed));
    projectile2->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile2);
}

list<std::tr1::shared_ptr<Projectile> >* Enemy::getProjectiles()
{
    //Retourne la référence de la liste des projectiles
    return &m_projectiles;
}

bool Enemy::canFire()
{
    //Créé un interval de temps entre chaque tir
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

const char* Enemy::getType()
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
    boundingBox.Left = m_position.x;
    boundingBox.Right = boundingBox.Left + image->GetWidth()/m_anim.Size();
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight();

    return boundingBox;
}

IntRect Enemy::getWeakBox()
{

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

Vector2f Enemy::getSize()
{
    return Vector2f(image->GetWidth(), image->GetHeight());
}

void Enemy::reset()
{
    m_projectiles.clear();
    m_vitesses.clear();
    if(m_animated != NULL)
        delete m_animated;
    if (image!= NULL )
        delete image;
    delete m_type;
}

bool Enemy::canTeleport()
{
    if(allowTeleport && teleportTimer.getTime() > 3)
    {
        return true;
    }
    return false;
}

void Enemy::setTeleporting(bool state)
{
    teleporting = state;
}


bool Enemy::readyToTeleport()
{
    if(teleportTimer.getTime() > 10)
        return true;
    return false;
}

void Enemy::teleport()
{
    teleporting = false;
    teleportTimer.reinitialize();
    teleportFrame = 0;
    Vector2f position(rand()%800+1, 200 + rand()%300+1);
    m_animated->SetPosition(Vector2f(position));
    m_position = position;
}

void Enemy::changeMoveMethod(std::string method)
{
    m_moveMethod = method;
}

bool Enemy::needRespawn()
{
    return false;
}
