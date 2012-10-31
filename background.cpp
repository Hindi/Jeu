#include "background.h"

using namespace std;
using namespace sf;

Background::Background(int speed, int SCREEN_WIDTH, int SCREEN_HEIGHT, sf::RenderWindow &app):
            m_speed(speed),
            m_width(SCREEN_WIDTH),
            m_height(SCREEN_HEIGHT),
            app(app)
{
    //Sprite des �toiles
    imageStar = new Image;
    imageStar2 = new Image;
    *imageStar = image_manager::getInstance()->getImage("images/etoile4.png");
    *imageStar2 = image_manager::getInstance()->getImage("images/etoile3.png");
    spriteStar.SetImage(*imageStar);

    //Sprite plan�tes
    imagePlanet = new Image;
    *imagePlanet = image_manager::getInstance()->getImage("images/planete1.png");;
    spritePlanet.SetImage(*imagePlanet);
    imagePlanet2 = new Image;
    *imagePlanet2 = image_manager::getInstance()->getImage("images/planete2.png");;
    spritePlanet2.SetImage(*imagePlanet);

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
        //On d�place les �toiles
        listStar[i].Move(0, m_speed * 2 * app.GetFrameTime());
        app.Draw(listStar[i]);
        //Si une �toile sors de l'�cran on la remet en haut avec une position al�atoire sur l'axe x
        if(listStar[i].GetPosition().y > m_height)
        {
            listStar[i].SetPosition((rand()%980)+1, -40);
        }
    }

    //On d�place les plan�tes
    spritePlanet.Move(0, m_speed* 10 * app.GetFrameTime());
    app.Draw(spritePlanet);

    //Si une plan�te sort on la replace de mani�re al�atoire
    if(spritePlanet.GetPosition().y > m_height)
    {
        spritePlanet2.SetPosition((rand()%980)+1, -500);
        spritePlanet.SetPosition(0,-1000);
    }
    if(spritePlanet2.GetPosition().y > m_height)
    {
        spritePlanet.SetPosition((rand()%980)+1, -500);
        spritePlanet2.SetPosition(0,-1000);
    }
}

void Background::init()
{
    Vector2f position;
    //On recopie l'�toile de base
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

    //On place al�atoirement les �toiles et les plan�tes
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
