#include "octopus.h"

using namespace std;
using namespace sf;

Octopus::Octopus(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
            Boss(1000, 5, 10000, 3, 3, "images/octopus/Yeux.png", Vector2f(250, -200), "boss", "roundtrip", 1, 20, 2, player, player2, false, "octopus")
{
    timerMove.start();
    timerFire1.start();
    timerFire2.start();
    lastTentaMove = 0;

    short numberFrame(10);
    imageLaser = new Image();
    *imageLaser = image_manager::getInstance()->getImage("images/octopus/lasor.png");

    for(int i=0; i<numberFrame; i++)
    {
        anim.PushFrame(Frame(imageLaser, sf::Rect<int>(imageLaser->GetWidth()*i/numberFrame, 0, imageLaser->GetWidth()*(i+1)/numberFrame, imageLaser->GetHeight())));
    }
    animated = new Animated(&anim, true, true, 0.01);
    animated2 = new Animated(&anim, true, true, 0.01);
    animated3 = new Animated(&anim, true, true, 0.01);
    animated4 = new Animated(&anim, true, true, 0.01);
    animated5 = new Animated(&anim, true, true, 0.01);
    animated6 = new Animated(&anim, true, true, 0.01);
    animated7 = new Animated(&anim, true, true, 0.01);

    Vector2f position(-100, -100);
    animated->SetPosition(position);
    animated2->SetPosition(position);
    animated3->SetPosition(position);
    animated4->SetPosition(position);
    animated5->SetPosition(position);
    animated6->SetPosition(position);
    animated7->SetPosition(position);


    imageTentacle = new Image();
    *imageTentacle = image_manager::getInstance()->getImage("images/octopus/Protections.png");
    animTentacle.PushFrame(Frame(imageTentacle,sf::Rect<int>(0, 0, imageTentacle->GetWidth()/2, imageTentacle->GetHeight())));
    animTentacle.PushFrame(Frame(imageTentacle,sf::Rect<int>(imageTentacle->GetWidth()/2, 0, imageTentacle->GetWidth(), imageTentacle->GetHeight())));
    animatedTentacle = new Animated(&animTentacle, true, true, 0.01);
    Vector2f positionProtection(m_position.x -100, m_position.y + 120);
    animatedTentacle->SetPosition(positionProtection);


    *image = image_manager::getInstance()->getImage("images/octopus/Yeux.png");
    m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth()/3, image->GetHeight()) ));
    m_anim.PushFrame(Frame(image, sf::Rect<int>(image->GetWidth()/3, 0, image->GetWidth()*2/3, image->GetHeight()) ));
    m_anim.PushFrame(Frame(image, sf::Rect<int>(image->GetWidth()*2/3, 0, image->GetWidth(), image->GetHeight()) ));
    m_animated->SetFrame(0);

    m_animated->SetAnim(&m_anim);
    m_animated->SetPosition(m_position.x, m_position.y);
}

Octopus::~Octopus()
{
    //dtor
}

void Octopus::fire()
{
    if(!m_adds.empty())
    {
        if(timerFireTime.getTime() > 2 && timerFireTime.getTime() < 2.05 && !lasorUp)
        {
            Vector2f position(m_position.x+100, m_position.y+200);
            animated->SetPosition(position);
            lasorUp = true;
        }
        else if(timerFireTime.getTime() > 2.05 && timerFireTime.getTime() < 2.1)
        {
            Vector2f position(m_position.x+100, m_position.y+298);
            animated2->SetPosition(position);
        }
        else if(timerFireTime.getTime() > 2.1 && timerFireTime.getTime() < 2.15)
        {
            cout << "huk" << endl;
            Vector2f position(m_position.x+100, m_position.y+298+98);
            animated3->SetPosition(position);
        }
        else if(timerFireTime.getTime() > 2.15 && timerFireTime.getTime() < 2.2)
        {
            Vector2f position(m_position.x+100, m_position.y+298+196);
            animated4->SetPosition(position);
        }
        else if(timerFireTime.getTime() > 2.2 && timerFireTime.getTime() < 2.25)
        {
            Vector2f position(m_position.x+100, m_position.y+298+196+98);
            animated5->SetPosition(position);
        }
        else if(timerFireTime.getTime() > 2.25 && timerFireTime.getTime() < 2.3)
        {
            Vector2f position(m_position.x+100, m_position.y+298+2*196);
            animated6->SetPosition(position);
        }
        else if(timerFireTime.getTime() > 2.3 && timerFireTime.getTime() < 2.35)
        {
            Vector2f position(m_position.x+100, m_position.y+298+2*196+98);
            animated7->SetPosition(position);
        }
        else if(timerFireTime.getTime() > 7)
        {
            Vector2f position(-100, -100);
            animated->SetPosition(position);
            animated2->SetPosition(position);
            animated3->SetPosition(position);
            animated4->SetPosition(position);
            animated5->SetPosition(position);
            timerFireTime.reinitialize();
            lasorUp = false;
        }
    }
}

IntRect Octopus::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x+50;
    boundingBox.Right = boundingBox.Left + image->GetWidth()/3;
    boundingBox.Top = m_position.y ;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight()/1.5;

    return boundingBox;
}

