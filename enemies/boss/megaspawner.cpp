#include "megaspawner.h"

using namespace sf;

Megaspawner::Megaspawner(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
    Boss(1000, 5, 10000, 3, 3, "images/megaspawner/mega.png", Vector2f(500, 200), "boss", "roundtrip", 1, 20, 2, player, player2, false, "megaspawner")
{
    m_animated->Scale(0.8,0.8);
    /*
    *image = image_manager::getInstance()->getImage("images/megaspawner/mega.png");/
    m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth()/4, image->GetHeight()) ));
    m_anim.PushFrame(Frame(image, sf::Rect<int>(image->GetWidth()/4, 0, image->GetWidth()/2, image->GetHeight()) ));
    m_anim.PushFrame(Frame(image, sf::Rect<int>(image->GetWidth()/2, 0, image->GetWidth()*3/4, image->GetHeight()) ));
    m_anim.PushFrame(Frame(image, sf::Rect<int>(image->GetWidth()*3/4, 0, image->GetWidth(), image->GetHeight()) ));
    m_animated->SetFrame(0);

    m_animated->SetAnim(&m_anim);
    m_animated->SetPosition(m_position.x, m_position.y);*/

}

Megaspawner::~Megaspawner()
{
    //dtor
}



void Megaspawner::fire()
{
    std::list<std::tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
    for(; lit != m_adds.end(); lit++)
    {

    }
}

IntRect Megaspawner::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x+50;
    boundingBox.Right = boundingBox.Left + image->GetWidth()/3;
    boundingBox.Top = m_position.y ;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight()/1.5;

    return boundingBox;
}

IntRect Megaspawner::getWeakBox()
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

void Megaspawner::move()
{

}
