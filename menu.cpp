#include "menu.h"

using namespace std;
using namespace sf;

Menu::Menu():
            position(250, 200),
            m_scale(1,1),
            currentLevel(1)
{
    //Image "nouvelle partie" fade
    imageFadePlay = new Image;
    *imageFadePlay = image_manager::getInstance()->getImage("images/nouvellePartie_fade.png");
    spritePlay.SetImage(*imageFadePlay);
    spritePlay.SetPosition(position);
    spritePlay.Scale(m_scale);

    //Image "comment jouer" fade
    position.y += 200;
    imageFadeHow = new Image;
    *imageFadeHow = image_manager::getInstance()->getImage("images/CommentJouer_fade.png");
    spriteHow.SetImage(*imageFadeHow);
    spriteHow.SetPosition(position);
    spriteHow.Scale(m_scale);

    //Image "credit" fade
    position.y += 200;
    imageFadeCredit = new Image;
    *imageFadeCredit = image_manager::getInstance()->getImage("images/Credits_fade.png");
    spriteCredit.SetImage(*imageFadeCredit);
    spriteCredit.SetPosition(position);
    spriteCredit.Scale(m_scale);

    //Images "Comment jouer", "nouvelle partie" et "credits" highlight
    imagePlay = new Image;
    imageHow = new Image;
    imageCredit = new Image;
    *imagePlay = image_manager::getInstance()->getImage("images/nouvellePartie.png");
    *imageHow = image_manager::getInstance()->getImage("images/CommentJouer.png");
    *imageCredit = image_manager::getInstance()->getImage("images/Credits.png");

    //Fin de niveau
    imageSuivant = new Image;
    imageSuivantFade = new Image;
    imageRecommencer = new Image;
    imageRecommencerFade = new Image;
    imageEndLevel = new Image;
    *imageSuivant = image_manager::getInstance()->getImage("images/suivant.png");
    *imageSuivantFade = image_manager::getInstance()->getImage("images/suivant_fade.png");
    *imageRecommencer = image_manager::getInstance()->getImage("images/recommencer.png");
    *imageRecommencerFade = image_manager::getInstance()->getImage("images/recommencer_fade.png");
    *imageEndLevel = image_manager::getInstance()->getImage("images/MenuNiveauFini.png");

    spriteEndLevel.SetImage(*imageEndLevel);
    spriteSuivant.SetPosition(Vector2f(400, 500));
    spriteRecommencer.SetPosition(Vector2f(800, 500));

    //Image de mise en pause
    position.y = 0;
    position.x = 0;
    imagePause = new Image;
    imageReprendre = new Image;
    imageArreter = new Image;
    *imagePause = image_manager::getInstance()->getImage("images/MenuPause.png");
    spritePause.SetImage(*imagePause);
    spritePause.SetPosition(position);
    spritePause.Scale(m_scale);

    //Image Image "reprendre partie" et "quitter partie"
    *imageReprendre = image_manager::getInstance()->getImage("images/ReprendreLaPartie.png");
    *imageArreter = image_manager::getInstance()->getImage("images/QuitterTaPartie.png");

    //Image Image "prendre partie" et "quitter partie" fade
    imageFadeReprendre = new Image;
    imageFadeArreter = new Image;
    position.y += 400;
    position.x = 250;
    *imageFadeReprendre = image_manager::getInstance()->getImage("images/ReprendreLaPartie_fade.png");
    spriteReprendre.SetImage(*imageFadeReprendre);
    spriteReprendre.SetPosition(position);
    spriteReprendre.Scale(m_scale);
    position.y += 200;
    *imageFadeArreter = image_manager::getInstance()->getImage("images/QuitterTaPartie_fade.png");
    spriteArreter.SetImage(*imageFadeArreter);
    spriteArreter.SetPosition(position);
    spriteArreter.Scale(m_scale);

    imageCreditContent = new Image;
    *imageCreditContent = image_manager::getInstance()->getImage("images/credits2.png");
    spriteCreditContent.SetImage(*imageCreditContent);
    spriteCreditContent.SetPosition(Vector2f(300, 400));
    spriteCreditContent.Scale(m_scale);


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
    delete imageSuivant;
    delete imageSuivantFade;
    delete imageRecommencer;
    delete imageRecommencerFade;
    delete imageEndLevel;
    delete imageCreditContent;
}

//Le menu principal avec gestion du highlight avec un système de points
void Menu::drawMainMenu(int select, int score)
{
    if(currentLevel > 1 && !Level_manager::getInstance()->endOfGame())
    {
        switch(select)
        {
            case 1:
            {
                spriteSuivant.SetImage(*imageSuivant);
                spriteRecommencer.SetImage(*imageRecommencerFade);
                break;
            }
            case 2:
            {
                spriteSuivant.SetImage(*imageSuivantFade);
                spriteRecommencer.SetImage(*imageRecommencer);
                break;
            }
        }
        app.Draw(spriteEndLevel);
        app.Draw(spriteSuivant);
        app.Draw(spriteRecommencer);
        Font font;
        if(!font.LoadFromFile("font/cubos.ttf"))
        {
            cout << "Erreur lors du chargement de la font pannel" << endl;
        }
        else
        {
            string result;
            std::ostringstream o;
            o << (score);
            result = o.str();
            String text;
            text.SetText(result);
            text.SetFont(font);
            text.SetSize(50);
            text.SetColor(Color(255, 255, 255));
            text.SetPosition(Vector2f(600, 382));
            app.Draw(text);
        }

    }
    else if(Level_manager::getInstance()->endOfGame())
    {
        Font font;
        if(!font.LoadFromFile("font/cubos.ttf"))
        {
            cout << "Erreur lors du chargement de la font pannel" << endl;
        }
        else
        {
            string result;
            std::ostringstream o;
            o << "Score final : ";
            o << (score);
            result = o.str();
            String text;
            text.SetText(result);
            text.SetFont(font);
            text.SetSize(50);
            text.SetColor(Color(255, 255, 255));
            text.SetPosition(Vector2f(400, 200));
            app.Draw(text);

            String start;
            start.SetText("Appuyez sur start pour recommencer");
            start.SetFont(font);
            start.SetSize(50);
            start.SetColor(Color(255, 255, 255));
            start.SetPosition(Vector2f(100, 100));
            app.Draw(start);

            app.Draw(spriteCreditContent);
        }
    }
    else
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
        app.Draw(spritePlay);
        app.Draw(spriteCredit);
        app.Draw(spriteHow);
    }
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
     app.Draw(spritePause);
     app.Draw(spriteReprendre);
     app.Draw(spriteArreter);
}

void Menu::setLevel(short nextLevel)
{
    currentLevel = nextLevel;
}

short Menu::getLevel()
{
    return currentLevel;
}
