#include "boss.h"

using namespace std;
using namespace sf;

Boss::Boss(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, std::tr1::shared_ptr<Player> player,
           std::tr1::shared_ptr<Player> player2, short level) :
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, false, player, player2),
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

Boss::~Boss()
{
    delete m_animated;
    if (image!= NULL )
    {
        delete image;
    }
    delete m_name;
}

void Boss::createAdd()
{
    switch(m_level)
    {
        case 1:
            tr1::shared_ptr<Adds> add(new Adds(200, 5, 1000, 5, 5, "images/enemy.png", Vector2f(200, 200), "add", "follow", 1, 5, 5, false, player, player2));
            m_adds.push_back(add);
            tr1::shared_ptr<Adds> add2(add);
            m_adds.push_back(add2);
            break;
    }
}

IntRect Boss::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x + image->GetWidth()/4;
    boundingBox.Right = boundingBox.Left + image->GetWidth()-image->GetWidth()/2;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight();

    return boundingBox;
}


IntRect Boss::getWeakBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x + image->GetWidth()/2;
    boundingBox.Right = boundingBox.Left + image->GetWidth()/2;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight()/2;

    return boundingBox;
}

void Boss::draw()
{
    app.Draw(*m_animated);
    list<tr1::shared_ptr<Adds> >::const_iterator li(m_adds.begin());
    for(; li!= m_adds.end(); li++)
    {
        (*li)->draw();
    }
}
