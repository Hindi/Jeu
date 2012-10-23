#include "pannel.h"

using namespace std;
using namespace sf;

Pannel::Pannel(const string &filepath, Vector2f position, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
            m_scale(1,1),
            m_player(player),
            m_player2(player2)
{
    imagePannel = new Image;
    *imagePannel = image_manager::getInstance()->getImage(filepath);
    (*imagePannel).CreateMaskFromColor(Color(255, 0, 255));
    sprite.SetImage(*imagePannel);
    sprite.SetPosition(position);
    sprite.Scale(m_scale);

    imageLife = new Image;
    imageLifeFade = new Image;

    //TODO : CHANGER L'INIT DES COEURS

    //Chargment des images de vie
    *imageLife = image_manager::getInstance()->getImage("images/Vie.png");
    *imageLifeFade = image_manager::getInstance()->getImage("images/Vie-fade.png");

    //Placement des sprite de vie
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
    app.Draw(spriteLife1);
    app.Draw(spriteLife2);
    app.Draw(spriteLife3);
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

//Met à jour les valeurs
void Pannel::checkPannel()
{
    app.Draw(sprite);
    this->drawLife();
    this->drawScore();
    this->drawEnemyStats();
}

//Gestion des icones de vie (transparent ou non)
void Pannel::drawLife()
{
    int lives = m_player->getLives();
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
        text.SetSize(20);
        text.SetColor(Color(0, 0, 0));
        text.SetPosition(Vector2f(1250,365));
        app.Draw(text);

        std::ostringstream os;
        os << Population::getInstance()->getCombo();
        result = os.str();
        text.SetText(result);
        text.SetFont(font);
        text.SetSize(20);
        text.SetColor(Color(0, 0, 0));
        text.SetPosition(Vector2f(1250,440));
        app.Draw(text);
    }

}
