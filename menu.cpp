#include "menu.h"

using namespace std;
using namespace sf;

Menu::Menu(RenderWindow &app): m_app(app), position(250, 200), m_scale(1,1)
{
    imageFadePlay = new Image;
    if(!(*imageFadePlay).LoadFromFile("images/nouvellePartie_fade.png"))
    {
        cerr << "Image loading failed : nouvellePArtie_fade.png" << endl;
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
    if(!(*imageFadeCredit).LoadFromFile("images/Crédits_fade.png"))
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
    else
    {
        if(!(*imageHow).LoadFromFile("images/CommentJouer.png"))
        {
                cerr << "Image loading failed : CommentJouer.png" << endl;
        }
        else
        {
            if(!(*imageCredit).LoadFromFile("images/Crédits.png"))
            {
                    cerr << "Image loading failed : Crédits.png" << endl;
            }
            else
            {

            }
        }
    }
}

Menu::~Menu()
{
    delete imagePlay;
    delete imageHow;
    delete imageCredit;
    delete imageFadePlay;
    delete imageFadePlay;
    delete imageFadePlay;
}

void Menu::draw(int select)
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

