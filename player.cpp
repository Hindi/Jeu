#include "player.h"

using namespace std;
using namespace sf;

Player::Player(short id, int life, Vector2f position):
            Unit(life, 10, 10, position),
            max_lives(3),
            m_frameWidth(118),
            m_frameHeight(93),
            fireRate(0.1),
            lastShot(0),
            m_score(0),
            lostLife(false),
            missiles(false),
            third(false),
            secondary(false),
            m_coefSpeed(40),
            m_damages(5),
            m_lives(99),
            m_armor(3),
            killThemAll(true)
{
    timer.start();
    timerArmor.start();
    timerKillThemAll.start();
    image = new Image;
    int start = 0;
    *image = image_manager::getInstance()->getImage("images/player.png");
    if(id == 1)
    {
        start = m_frameHeight;
        m_position.x += -100;
    }
    m_anim.PushFrame(Frame(image, sf::Rect<int>(0, start,m_frameWidth,m_frameHeight+start)));

    goRight.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth,start,m_frameWidth*2,m_frameHeight+start)));
    goRight.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth*3,start,m_frameWidth*4,m_frameHeight+start)));

    goLeft.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth*2,start,m_frameWidth*3,m_frameHeight+start)));
    goLeft.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth*4,start,m_frameWidth*5,m_frameHeight+start)));

    m_animated = new Animated(&m_anim, false, false, 0.4);
    m_animated->SetPosition(m_position.x, m_position.y);

    imageReactor = new Image;
    *imageReactor = image_manager::getInstance()->getImage("images/reacteur.png");
    m_animReactor.PushFrame(Frame(imageReactor, sf::Rect<int>(0, 0, 40, 100)));
    m_animReactor.PushFrame(Frame(imageReactor, sf::Rect<int>(40, 0, 80, 100)));
    m_animReactor.PushFrame(Frame(imageReactor, sf::Rect<int>(80, 0, 120, 100)));
    m_animReactor.PushFrame(Frame(imageReactor, sf::Rect<int>(120, 0, 160, 100)));
    m_animReactor.PushFrame(Frame(imageReactor, sf::Rect<int>(160, 0, 200, 100)));

    m_animatedReactor = new Animated(&m_animReactor, true, true, 0.1);
    m_animatedReactor->SetPosition(m_position.x, m_position.y);
}

Player::~Player()
{
    delete image;
    delete imageReactor;
    delete m_animatedReactor;
    delete m_animated;
}


Sprite* Player::getSprite()
{
    //Retourne la référence de sprite
    return m_animated;
}

short Player::getLives()
{
    //Retourne le nombre de vies restantes
    return m_lives;
}

IntRect Player::GetBoundingBox()
{
    //Récupère le rectangle de collision pour le joueur
    IntRect boundingBox;
    boundingBox.Left = (int)m_position.x;
    boundingBox.Right = boundingBox.Left + m_frameWidth;
    boundingBox.Top = (int)m_position.y;
    boundingBox.Bottom = boundingBox.Top + m_frameHeight;

    return boundingBox;
}

void Player::fire0()
{
    if(canFire(lastShot, timer, fireRate))//Création des projectiles
    {
        //*******************************
        //On créé le projectile du centre
        //*******************************

        Vector2f positionProjectile = m_position;
        positionProjectile.x += 39;
        positionProjectile.y -= 30;
        string filepath;
        Vector2f vitesse(0, -30);
        if(Cheat_manager::getInstance()->getSopalintMode())
        {
            filepath = "images/projectile5.png";
            vitesse.x = -15;
        }
        else
            filepath = "images/projectile.png";
        std::tr1::shared_ptr<Projectile> projectile(new Projectile(filepath, positionProjectile, Vector2f(0, -30), m_coefSpeed));
        projectile->setPosition(positionProjectile);
        Projectile_manager::getInstance()->addPlayerProjectile(projectile);
        if(secondary)//Si les armes secondaires sont activées
        {
            //*******************************
            //On créé le projectile de droite
            //*******************************
            positionProjectile.x += 19;
            positionProjectile.y += 25;
            std::tr1::shared_ptr<Projectile> projectileDroite(new Projectile(filepath, positionProjectile, Vector2f(0, -30), m_coefSpeed));
            projectileDroite->setPosition(positionProjectile);
            Projectile_manager::getInstance()->addPlayerProjectile(projectileDroite);
            //*******************************
            //On créé le projectile de gauche
            //*******************************
            positionProjectile.x -= 38;
            std::tr1::shared_ptr<Projectile> projectileGauche(new Projectile(filepath, positionProjectile, Vector2f(0, -30), m_coefSpeed));
            projectileGauche->setPosition(positionProjectile);
            Projectile_manager::getInstance()->addPlayerProjectile(projectileGauche);
        }
        if(third)
        {
            //***************************************
            //On créé le projectile de extreme droite
            //***************************************
            positionProjectile.x += 68;
            positionProjectile.y += 5;
            std::tr1::shared_ptr<Projectile> projectileExtremeGauche(new Projectile(filepath, positionProjectile, Vector2f(0, -30), m_coefSpeed));
            projectileExtremeGauche->setPosition(positionProjectile);
            Projectile_manager::getInstance()->addPlayerProjectile(projectileExtremeGauche);
            //***************************************
            //On créé le projectile de extreme gauche
            //***************************************
            positionProjectile.x -= 90;
            std::tr1::shared_ptr<Projectile> projectileExtremeDroite(new Projectile(filepath, positionProjectile, Vector2f(0, -30), m_coefSpeed));
            projectileExtremeDroite->setPosition(positionProjectile);
            Projectile_manager::getInstance()->addPlayerProjectile(projectileExtremeDroite);
        }
        lastShot = timer.getTime();
    }
}

