#include "SFML/Graphics.hpp"
#include "jeu.h"
#include "menu.h"
#include "timer.h"
#include <iostream>
#include "const.h"
#include <tr1/memory>
#include "son/sound_manager.h"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

RenderWindow app(sf::VideoMode(1366, 768), "jeu");

/*
TODO LIST
- Roundtrip
- Projectiles
*/

int main()
{
    const int SCREEN_WIDTH(1366), SCREEN_HEIGHT(768), MAX_MENU(3);
    app.UseVerticalSync(true);
    app.SetFramerateLimit(60);

    int stateLevel, score(0);

    //Gestionnaire d'images
    image_manager *imageManager;
    imageManager = image_manager::getInstance();
	imageManager->addResourceDirectory("images/" );

    Menu menu;
    Jeu jeu(SCREEN_WIDTH, SCREEN_HEIGHT, menu);
    Timer timer;

    int select(1);
    Event Event;

    sf::SoundBuffer buffer;
    sf:: Sound sound;
    buffer = sound_manager::getInstance()->getBuffer("son/clic.ogg");
    sound.SetBuffer(buffer);
    sound.SetLoop(false);
    sound.SetPitch(1.f);
    sound.SetVolume(50.f);

    //Gestion du highlight du menu avec un système de points
    while (app.IsOpened())
    {
        app.Clear();
        while(app.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                app.Close();
             if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
            {
                app.Close();
            }
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down || Event.Key.Code == sf::Key::Right))
            {
                sound.Play();
                if(select == MAX_MENU)
                    select +=0;
                else
                    select +=1;
            }
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up || Event.Key.Code == sf::Key::Left))
            {
                sound.Play();
                if(select == 1)
                    select -=0;
                else
                    select -=1;
            }
            //Action à effectuer quand on appuie ur entrée : dépend du nombre de points
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
            {
                sound.Play();
                switch(select)
                {
                    case 1:
                    {
                        if(Level_manager::getInstance()->endOfGame())
                        {
                            Level_manager::getInstance()->setLevelNumber(1);
                            menu.setLevel(1);
                        }
                        stateLevel = jeu.start(menu.getLevel());
                        break;
                    }
                    case 2:
                    {
                        if(menu.getLevel() > 1)
                            stateLevel = jeu.start(menu.getLevel()-1);
                        break;
                    }
                    case 3:
                    {
                        break;
                    }
                }
            }
        }
        score = jeu.getTotalScore();
        menu.drawMainMenu(select, score);
        app.Display();
        timer.sleep(1);
    }
    return 0;
}
