#include "pannel.h"

using namespace std;
using namespace sf;

Pannel::Pannel(const string &filepath, Vector2f position, Player &player, Player &player2):
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
}

//Gestion des icones de vie (transparent ou non)
void Pannel::drawLife()
{
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
    app.Draw(spriteLife1);
    app.Draw(spriteLife2);
    app.Draw(spriteLife3);
}

//Affichage du score
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
        oss << (m_player.getScore()+m_player2.getScore());
        string result = oss.str();
        String text;
        text.SetText(result);
        text.SetFont(font);
        text.SetSize(20);
        text.SetColor(Color(255, 255, 255));
        text.SetPosition(position);
        app.Draw(text);
    }
}
