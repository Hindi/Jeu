#include "player.h"

using namespace std;
using namespace sf;

Player::Player(int life, Vector2f position, RenderWindow &app, image_manager &imageManager, Projectile_manager &projectile_manager):
            Unit(life, 10, 10, position, app, projectile_manager),
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
            m_imageManager(imageManager),
            m_coefSpeed(40),
            m_damages(5),
            m_lives(4)
{
    timer.start();
    image = new Image;
    *image = imageManager.getImage("images/player.png");
    m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0,m_frameWidth,m_frameHeight) ));
    m_anim.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth, 0, 2*m_frameWidth,m_frameHeight) ));
    m_anim.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth*2, 0, 3*m_frameWidth,m_frameHeight) ));
    m_anim.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth*3, 0, 4*m_frameWidth,m_frameHeight) ));
    m_anim.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth*4, 0, 5*m_frameWidth,m_frameHeight) ));

    goRight.PushFrame(Frame(image, sf::Rect<int>(0,m_frameHeight,m_frameWidth,m_frameHeight*2) ));
    goRight.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth,m_frameHeight, 2*m_frameWidth,m_frameHeight*2) ));
    goRight.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth*2,m_frameHeight, 3*m_frameWidth,m_frameHeight*2) ));
    goRight.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth*3,m_frameHeight, 4*m_frameWidth,m_frameHeight*2) ));
    goRight.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth*4,m_frameHeight, 5*m_frameWidth,m_frameHeight*2) ));

    goLeft.PushFrame(Frame(image, sf::Rect<int>(0,m_frameHeight*2,m_frameWidth,m_frameHeight*3) ));
    goLeft.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth,m_frameHeight*2, 2*m_frameWidth,m_frameHeight*3) ));
    goLeft.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth*2,m_frameHeight*2, 3*m_frameWidth,m_frameHeight*3) ));
    goLeft.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth*3,m_frameHeight*2, 4*m_frameWidth,m_frameHeight*3) ));
    goLeft.PushFrame(Frame(image, sf::Rect<int>(m_frameWidth*4,m_frameHeight*2, 5*m_frameWidth,m_frameHeight*3) ));

    m_animated = new Animated(&m_anim, false, true, 0.5);
    m_animated->SetPosition(m_position.x, m_position.y);
}

Player::~Player()
{
    list<Projectile*>::const_iterator lit(m_projectiles.begin());
    for(; lit!=m_projectiles.end(); lit++)
    {
        delete *lit;
    }
    m_projectiles.clear();
    delete image;
}


Sprite* Player::getSprite()
{
    //Retourne la référence de sprite
    return m_animated;
}

int Player::getLives()
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

void Player::fire()
{
    if(canFire(lastShot, timer, fireRate))//Création des projectiles
    {
        //*******************************
        //On créé le projectile du centre
        //*******************************

        Vector2f positionProjectile = m_position;
        positionProjectile.x += 39;
        positionProjectile.y -= 30;
        const string filepath = "images/projectile.png";
        projectile = new Projectile(filepath, positionProjectile, Vector2f(0, -30), m_coefSpeed, m_imageManager);
        projectile->SetPosition(positionProjectile);
        m_projectile_manager.addPlayerProjectile(projectile);
        if(secondary)//Si les armes secondaires sont activées
        {
            //*******************************
            //On créé le projectile de droite
            //*******************************
            positionProjectile.x += 19;
            positionProjectile.y += 25;
            projectileDroite = new Projectile(filepath, positionProjectile, Vector2f(0, -30), m_coefSpeed, m_imageManager);
            projectileDroite->SetPosition(positionProjectile);
            m_projectile_manager.addPlayerProjectile(projectileDroite);
            //*******************************
            //On créé le projectile de gauche
            //*******************************
            positionProjectile.x -= 38;
            projectileDroite = new Projectile(filepath, positionProjectile, Vector2f(0, -30), m_coefSpeed, m_imageManager);
            projectileDroite->SetPosition(positionProjectile);
            m_projectile_manager.addPlayerProjectile(projectileDroite);
        }
        if(third)
        {
            //***************************************
            //On créé le projectile de extreme droite
            //***************************************
            positionProjectile.x += 68;
            positionProjectile.y += 5;
            projectileExtremeGauche = new Projectile(filepath, positionProjectile, Vector2f(0, -30), m_coefSpeed, m_imageManager);
            projectileExtremeGauche->SetPosition(positionProjectile);
            m_projectile_manager.addPlayerProjectile(projectileExtremeGauche);
            //***************************************
            //On créé le projectile de extreme gauche
            //***************************************
            positionProjectile.x -= 90;
            projectileExtremeDroite = new Projectile(filepath, positionProjectile, Vector2f(0, -30), m_coefSpeed, m_imageManager);
            projectileExtremeDroite->SetPosition(positionProjectile);
            m_projectile_manager.addPlayerProjectile(projectileExtremeDroite);
        }
        lastShot = timer.getTime();
    }
}

list<Projectile*>* Player::getProjectiles()
{
    //Retourne la référence de la liste des projectiles
    return &m_projectiles;
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

double Player::getScore()
{
    return m_score;
}

void Player::loseLive()
{
    Vector2f position(500, 1000);
    m_position = position;
    m_lives -= 1;
    lostLife = true;
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
        m_animated->SetLoop(true);
    }
    m_position.y -= m_ySpeed * m_app.GetFrameTime() * coefSpeed;
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
    m_position.y += m_ySpeed * m_app.GetFrameTime() * coefSpeed;
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
    }
    m_position.x -= m_xSpeed * m_app.GetFrameTime() * coefSpeed;
    m_animated->SetPosition(m_position.x, m_position.y);
    if(m_animated->IsPaused())
        m_animated->Play();
}

void Player::moveRight()
{
    if (m_animated->GetAnim() != &goRight)
    {
        m_animated->SetLoop(false);
        m_animated->SetAnim(&goRight);
    }
    m_position.x += m_xSpeed * m_app.GetFrameTime() * coefSpeed;
    m_animated->SetPosition(m_position.x, m_position.y);
    if(m_animated->IsPaused())
        m_animated->Play();
}

void Player::dontMove()
{
    if (m_animated->GetAnim() != &m_anim)
    {
        m_animated->SetAnim(&m_anim)
;        m_animated->SetLoop(true);
    }
    if(m_animated->IsPaused())
        m_animated->Play();
}

void Player::draw()
{
    m_animated->anim(m_app.GetFrameTime());
    m_app.Draw(*m_animated);
}

int Player::getPosition(int axis)
{
    if(axis == 0)
        return m_position.x;
    else
        return m_position.y;
}

void Player::setPosition(int axis, int value)
{
    if(axis == 1)
        m_position.x = value;
    else
        m_position.y = value;
}

int Player::getDamages()
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
