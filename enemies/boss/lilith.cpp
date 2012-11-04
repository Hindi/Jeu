#include "lilith.h"

using namespace std;
using namespace sf;

Lilith::Lilith(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2) :
            Boss(10, 5, 10000, 5, 5, "images/enemy2.png", Vector2f(500, 500), "boss", "don't move", 1, 50, 2, player, player2, true),
            m_level(1),
            m_position(Vector2f(500,500))
{
    image = new Image();
    *image = image_manager::getInstance()->getImage("images/enemy2.png");
    timer.start();
    timerMove.start();

    m_animated = new Animated;
    m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth(), image->GetHeight()) ));
    m_animated->SetAnim(&m_anim);
    m_animated->Play();
    m_animated->SetPosition(500, 500);
}

Lilith::~Lilith()
{

}

void Lilith::addsMove()
{
    this->follow();
}