void Player::fire1()
{
    if(canFire(lastShot, timer, fireRate))
    {
        Vector2f positionProjectile = m_position;
        positionProjectile.x += 39;
        positionProjectile.y -= 30;
        string filepath;
        Vector2f vitesse(0, -30), vitesse21(10, -30), vitesse22(-10, -30), vitesse31(-30, -30), vitesse32(30, -30);
        if(Cheat_manager::getInstance()->getSopalintMode())
        {
            filepath = "images/projectile5.png";
            vitesse.y = -15;
            vitesse21.x = -5;
            vitesse21.y = -15;
            vitesse31.x = 10;
            vitesse31.y = -15;
            vitesse22.x =  5;
            vitesse22.y = -15;
            vitesse32.x = -10;
            vitesse32.y = -15;
        }
        else
        {
            filepath = "images/projectile.png";
        }
        std::tr1::shared_ptr<Projectile> projectile(new Projectile(filepath, positionProjectile, vitesse, m_coefSpeed));
        projectile->setPosition(positionProjectile);
        Projectile_manager::getInstance()->addPlayerProjectile(projectile);

        if(secondary)
        {
             //*******************************
            //On créé le projectile de droite
            //*******************************
            positionProjectile.x += 19;
            positionProjectile.y += 25;
            std::tr1::shared_ptr<Projectile> projectileDroite(new Projectile(filepath, positionProjectile, vitesse21, m_coefSpeed));
            projectileDroite->rotate(-15);
            projectileDroite->setPosition(positionProjectile);
            Projectile_manager::getInstance()->addPlayerProjectile(projectileDroite);
            //*******************************
            //On créé le projectile de gauche
            //*******************************
            positionProjectile.x -= 38;
            std::tr1::shared_ptr<Projectile> projectileGauche(new Projectile(filepath, positionProjectile, vitesse22, m_coefSpeed));
            projectileGauche->setPosition(positionProjectile);
            projectileGauche->rotate(15);
            Projectile_manager::getInstance()->addPlayerProjectile(projectileGauche);
        }
        if(third)
        {

            //***************************************
            //On créé le projectile de extreme droite
            //***************************************
            positionProjectile.x += 80;
            positionProjectile.y += 5;
            std::tr1::shared_ptr<Projectile> projectileExtremeGauche(new Projectile(filepath, positionProjectile, vitesse32, m_coefSpeed));
            projectileExtremeGauche->setPosition(positionProjectile);
            projectileExtremeGauche->rotate(-45);
            Projectile_manager::getInstance()->addPlayerProjectile(projectileExtremeGauche);
            //***************************************
            //On créé le projectile de extreme gauche
            //***************************************
            positionProjectile.y += 25;
            positionProjectile.x -= 115;
            std::tr1::shared_ptr<Projectile> projectileExtremeDroite(new Projectile(filepath, positionProjectile, vitesse31, m_coefSpeed));
            projectileExtremeDroite->setPosition(positionProjectile);
            projectileExtremeDroite->rotate(45);
            Projectile_manager::getInstance()->addPlayerProjectile(projectileExtremeDroite);
        }
        lastShot = timer.getTime();
    }
}

