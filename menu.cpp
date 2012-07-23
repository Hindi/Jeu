#include "menu.h"

using namespace std;
using namespace sf;

Menu::Menu(RenderWindow &app): m_app(app), position(250, 200), m_scale(1,1)
{
    imageFadePlay = new Image;
    if(!(*imageFadePlay).LoadFromFile("images/nouvellePartie_fade.png"))
    {
        cerr << "Image loading failed : nouvellePartie_fade.png" << endl;
    }
    else
    {
        spritePlay.SetImage(*imageFadePlay);
        spritePlay.SetPosition(position);
        spritePlay.Scale(m_scale);
    }

    position.y += 200;
    imageFadeHow = new Image;
    if(!(*imageFadeHow).LoadFromFile("images/CommentJouer_fade.png"))
    {
        cerr << "Image loading failed : nouvellePArtie_fade.png" << endl;
    }
    else
    {
        spriteHow.SetImage(*imageFadeHow);
        spriteHow.SetPosition(position);
        spriteHow.Scale(m_scale);
    }

    position.y += 200;
    imageFadeCredit = new Image;
    if(!(*imageFadeCredit).LoadFromFile("images/Credits_fade.png"))
    {
        cerr << "Image loading failed : nouvellePArtie_fade.png" << endl;
    }
    else
    {
        spriteCredit.SetImage(*imageFadeCredit);
        spriteCredit.SetPosition(position);
        spriteCredit.Scale(m_scale);
    }

    imagePlay = new Image;
    imageHow = new Image;
    imageCredit = new Image;
    if(!(*imagePlay).LoadFromFile("images/nouvellePartie.png"))
    {
            cerr << "Image loading failed : nouvellePArtie.png" << endl;
    }
    if(!(*imageHow).LoadFromFile("images/CommentJouer.png"))
    {
            cerr << "Image loading failed : CommentJouer.png" << endl;
    }
    if(!(*imageCredit).LoadFromFile("images/Credits.png"))
    {
            cerr << "Image loading failed : Crédits.png" << endl;
    }

    imagePause = new Image;
    imageReprendre = new Image;
    imageArreter = new Image;

    position.y = 0;
    position.x = 0;
    if(!(*imagePause).LoadFromFile("images/MenuPause.png"))
    {
            cerr << "Image loading failed : MenuPause.png" << endl;
    }
    else
    {
        spritePause.SetImage(*imagePause);
        spritePause.SetPosition(position);
        spritePause.Scale(m_scale);
    }
    if(!(*imageReprendre).LoadFromFile("images/ReprendreLaPartie.png"))
    {
            cerr << "Image loading failed : ReprendreLaPartie.png" << endl;
    }
    if(!(*imageArreter).LoadFromFile("images/QuitterTaPartie.png"))
    {
            cerr << "Image loading failed : QuitterTaPartie.png" << endl;
    }

    imageFadeReprendre = new Image;
    imageFadeArreter = new Image;
    position.y += 400;
    position.x = 250;
    if(!(*imageFadeReprendre).LoadFromFile("images/ReprendreLaPartie_fade.png"))
    {
            cerr << "Image loading failed : ReprendreLaPartie_fade.png" << endl;
    }
    else
    {
        spriteReprendre.SetImage(*imageFadeReprendre);
        spriteReprendre.SetPosition(position);
        spriteReprendre.Scale(m_scale);
    }
    position.y += 200;
    if(!(*imageFadeArreter).LoadFromFile("images/QuitterTaPartie_fade.png"))
    {
            cerr << "Image loading failed : QuitterTaPartie_fade.png" << endl;
    }
    else
    {
        spriteArreter.SetImage(*imageFadeArreter);
        spriteArreter.SetPosition(position);
        spriteArreter.Scale(m_scale);
    }
}

Menu::~Menu()
{
    delete imagePlay;
    delete imageHow;
    delete imageCredit;
    delete imageFadePlay;
    delete imageFadeHow;
    delete imageFadeCredit;
    delete imagePause;
    delete imageReprendre;
    delete imageArreter;
    delete imageFadeReprendre;
    delete imageFadeArreter;
}

void Menu::drawMainMenu(int select)
{
    switch(select)
    {
        case 1:
        {
            spritePlay.SetImage(*imagePlay);
            spriteHow.SetImage(*imageFadeHow);
            spriteCredit.SetImage(*imageFadeCredit);
            break;
        }
        case 2:
        {
            spritePlay.SetImage(*imageFadePlay);
            spriteHow.SetImage(*imageHow);
            spriteCredit.SetImage(*imageFadeCredit);
            break;
        }
        case 3:
        {
            spritePlay.SetImage(*imageFadePlay);
            spriteHow.SetImage(*imageFadeHow);
            spriteCredit.SetImage(*imageCredit);
            break;
        }
    }
    m_app.Draw(spritePlay);
    m_app.Draw(spriteCredit);
    m_app.Draw(spriteHow);
}

void Menu::drawPauseMenu(int select)
{
    switch(select)
    {
        case 1:
        {
            spriteReprendre.SetImage(*imageReprendre);
            spriteArreter.SetImage(*imageFadeArreter);
            break;
        }
        case 2:
        {
            spriteReprendre.SetImage(*imageFadeReprendre);
            spriteArreter.SetImage(*imageArreter);
            break;
        }
    }
     m_app.Draw(spritePause);
     m_app.Draw(spriteReprendre);
     m_app.Draw(spriteArreter);
}
