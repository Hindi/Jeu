#include "SFML/Graphics.hpp"
#include "jeu.h"
#include "menu.h"
#include "timer.h"
#include <iostream>

using namespace std;
using namespace sf;

void startGame(Jeu jeu);

int main()
{

    const int SCREEN_WIDTH(1280), SCREEN_HEIGHT(1024), MAX_MENU(3);
    sf::RenderWindow app(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Jeu");
    app.UseVerticalSync(true);
    app.SetFramerateLimit(60);


    Menu menu(app);
    Jeu jeu(app, SCREEN_WIDTH, SCREEN_HEIGHT, menu);
    Timer timer;

    int select(1);
    Event Event;

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
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down))
            {
                if(select == MAX_MENU)
                    select +=0;
                else
                    select +=1;
            }
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up))
            {
                if(select == 1)
                    select -=0;
                else
                    select -=1;
            }
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
            {
                switch(select)
                {
                    case 1:
                    {
                        startGame(jeu);
                        break;
                    }
                    case 2:
                    {
                        break;
                    }
                    case 3:
                    {
                        break;
                    }
                }
            }
        }


    menu.drawMainMenu(select);
    app.Display();
    timer.sleep(1);
    }
    return 0;
}

void startGame(Jeu jeu)
{
    jeu.start();
}
