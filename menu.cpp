#include "menu.h"

using namespace std;
using namespace sf;

Menu::Menu(RenderWindow &app, image_manager imageManager):
            m_app(app),
            position(250, 200),
            m_scale(1,1),
            m_imageManager(imageManager)
{
    //Image "nouvelle partie" fade
    imageFadePlay = new Image;
    *imageFadePlay = m_imageManager.getImage("images/nouvellePartie_fade.png");
    spritePlay.SetImage(*imageFadePlay);
    spritePlay.SetPosition(position);
    spritePlay.Scale(m_scale);

    //Image "comment jouer" fade
    position.y += 200;
    imageFadeHow = new Image;
    *imageFadeHow = m_imageManager.getImage("images/CommentJouer_fade.png");
    spriteHow.SetImage(*imageFadeHow);
    spriteHow.SetPosition(position);
    spriteHow.Scale(m_scale);

    //Image "credit" fade
    position.y += 200;
    imageFadeCredit = new Image;
    *imageFadeCredit = m_imageManager.getImage("images/Credits_fade.png");
    spriteCredit.SetImage(*imageFadeCredit);
    spriteCredit.SetPosition(position);
    spriteCredit.Scale(m_scale);

    //Images "Comment jouer", "nouvelle partie" et "credits" highlight
    imagePlay = new Image;
    imageHow = new Image;
    imageCredit = new Image;
    *imagePlay = m_imageManager.getImage("images/nouvellePartie.png");
    *imageHow = m_imageManager.getImage("images/CommentJouer.png");
    *imageCredit = m_imageManager.getImage("images/Credits.png");

    //Image de mise en pause
    position.y = 0;
    position.x = 0;
    imagePause = new Image;
    imageReprendre = new Image;
    imageArreter = new Image;
    *imagePause = m_imageManager.getImage("images/MenuPause.png");
    spritePause.SetImage(*imagePause);
    spritePause.SetPosition(position);
    spritePause.Scale(m_scale);

    //Image Image "reprendre partie" et "quitter partie"
    *imageReprendre = m_imageManager.getImage("images/ReprendreLaPartie.png");
    *imageArreter = m_imageManager.getImage("images/QuitterTaPartie.png");

    //Image Image "prendre partie" et "quitter partie" fade
    imageFadeReprendre = new Image;
    imageFadeArreter = new Image;
    position.y += 400;
    position.x = 250;
    *imageFadeReprendre = m_imageManager.getImage("images/ReprendreLaPartie_fade.png");
    spriteReprendre.SetImage(*imageFadeReprendre);
    spriteReprendre.SetPosition(position);
    spriteReprendre.Scale(m_scale);
    position.y += 200;
    *imageFadeArreter = m_imageManager.getImage("images/QuitterTaPartie_fade.png");
    spriteArreter.SetImage(*imageFadeArreter);
    spriteArreter.SetPosition(position);
    spriteArreter.Scale(m_scale);

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

//Le menu principal avec gestion du highlight avec un système de points
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

//Le menu de pause avec gestion du highlight avec un système de points
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
