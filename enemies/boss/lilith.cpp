#include "lilith.h"

using namespace std;
using namespace sf;

Lilith::Lilith(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2) :
            Boss(1000, 5, 10000, 5, 5, "images/enemy2.png", Vector2f(500, 500), "boss", "don't move", 1, 50, 2, player, player2, 1),
            m_level(level)
{
    image = new Image();
    *image = image_manager::getInstance()->getImage(filepath);
    timer.start();
    timerMove.start();

    m_animated = new Animated;
    m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth(), image->GetHeight()) ));
    m_animated->SetAnim(&m_anim);
    m_animated->Play();
    m_animated->SetPosition(position.x, position.y);

    this->createAdd();
}

Lilith::~Lilith()
{
    delete m_animated;
    if (image!= NULL )
    {
        delete image;
    }
    delete m_name;
}

void Lilith::createAdd()
{
    switch(m_level)
    {
        case 1:
            tr1::shared_ptr<Adds> add(new Adds(200, 5, 1000, 5, 5, "images/enemy.png", Vector2f(m_position.x, m_position.y + image->GetHeight()), "add", "follow", 1, 5, 5, false, player, player2));
            m_adds.push_back(add);
            tr1::shared_ptr<Adds> add2(new Adds(200, 5, 1000, 5, 5, "images/enemy.png", Vector2f(m_position.x + image->GetWidth() /1.5, m_position.y + image->GetHeight()), "add", "follow", 1, 5, 5, false, player, player2));
            m_adds.push_back(add2);
            break;
    }
}

IntRect Lilith::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x + image->GetWidth()/4;
    boundingBox.Right = boundingBox.Left + image->GetWidth()-image->GetWidth()/2;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight();

    return boundingBox;
}


IntRect Lilith::getWeakBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x + image->GetWidth()/2;
    boundingBox.Right = boundingBox.Left + image->GetWidth()/2;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight()/2;

    return boundingBox;
}

void Lilith::draw()
{
    app.Draw(*m_animated);
    list<tr1::shared_ptr<Adds> >::const_iterator li(m_adds.begin());
    for(; li!= m_adds.end(); li++)
    {
        (*li)->draw();
    }
}

void Lilith::move()
{
    list<tr1::shared_ptr<Adds> >::const_iterator li(m_adds.begin());
    for(; li!= m_adds.end(); li++)
    {
        (*li)->follow();
    }
}
