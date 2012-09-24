#include "background.h"

using namespace std;
using namespace sf;

Background::Background(RenderWindow &app, int speed, int SCREEN_WIDTH, int SCREEN_HEIGHT, image_manager &imageManager):
            m_app(app),
            m_speed(speed),
            m_width(SCREEN_WIDTH),
            m_height(SCREEN_HEIGHT)
{
    //Sprite des �toiles
    imageStar = new Image;
    *imageStar = imageManager.getImage("images/projectile.png");
    spriteStar.SetImage(*imageStar);

    //Sprite plan�tes
    imagePlanet = new Image;
    *imagePlanet = imageManager.getImage("images/planete2.png");;
    spritePlanet.SetImage(*imagePlanet);

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
        listStar[i].Move(0, m_speed * 2 * m_app.GetFrameTime());
        m_app.Draw(listStar[i]);
        //Si une �toile sors de l'�cran on la remet en haut avec une position al�atoire sur l'axe x
        if(listStar[i].GetPosition().y > m_height)
        {
            listStar[i].SetPosition((rand()%980)+1, -40);
        }
    }

    //On d�place les plan�tes
    spritePlanet.Move(0, m_speed* 10 * m_app.GetFrameTime());
    m_app.Draw(spritePlanet);

    //Si une plan�te sort on la replace de mani�re al�atoire
    if(spritePlanet.GetPosition().y > m_height)
    {
        spritePlanet.SetPosition((rand()%980)+1, -500);
    }
}

void Background::init()
{
    Vector2f position;
    //On recopie l'�toile de base
    Sprite starCopy(spriteStar);
    Sprite starCopy1(spriteStar);
    Sprite starCopy2(spriteStar);
    Sprite starCopy3(spriteStar);
    Sprite starCopy4(spriteStar);
    Sprite starCopy5(spriteStar);
    Sprite starCopy6(spriteStar);
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
