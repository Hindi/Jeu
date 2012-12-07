#include "boss.h"

using namespace std;
using namespace sf;

Boss::Boss(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, char* type, const std::string moveMethod, int moveValue, const int coefSpeed, const int firerate, std::tr1::shared_ptr<Player> player,
           std::tr1::shared_ptr<Player> player2, bool allowTeleport, const char* name) :
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, false, player, player2, allowTeleport),
            startedLasor(false),
            laserRate(5),
            laserFocusing(false),
            startLife(life),
            m_name(name)
{
    timerLaser.start();
    timerFireTime.start();
    timerAddMove.start();
    imageFocus = new Image();
    *imageFocus = image_manager::getInstance()->getImage("images/concentrateurEnergie.png");
    int i=0;
    for(; i < 10; i++)
    {
        m_animFocus.PushFrame(Frame(imageFocus, sf::Rect<int>(imageFocus->GetWidth()*i/10, 0, imageFocus->GetWidth()*(i+1)/10, imageFocus->GetHeight()) ));
    }
    m_animatedFocus = new Animated;
    m_animatedFocus->SetAnim(&m_animFocus);
    m_animatedFocus->SetLoop(true);
    m_animatedFocus->SetFrameTime(0.05f);
    m_animatedFocus->Scale(2,2);
    m_animatedFocus->Pause();
    m_animatedFocus->SetPosition(m_position.x, m_position.y);

    imageHealthBackground = new Image;
    *imageHealthBackground = image_manager::getInstance()->getImage("images/lilith/barre_vie_fade.png");
    imageHealthBar = new Image;
    *imageHealthBar = image_manager::getInstance()->getImage("images/lilith/barre_vie.png");

    spriteHealthBackground.SetImage(*imageHealthBackground);
    spriteHealthBackground.SetPosition(300, 50);
    spriteHealthBar.SetImage(*imageHealthBar);
    spriteHealthBar.SetPosition(300, 50);


    vuuuBuffer = sound_manager::getInstance()->getBuffer("son/vuuuu.ogg");
    vuuuSound.SetBuffer(vuuuBuffer);
    vuuuSound.SetLoop(false);
    vuuuSound.SetPitch(0.53f);
    vuuuSound.SetVolume(100.f);
}

Boss::~Boss()
{
    delete m_name;
    delete m_animatedFocus;
    delete imageFocus;
    if(vuuuSound.GetStatus() == sf::Sound::Playing)
        vuuuSound.Stop();
    m_adds.clear();
}

void Boss::draw()
{
    if(teleporting)
    {
        if(teleportFrame % 2 == 1)
            app.Draw(*m_animated);
        teleportFrame++;
    }
    else
        app.Draw(*m_animated);
    if(laserFocusing)
    {
        //On dessine le focus
        m_animatedFocus->anim(app.GetFrameTime());
        app.Draw(*m_animatedFocus);
    }
    this->drawHealthBar();

    if(!m_adds.empty())
    {
        list<tr1::shared_ptr<Adds> >::iterator lit(m_adds.begin());
        for(; lit != m_adds.end();)
        {
            if((*lit)->isDead())
            {
                lit = m_adds.erase(lit);
            }
            else
                lit++;
        }
    }

}


Vector2f Boss::getPosition()
{
    return m_position;
}

void Boss::setTeleporting(bool state)
{
    teleporting = state;

    if(!m_adds.empty())
    {
        list<tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
        for(; lit != m_adds.end(); lit++)
        {
            (*lit)->setTeleporting(true);
        }
    }
}

