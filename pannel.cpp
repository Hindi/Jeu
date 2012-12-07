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
    sprite.SetImage(*imagePannel);
    sprite.SetPosition(position);
    sprite.Scale(m_scale);

    imageTopPannel = new Image;
    *imageTopPannel = image_manager::getInstance()->getImage("images/pannelHaut1.png");
    topPannel.SetImage(*imageTopPannel);
    topPannel.SetPosition(Vector2f(0, 0));
    topPannel.Scale(0.75, 0.75);

    imageTopPannel2 = new Image;
    *imageTopPannel2 = image_manager::getInstance()->getImage("images/pannelHaut2.png");
    topPannel2.SetImage(*imageTopPannel2);
    topPannel2.SetPosition(Vector2f(500, 0));
    topPannel2.Scale(0.75,0.75);

    imageLife = new Image;
    imageLifeFade = new Image;

    imageArmor = new Image;
    imageArmorFade = new Image;

    imageProgressBar = new Image;
    *imageProgressBar = image_manager::getInstance()->getImage("images/progression-barre.png");
    spriteProgressBar.SetImage(*imageProgressBar);
    spriteProgressBar.SetPosition(1000, 600);

    imageProgressBackground = new Image;
    *imageProgressBackground = image_manager::getInstance()->getImage("images/progression-barre-fade.png");
    spriteProgressBackground.SetImage(*imageProgressBackground);
    spriteProgressBackground.SetPosition(1000, 600);

    //Chargment des images de vie
    *imageLife = image_manager::getInstance()->getImage("images/Vie.png");
    *imageLifeFade = image_manager::getInstance()->getImage("images/Vie-fade.png");

    *imageArmor = image_manager::getInstance()->getImage("images/Armure.png");
    *imageArmorFade = image_manager::getInstance()->getImage("images/Armure-fade.png");

    //Sprites pour les vies
    position.x = 170;
    position.y = 0;
    spriteLife1.SetPosition(position);
    position.x += 30;
    spriteLife2.SetPosition(position);
    position.x += 30;
    spriteLife3.SetPosition(position);

    position.x = 660;
    position.y = 0;
    spriteLife21.SetPosition(position);
    position.x += 30;
    spriteLife22.SetPosition(position);
    position.x += 30;
    spriteLife23.SetPosition(position);

    //Sprite pour les armures

    position.x = 170;
    position.y = 35;
    spriteArmor1.SetPosition(position);
    position.x += 30;
    spriteArmor2.SetPosition(position);
    position.x += 30;
    spriteArmor3.SetPosition(position);

    position.x = 660;
    position.y = 35;
    spriteArmor21.SetPosition(position);
    position.x += 30;
    spriteArmor22.SetPosition(position);
    position.x += 30;
    spriteArmor23.SetPosition(position);
}

Pannel::~Pannel()
{
    delete imagePannel;
    delete imageLife;
    delete imageLifeFade;
    delete imageArmor;
    delete imageArmorFade;
    delete imageTopPannel;
    delete imageProgressBar;
    delete imageProgressBackground;
}

Sprite* Pannel::getSprite()
{
    return &sprite;
}

//Met à jour les valeurs
void Pannel::checkPannel()
{
    app.Draw(sprite);
    app.Draw(topPannel2);
    app.Draw(topPannel);
    this->drawLife();
    this->drawScore();
    this->drawEnemyStats();
    this->drawArmor();
    this->drawProgress();
}

//Gestion des icones de vie (transparent ou non)
void Pannel::drawLife()
{
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

    lives = m_player2->getLives();
    switch(lives)
    {
        case 0:
        {
            spriteLife21.SetImage(*imageLifeFade);
            spriteLife22.SetImage(*imageLifeFade);
            spriteLife23.SetImage(*imageLifeFade);
            break;
        }
        case 1:
        {
            spriteLife21.SetImage(*imageLife);
            spriteLife22.SetImage(*imageLifeFade);
            spriteLife23.SetImage(*imageLifeFade);
            break;
        }
        case 2:
        {
            spriteLife21.SetImage(*imageLife);
            spriteLife22.SetImage(*imageLife);
            spriteLife23.SetImage(*imageLifeFade);
            break;
        }
        case 3:
        {
            spriteLife21.SetImage(*imageLife);
            spriteLife22.SetImage(*imageLife);
            spriteLife23.SetImage(*imageLife);
            break;
        }
    }
    app.Draw(spriteLife21);
    app.Draw(spriteLife22);
    app.Draw(spriteLife23);
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
        Vector2f position(920, 230);
        std::ostringstream oss;
        oss << (m_player->getScore());
        string result = oss.str();
        String text;
        text.SetText(result);
        text.SetFont(font);
        text.SetSize(20);
        text.SetColor(Color(0, 0, 0));
        text.SetPosition(position);
        app.Draw(text);

        std::ostringstream os;
        position.y += 25;
        os << (m_player2->getScore());
        result = os.str();
        text.SetText(result);
        text.SetFont(font);
        text.SetSize(20);
        text.SetColor(Color(0, 0, 0));
        text.SetPosition(position);
        app.Draw(text);

        playerScore = m_player->getScore() + m_player2->getScore();
        position.y += 40;
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
        text.SetPosition(Vector2f(900,450));
        app.Draw(text);

        std::ostringstream os;
        os << Population::getInstance()->getCombo();
        result = os.str();
        text.SetText(result);
        text.SetFont(font);
        text.SetSize(35);
        text.SetColor(Color(0, 0, 0));
        text.SetPosition(Vector2f(900,517));
        app.Draw(text);
    }
}

void Pannel::drawArmor()
{
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

    armor = m_player2->getArmor();
    switch(armor)
    {
        case 0:
        {
            spriteArmor21.SetImage(*imageArmorFade);
            spriteArmor22.SetImage(*imageArmorFade);
            spriteArmor23.SetImage(*imageArmorFade);
            break;
        }
        case 1:
        {
            spriteArmor21.SetImage(*imageArmor);
            spriteArmor22.SetImage(*imageArmorFade);
            spriteArmor23.SetImage(*imageArmorFade);
            break;
        }
        case 2:
        {
            spriteArmor21.SetImage(*imageArmor);
            spriteArmor22.SetImage(*imageArmor);
            spriteArmor23.SetImage(*imageArmorFade);
            break;
        }
        case 3:
        {
            spriteArmor21.SetImage(*imageArmor);
            spriteArmor22.SetImage(*imageArmor);
            spriteArmor23.SetImage(*imageArmor);
            break;
        }
    }
    app.Draw(spriteArmor21);
    app.Draw(spriteArmor22);
    app.Draw(spriteArmor23);
}

void Pannel::drawProgress()
{
/*    float position = Level_manager::getInstance()->getLevelPosition();
    float size = Level_manager::getInstance()->getLevelSize();*/
    float progress = Level_manager::getInstance()->getLevelProgress();
    spriteProgressBar.SetSubRect(IntRect(0, imageProgressBar->GetHeight(), imageProgressBar->GetWidth(), imageProgressBar->GetHeight() - imageProgressBar->GetHeight()*progress));

    app.Draw(spriteProgressBackground);
    app.Draw(spriteProgressBar);
}
