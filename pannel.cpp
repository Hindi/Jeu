#include "pannel.h"

using namespace std;
using namespace sf;

Pannel::Pannel(RenderWindow &app, const string &filepath, Vector2f position, Player &player): m_app(app), m_scale(1,1), m_player(player)
{
    imagePannel = new Image;
    if(!(*imagePannel).LoadFromFile(filepath))
    {
        cerr << "Image loading failed : " << filepath << endl;
    }
    else
    {
        (*imagePannel).CreateMaskFromColor(Color(255, 0, 255));
        sprite.SetImage(*imagePannel);
        sprite.SetPosition(position);
        sprite.Scale(m_scale);
    }
    imageLife = new Image;
    imageLifeFade = new Image;
    if(!(*imageLife).LoadFromFile("images/Vie.png"))
    {
        cerr << "Image loading failed : Vie.png"<< endl;
    }
    else
    {
        if(!(*imageLifeFade).LoadFromFile("images/Vie-fade.png"))
        {
            cerr << "Image loading failed : Vie-fade.png"<< endl;
        }
        else
        {
            Vector2f position = m_position;
            position.x += 1000;
            position.y += 20;

            spriteLife1.SetPosition(position);
            position.x += 50;
            spriteLife2.SetPosition(position);
            position.x += 50;
            spriteLife3.SetPosition(position);
            int lives = m_player.getLives();
            switch(lives)
            {
                case 1:
                {
                    spriteLife1.SetImage(*imageLifeFade);
                    spriteLife2.SetImage(*imageLifeFade);
                    spriteLife3.SetImage(*imageLifeFade);
                    break;
                }
                case 2:
                {
                    spriteLife1.SetImage(*imageLife);
                    spriteLife2.SetImage(*imageLifeFade);
                    spriteLife3.SetImage(*imageLifeFade);
                    break;
                }
                case 3:
                {
                    spriteLife1.SetImage(*imageLife);
                    spriteLife2.SetImage(*imageLife);
                    spriteLife3.SetImage(*imageLifeFade);
                    break;
                }
                case 4:
                {
                    spriteLife1.SetImage(*imageLife);
                    spriteLife2.SetImage(*imageLife);
                    spriteLife3.SetImage(*imageLife);
                    break;
                }
            }
            m_app.Draw(spriteLife1);
            m_app.Draw(spriteLife2);
            m_app.Draw(spriteLife3);
        }
    }
}

Pannel::~Pannel()
{
    delete imagePannel;
    delete imageLife;
    delete imageLifeFade;
}

Sprite* Pannel::getSprite()
{
    return &sprite;
}

void Pannel::checkPannel()
{
    this->drawLife();
    this->drawScore();
}

void Pannel::drawLife()
{
    Vector2f position = m_position;
    position.x += 1000;
    position.y += 20;

    spriteLife1.SetPosition(position);
    position.x += 50;
    spriteLife2.SetPosition(position);
    position.x += 50;
    spriteLife3.SetPosition(position);
    int lives = m_player.getLives();
    switch(lives)
    {
        case 1:
        {
            spriteLife1.SetImage(*imageLifeFade);
            spriteLife2.SetImage(*imageLifeFade);
            spriteLife3.SetImage(*imageLifeFade);
            break;
        }
        case 2:
        {
            spriteLife1.SetImage(*imageLife);
            spriteLife2.SetImage(*imageLifeFade);
            spriteLife3.SetImage(*imageLifeFade);
            break;
        }
        case 3:
        {
            spriteLife1.SetImage(*imageLife);
            spriteLife2.SetImage(*imageLife);
            spriteLife3.SetImage(*imageLifeFade);
            break;
        }
        case 4:
        {
            spriteLife1.SetImage(*imageLife);
            spriteLife2.SetImage(*imageLife);
            spriteLife3.SetImage(*imageLife);
            break;
        }
    }
    m_app.Draw(spriteLife1);
    m_app.Draw(spriteLife2);
    m_app.Draw(spriteLife3);
}

void Pannel::drawScore()
{
    Font font;
    if(!font.LoadFromFile("Omegav2.ttf"))
    {
        cout << "Erreur lors du chargement de la font pannel" << endl;
    }
    else
    {
        Vector2f position(50, 50);
        std::ostringstream oss;
        oss << m_player.getScore();
        string result = oss.str();
        String text;
        text.SetText(result);
        text.SetFont(font);
        text.SetSize(20);
        text.SetColor(Color(255, 255, 255));
        text.SetPosition(position);
        m_app.Draw(text);
    }
}