void Boss::firinhMahLasor(int fireTime)
{
    if(!startedLasor && timerLaser.getTime() > laserRate && !teleporting)
    {
        timerAddMove.reinitialize();
        startedLasor = true;
        loop = 0;
        firinh = false;
    }
    if(startedLasor && timerAddMove.getTime() < 10)
    {
        if(vuuuSound.GetStatus() != sf::Sound::Playing)
            vuuuSound.Play();
        int speed, sign;

        if(!m_adds.empty())
        {
            list<tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
            for(; lit != m_adds.end(); lit++)
            {
                sign = ((*lit)->getPosition().x - image->GetWidth()/3 - m_position.x);
                speed = (sign / fabs(sign))*21;
                (*lit)->horizontalMove(speed);
            }
            if(timerAddMove.getTime() > 2)
                laserFocusing = true;
        }
    }
    if(laserFocusing)
    {
        if(m_animatedFocus->IsPaused())
                m_animatedFocus->Play();//On relance l'animation
        //On récupère le numéro de l'image qui est affichée
        int currentFrame = m_animatedFocus->GetCurrentFrame();
        int nombreFrame = m_animFocus.Size();
        Vector2f position(m_position.x + image->GetWidth()/2 - imageFocus->GetWidth()/(nombreFrame*2)-50 ,m_position.y+ image->GetHeight()/2 + imageFocus->GetHeight()/2-90);
        //On positionne l'animation sur l'ennemi qui a explose
        m_animatedFocus->SetPosition(position);
        //Si l'image actuelle correspond à la dernière image de l'animation
        if(currentFrame == m_animatedFocus->GetAnim()->Size()-1 && !firinh)
        {
            loop++;
            if(loop > 15)
            {
                laserFocusing = false;//On arrête le focus
                firinh = true;
                timerFireTime.reinitialize();
                loop = 0;
            }
        }
        if(firinh && timerAddMove.getTime() > 6)
        {
            position.x = m_position.x + image->GetWidth()/2 - 20;
            position.y = m_position.y + image->GetHeight()/2 + 40;
            std::tr1::shared_ptr<Projectile> projectile(new Projectile("images/projectile.png", position, Vector2f(0, 15), m_coefSpeed));
            projectile->setPosition(position);
            Projectile_manager::getInstance()->addEnemyProjectile(projectile);
            laserFocusing = false;
            if(vuuuSound.GetStatus() == sf::Sound::Playing)
                vuuuSound.Stop();
            if(timerFireTime.getTime() > fireTime)
            {
                cout << "huk" << endl;
                startedLasor = false;
                timerLaser.reinitialize();
                firinh = false;
            }
        }
    }
}

void Boss::pushAdd(std::tr1::shared_ptr<Adds> add)
{
    m_adds.push_back(add);
}

void Boss::follow()
{
    list<tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
    for(; lit != m_adds.end(); lit++)
    {
        Vector2f position(m_position.x +(*lit)->getRelativePosition().x, m_position.y + (*lit)->getRelativePosition().y);
        (*lit)->getAnimation()->SetPosition(position);
        (*lit)->setPosition(position);
    }
}

bool Boss::canFire()
{
    return true;
}

bool Boss::canTeleport()
{
    if(allowTeleport && teleportTimer.getTime() > 15  && !startedLasor)
    {
        return true;
    }
    return false;
}

void Boss::teleport()
{
    teleporting = false;

    if(!m_adds.empty())
    {
        list<tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
        for(; lit != m_adds.end(); lit++)
        {
            (*lit)->setTeleporting(false);
        }
    }
    teleportTimer.reinitialize();
    teleportFrame = 0;
    Vector2f position(100+rand()%700+1, 200 + rand()%150+1);
    m_animated->SetPosition(Vector2f(position));
    m_position = position;
}

void Boss::drawHealthBar()
{
    float health = (float)m_life/(float)startLife;
    spriteHealthBar.SetSubRect(IntRect(0, 0, imageHealthBar->GetWidth()*(health), imageHealthBar->GetHeight()));
    app.Draw(spriteHealthBackground);
    app.Draw(spriteHealthBar);
}

const char* Boss::getName()
{
    return m_name;
}

bool Boss::needRespawn()
{
    return false;
}
