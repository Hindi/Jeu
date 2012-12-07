#include "background.h"

using namespace std;
using namespace sf;

Background::Background(int speed, int SCREEN_WIDTH, int SCREEN_HEIGHT, sf::RenderWindow &app):
            app(app),
            m_speed(speed),
            m_width(SCREEN_WIDTH),
            m_height(SCREEN_HEIGHT)
{
    //Sprite des étoiles
    imageStar = new Image;
    imageStar2 = new Image;
    *imageStar = image_manager::getInstance()->getImage("images/etoile4.png");
    *imageStar2 = image_manager::getInstance()->getImage("images/etoile3.png");
    spriteStar.SetImage(*imageStar);

    //Sprite planètes
    imagePlanet = new Image;
    *imagePlanet = image_manager::getInstance()->getImage("images/planete1.png");
    imagePlanet2 = new Image;
    *imagePlanet2 = image_manager::getInstance()->getImage("images/planete2.png");
    imagePlanet3 = new Image;
    *imagePlanet3 = image_manager::getInstance()->getImage("images/planete3.png");
    imagePlanet4 = new Image;
    *imagePlanet4 = image_manager::getInstance()->getImage("images/planete4.png");

    short level = Level_manager::getInstance()->getLevelNumber();
    switch(level)
    {
        case 12:
            spritePlanet.SetImage(*imagePlanet);
            break;
        case 2:
            spritePlanet.SetImage(*imagePlanet2);
            break;
        case 3:
            spritePlanet.SetImage(*imagePlanet3);
            break;
        case 1:
            spritePlanet.SetImage(*imagePlanet4);
            break;
    }

    this->init();
}

Background::~Background()
{
    listStar.clear();
    delete imageStar;
    delete imagePlanet;
}


void Background::manage()
{
    int i = 0;
    for(; i < LIST_SIZE; i++)
    {
        //On déplace les étoiles
        listStar[i].Move(0, m_speed * 2 * app.GetFrameTime());
        app.Draw(listStar[i]);
        //Si une étoile sors de l'écran on la remet en haut avec une position aléatoire sur l'axe x
        if(listStar[i].GetPosition().y > m_height)
        {
            listStar[i].SetPosition((rand()%980)+1, -40);
        }
    }

    //On déplace les planètes
    spritePlanet.Move(0, m_speed* 10 * app.GetFrameTime());
    app.Draw(spritePlanet);

    //Si une planète sort on la replace de manière aléatoire
    if(spritePlanet.GetPosition().y > m_height)
    {
        //spritePlanet2.SetPosition((rand()%980)+1, -500);
        spritePlanet.SetPosition(0,-1000);
    }
}

void Background::init()
{
    Vector2f position;
    //On recopie l'étoile de base
    Sprite starCopy(spriteStar);
    Sprite starCopy1(spriteStar);
    spriteStar.SetImage(*imageStar2);
    Sprite starCopy2(spriteStar);
    spriteStar.SetImage(*imageStar);
    Sprite starCopy3(spriteStar);
    spriteStar.SetImage(*imageStar2);
    Sprite starCopy4(spriteStar);
    spriteStar.SetImage(*imageStar);
    Sprite starCopy5(spriteStar);
    Sprite starCopy6(spriteStar);
    spriteStar.SetImage(*imageStar2);
    Sprite starCopy7(spriteStar);
    Sprite starCopy8(spriteStar);
    Sprite starCopy9(spriteStar);

    //On ajoute les copie dans la liste
    listStar.push_back(starCopy);
    listStar.push_back(starCopy1);
    listStar.push_back(starCopy2);
    listStar.push_back(starCopy3);
    listStar.push_back(starCopy4);
    listStar.push_back(starCopy5);
    listStar.push_back(starCopy6);
    listStar.push_back(starCopy7);
    listStar.push_back(starCopy8);
    listStar.push_back(starCopy9);

    //On place aléatoirement les étoiles et les planètes
    LIST_SIZE = listStar.size();
    srand(time(NULL));
    for(int i = 0; i < LIST_SIZE; i++)
    {
        position.x = (rand()%980)+1;
        position.y = (rand()%1024)+1;
        listStar[i].SetPosition(position);
    }
    position.x = (rand()%980)+1;
    position.y = (rand()%1024)+1;
    spritePlanet.SetPosition(position);
}