IntRect Octopus::getWeakBox()
{
    IntRect boundingBox;
    if(m_adds.empty())
    {
        boundingBox.Left = m_position.x;
        boundingBox.Right = boundingBox.Left + image->GetWidth()/3;
        boundingBox.Top = m_position.y + image->GetHeight();
        boundingBox.Bottom = m_position.y + image->GetHeight()+20;
    }
    else
    {
        boundingBox.Left = 0;
        boundingBox.Right = 0;
        boundingBox.Top = 0;
        boundingBox.Bottom = 0;
    }

    return boundingBox;
}
void Octopus::move()
{
    if(timerMove.getTime() < 0.5)
    {
        this->moveDown();
        this->follow();
    }
    else if(timerMove.getTime() - lastTentaMove > 0.1 && !m_adds.empty())
    {
        list<tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
        Vector2f position;
        float y=0;
        for(; lit != m_adds.end(); lit++)
        {
            position.y = (*lit)->getPosition().y;
            y = position.y / 100;
            float t = timerMove.getTime() + (*lit)->getRelativePosition().x;
            position.x = m_position.x + (*lit)->getRelativePosition().x + (pow(2,position.y/95) + 20) * ( 0.6*sin(y-t) + 0.5*sin(1.7*(y-t)) + 0.3*sin(2.4*(y-t)) + 0.4*sin(4.1*(y-t)));
            (*lit)->getAnimation()->SetPosition(position);
            (*lit)->setPosition(position);
        }

        lastTentaMove = timerMove.getTime();
    }

    //On change l'image du bout de tentacule
    list<tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
    list<tr1::shared_ptr<Adds> >::const_iterator litref1(m_adds.begin());
    list<tr1::shared_ptr<Adds> >::const_iterator litref2(m_adds.begin());
    int yref1(0), yref2(0);
    if(!m_adds.empty())
    {
        for(; lit != m_adds.end(); lit++)
        {
            if((*lit)->getPosition().y > yref1 && (*lit)->getPosition().x < 600)
            {
                yref1 = (*lit)->getPosition().y;
                litref1 = lit;
            }
            if((*lit)->getPosition().y > yref2 && (*lit)->getPosition().x > 600)
            {
                yref2 = (*lit)->getPosition().y;
                litref2 = lit;
            }
        }
        if(!yref1 == 0)
        {
            (*litref1)->changeImage("images/octopus/TentaculeBout.png", 1);
            if(timerFire1.getTime() > 2)
            {
                timerFire1.reinitialize();
                (*litref1)->fireCircle();
            }
        }
        if(!yref2 == 0)
        {
            (*litref2)->changeImage("images/octopus/TentaculeBout.png", 1);
            if(timerFire2.getTime() > 2)
            {
                timerFire2.reinitialize();
                (*litref2)->fireCircle();
            }

        }
    }

    if(lasorUp && !m_adds.empty())
    {
        m_animated->SetFrame(1);
        animated->anim(app.GetFrameTime());
        animated2->anim(app.GetFrameTime());
        animated3->anim(app.GetFrameTime());
        animated4->anim(app.GetFrameTime());
        animated5->anim(app.GetFrameTime());
        animated6->anim(app.GetFrameTime());
        animated7->anim(app.GetFrameTime());
        app.Draw(*animated7);
        app.Draw(*animated6);
        app.Draw(*animated5);
        app.Draw(*animated4);
        app.Draw(*animated3);
        app.Draw(*animated2);
        app.Draw(*animated);
    }
    else if(m_adds.empty())
    {
        m_animated->SetFrame(3);
        timerTentacles.start();
    }
    else
        m_animated->SetFrame(2);
    if(this->needRespawn())
    {
        m_coefSpeed++;
        Vector2f position(-140, 90);
        Vector2f absolutePosition;
        for(int i=0; i < 15; i++)
        {
            absolutePosition.x = m_position.x + position.x;
            absolutePosition.y = m_position.y + position.y;
            Population::getInstance()->createAdd(100, 5, 50, 5, 5, "images/octopus/Tentacule.png", position, absolutePosition, "add", "follow" ,1, m_coefSpeed, 1, false, player, player2);
            cout << absolutePosition.y << endl;
            position.y += 30;
        }
        position.x = 350;
        position.y = 90;
        for(int i=0; i < 15; i++)
        {
            absolutePosition.x = m_position.x + position.x;
            absolutePosition.y = m_position.y + position.y;
            Population::getInstance()->createAdd(100, 5, 50, 5, 5, "images/octopus/Tentacule.png", position, absolutePosition, "add", "follow" ,1, m_coefSpeed, 1, false, player, player2);
            position.y += 30;
        }
    }
}

void Octopus::follow()
{
    if(!m_adds.empty())
    {
        list<tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
        for(; lit != m_adds.end(); lit++)
        {
            Vector2f position(m_position.x +(*lit)->getRelativePosition().x, m_position.y + (*lit)->getRelativePosition().y);
            (*lit)->getAnimation()->SetPosition(position);
            (*lit)->setPosition(position);
        }
    }
}

void Octopus::draw()
{
    app.Draw(*m_animated);
    app.Draw(*animatedTentacle);
    if(laserFocusing)
    {
        //On dessine le focus
        m_animatedFocus->anim(app.GetFrameTime());
        app.Draw(*m_animatedFocus);
    }
    this->drawHealthBar();

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

bool Octopus::needRespawn()
{
    if(timerTentacles.getTime() > 5)
    {
        timerTentacles.reinitialize();
        timerTentacles.pause();
    }
}
