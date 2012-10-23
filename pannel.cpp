#include "pannel.h"

using namespace std;
using namespace sf;

Pannel::Pannel(const string &filepath, Vector2f position, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
            m_scale(1,1),
            m_player(player),
            m_player2(player2),
            m_position(position)
{
    imagePannel = new Image;
    *imagePannel = image_manager::getInstance()->getImage(filepath);
    (*imagePannel).CreateMaskFromColor(Color(255, 0, 255));
    sprite.SetImage(*imagePannel);
    sprite.SetPosition(position);
    sprite.Scale(m_scale);

    imageLife = new Image;
    imageLifeFade = new Image;

    imageArmor = new Image;
    imageArmorFade = new Image;

    //TODO : CHANGER L'INIT DES COEURS

    //Chargment des images de vie
    *imageLife = image_manager::getInstance()->getImage("images/Vie.png");
    *imageLifeFade = image_manager::getInstance()->getImage("images/Vie-fade.png");

    *imageArmor = image_manager::getInstance()->getImage("images/Armure.png");
    *imageArmorFade = image_manager::getInstance()->getImage("images/Armure-fade.png");
}

Pannel::~Pannel()
{
    delete imagePannel;
    delete imageLife;
    delete imageLifeFade;
    delete imageArmor;
    delete imageArmorFade;
}

Sprite* Pannel::getSprite()
{
    return &sprite;
}

//Met à jour les valeurs
void Pannel::checkPannel()
{
    app.Draw(sprite);
    this->drawLife();
    this->drawScore();
    this->drawEnemyStats();
    this->drawArmor();
}

//Gestion des icones de vie (transparent ou non)
void Pannel::drawLife()
{
    Vector2f position = m_position;
    position.x += 100;
    position.y += 550;
    spriteLife1.SetPosition(position);
    position.x += 50;
    spriteLife2.SetPosition(position);
    position.x += 50;
    spriteLife3.SetPosition(position);
    int lives = m_player->getLives();
    switch(lives)
    {
        case 0:
        {
            spriteLife1.SetImage(*imageLifeFade);
            spriteLife2.SetImage(*imageLifeFade);
            spriteLife3.SetImage(*imageLifeFade);
            break;
        }
        case 1:
        {
            spriteLife1.SetImage(*imageLife);
            spriteLife2.SetImage(*imageLifeFade);
            spriteLife3.SetImage(*imageLifeFade);
            break;
        }
        case 2:
        {
            spriteLife1.SetImage(*imageLife);
            spriteLife2.SetImage(*imageLife);
            spriteLife3.SetImage(*imageLifeFade);
            break;
        }
        case 3:
        {
            spriteLife1.SetImage(*imageLife);
            spriteLife2.SetImage(*imageLife);
            spriteLife3.SetImage(*imageLife);
            break;
        }
    }
    app.Draw(spriteLife1);
    app.Draw(spriteLife2);
    app.Draw(spriteLife3);


    position.x -= 250;
    spriteLife1.SetPosition(position);
    position.x += 50;
    spriteLife2.SetPosition(position);
    position.x += 50;
    spriteLife3.SetPosition(position);
    lives = m_player2->getLives();
    switch(lives)
    {
        case 0:
        {
            spriteLife1.SetImage(*imageLifeFade);
            spriteLife2.SetImage(*imageLifeFade);
            spriteLife3.SetImage(*imageLifeFade);
            break;
        }
        case 1:
        {
            spriteLife1.SetImage(*imageLife);
            spriteLife2.SetImage(*imageLifeFade);
            spriteLife3.SetImage(*imageLifeFade);
            break;
        }
        case 2:
        {
            spriteLife1.SetImage(*imageLife);
            spriteLife2.SetImage(*imageLife);
            spriteLife3.SetImage(*imageLifeFade);
            break;
        }
        case 3:
        {
            spriteLife1.SetImage(*imageLife);
            spriteLife2.SetImage(*imageLife);
            spriteLife3.SetImage(*imageLife);
            break;
        }
    }
    app.Draw(spriteLife1);
    app.Draw(spriteLife2);
    app.Draw(spriteLife3);
}

//Affichage du score
void Pannel::drawScore()
{
    Font font;
    if(!font.LoadFromFile("font/cubos.ttf"))
    {
        cout << "Erreur lors du chargement de la font pannel" << endl;
    }
    else
    {
        Vector2f position(1180, 130);
        std::ostringstream oss;
        oss << (m_player->getScore());
        string result = "player 1 : " + oss.str();
        String text;
        text.SetText(result);
        text.SetFont(font);
        text.SetSize(20);
        text.SetColor(Color(0, 0, 0));
        text.SetPosition(position);
        app.Draw(text);

        std::ostringstream os;
        position.y += 15;
        os << (m_player2->getScore());
        result = "player 2 : " + os.str();
        text.SetText(result);
        text.SetFont(font);
        text.SetSize(20);
        text.SetColor(Color(0, 0, 0));
        text.SetPosition(position);
        app.Draw(text);

        result = "Total :";
        position.y += 30;
        text.SetText(result);
        text.SetSize(25);
        text.SetColor(Color(0, 0, 0));
        text.SetPosition(position);
        app.Draw(text);

        position.y += 30;
        std::ostringstream o;
        o << (m_player->getScore() + m_player2->getScore());
        result = o.str();
        text.SetText(result);
        text.SetFont(font);
        text.SetSize(20);
        text.SetColor(Color(0, 0, 0));
        text.SetPosition(position);
        app.Draw(text);
    }
}

void Pannel::drawEnemyStats()
{
    Font font;
    if(!font.LoadFromFile("font/cubos.ttf"))
    {
        cout << "Erreur lors du chargement de la font pannel" << endl;
    }
    else
    {
        std::ostringstream oss;
        oss << Population::getInstance()->getKilledEnemies();
        string result = oss.str();
        String text;
        text.SetText(result);
        text.SetFont(font);
        text.SetSize(35);
        text.SetColor(Color(0, 0, 0));
        text.SetPosition(Vector2f(1250,350));
        app.Draw(text);

        std::ostringstream os;
        os << Population::getInstance()->getCombo();
        result = os.str();
        text.SetText(result);
        text.SetFont(font);
        text.SetSize(35);
        text.SetColor(Color(0, 0, 0));
        text.SetPosition(Vector2f(1250,420));
        app.Draw(text);
    }
}

void Pannel::drawArmor()
{

    Vector2f position = m_position;
    position.x += 100;
    position.y += 600;
    spriteArmor1.SetPosition(position);
    position.x += 50;
    spriteArmor2.SetPosition(position);
    position.x += 50;
    spriteArmor3.SetPosition(position);
    int armor = m_player->getArmor();
    switch(armor)
    {
        case 0:
        {
            spriteArmor1.SetImage(*imageArmorFade);
            spriteArmor2.SetImage(*imageArmorFade);
            spriteArmor3.SetImage(*imageArmorFade);
            break;
        }
        case 1:
        {
            spriteArmor1.SetImage(*imageArmor);
            spriteArmor2.SetImage(*imageArmorFade);
            spriteArmor3.SetImage(*imageArmorFade);
            break;
        }
        case 2:
        {
            spriteArmor1.SetImage(*imageArmor);
            spriteArmor2.SetImage(*imageArmor);
            spriteArmor3.SetImage(*imageArmorFade);
            break;
        }
        case 3:
        {
            spriteArmor1.SetImage(*imageArmor);
            spriteArmor2.SetImage(*imageArmor);
            spriteArmor3.SetImage(*imageArmor);
            break;
        }
    }
    app.Draw(spriteArmor1);
    app.Draw(spriteArmor2);
    app.Draw(spriteArmor3);


    position.x -= 250;
    spriteArmor1.SetPosition(position);
    position.x += 50;
    spriteArmor2.SetPosition(position);
    position.x += 50;
    spriteArmor3.SetPosition(position);
    armor = m_player2->getArmor();
    switch(armor)
    {
        case 0:
        {
            spriteArmor1.SetImage(*imageArmorFade);
            spriteArmor2.SetImage(*imageArmorFade);
            spriteArmor3.SetImage(*imageArmorFade);
            break;
        }
        case 1:
        {
            spriteArmor1.SetImage(*imageArmor);
            spriteArmor2.SetImage(*imageArmorFade);
            spriteArmor3.SetImage(*imageArmorFade);
            break;
        }
        case 2:
        {
            spriteArmor1.SetImage(*imageArmor);
            spriteArmor2.SetImage(*imageArmor);
            spriteArmor3.SetImage(*imageArmorFade);
            break;
        }
        case 3:
        {
            spriteArmor1.SetImage(*imageArmor);
            spriteArmor2.SetImage(*imageArmor);
            spriteArmor3.SetImage(*imageArmor);
            break;
        }
    }
    app.Draw(spriteArmor1);
    app.Draw(spriteArmor2);
    app.Draw(spriteArmor3);
}