bool canFire(float lastShot, Timer &timer, float const fireRate)
{
    //Créé un interval de temps entre chaque tir
    if(timer.getTime() - lastShot > fireRate)
    {
        timer.reinitialize();
        return true;
    }
    else
        return false;
}

void Player::addScore(int score)
{
    m_score += score;
}

int Player::getScore()
{
    return m_score;
}

void Player::loseLive()
{
    if(m_armor > 0)
    {
        if(timerArmor.getTime() > 2)
        {
            m_armor--;
            timerArmor.reinitialize();
        }
    }
    else
    {
        Vector2f position(500, 1000);
        m_position = position;
        m_lives -= 1;
        lostLife = true;
        m_armor = 3;
    }
}

bool Player::getLostlife()
{
    return lostLife;
}

void Player::resetLostLife()
{
    lostLife = false;
}


void Player::moveUp()
{
    if (m_animated->GetAnim() != &m_anim)
    {
        m_animated->SetAnim(&m_anim);
        m_animated->SetLoop(false);
    }
    m_position.y -= m_ySpeed * app.GetFrameTime() * coefSpeed;
    m_animated->SetPosition(m_position.x, m_position.y);
    if(m_animated->IsPaused())
        m_animated->Play();
}

void Player::moveDown()
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

void Player::moveLeft()
{
    if (m_animated->GetAnim() != &goLeft)
    {
        m_animated->SetAnim(&goLeft);
        m_animated->SetLoop(false);
        if(m_animated->IsPaused())
            m_animated->Play();
    }
    else if(m_animated->GetAnim() == &goLeft && m_animated->GetCurrentFrame() == 1)
    {
        m_animated->Pause();
    }
    m_position.x -= m_xSpeed * app.GetFrameTime() * coefSpeed;
    m_animated->SetPosition(m_position.x, m_position.y);
}

void Player::moveRight()
{
    if (m_animated->GetAnim() != &goRight)
    {
        m_animated->SetLoop(false);
        m_animated->SetAnim(&goRight);
        if(m_animated->IsPaused())
            m_animated->Play();
    }
    else if(m_animated->GetAnim() == &goRight && m_animated->GetCurrentFrame() == 1)
    {
        m_animated->Pause();
    }
    m_position.x += m_xSpeed * app.GetFrameTime() * coefSpeed;
    m_animated->SetPosition(m_position.x, m_position.y);
}

void Player::dontMove()
{
    if (m_animated->GetAnim() != &m_anim)
    {
        m_animated->SetAnim(&m_anim);
        m_animated->SetLoop(false);
    }
    if(m_animated->IsPaused())
        m_animated->Play();
}

void Player::draw()
{
    if(Cheat_manager::getInstance()->getSopalintMode())
    {
        m_lives = 3;
        m_armor = 3;
    }
    this->checkKTA();
    if(!this->isDead())
    {
        m_animatedReactor->SetPosition(m_animated->GetPosition().x + m_frameWidth/2.8, m_animated->GetPosition().y + m_frameHeight/1.35);
        m_animatedReactor->anim(app.GetFrameTime());
        app.Draw(*m_animatedReactor);

        m_animated->anim(app.GetFrameTime());
        app.Draw(*m_animated);
    }
    if(Cheat_manager::getInstance()->getSopalintMode() && m_score < 10000)
    {
        m_score = 100000;
    }
}

int Player::getPosition(int axis)
{
    if(axis == 0)
        return m_position.x;
    else
        return m_position.y;

}

Vector2f Player::getPosition()
{
    return m_position;
}

void Player::setPosition(int axis, int value)
{
    if(axis == 1)
        m_position.x = value;
    else
        m_position.y = value;
}

short Player::getDamages() const
{
    return m_damages;
}

bool Player::getMissile()
{
    return missiles;
}

bool Player::getSecondary()
{
    return secondary;
}

bool Player::getThird()
{
    return third;
}

void Player::setMissile(bool mode)
{
    missiles = mode;
}

void Player::setSecondary(bool mode)
{
    secondary = mode;
}

void Player::setThird(bool mode)
{
    third = mode;
}

short Player::getArmor()
{
    return m_armor;
}

bool Player::getPlayerKTA()
{
    return killThemAll;
}

void Player::setPlayerKTA(bool state)
{
    killThemAll = state;
}

void Player::checkKTA()
{
    if(!killThemAll && timerKillThemAll.getTime() > 120)
    {
        killThemAll = true;
        timerKillThemAll.reinitialize();
    }

}

bool Player::isDead()
{
    if(m_lives == 0)
        return true;
    return false;
}
