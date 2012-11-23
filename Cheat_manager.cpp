#include "Cheat_manager.h"

using namespace sf;

Cheat_manager::Cheat_manager()
{
    konamiCode.push_back("u");
    konamiCode.push_back("u");
    konamiCode.push_back("d");
    konamiCode.push_back("d");
    konamiCode.push_back("l");
    konamiCode.push_back("r");
    konamiCode.push_back("l");
    konamiCode.push_back("r");
    konamiCode.push_back("b");
    konamiCode.push_back("a");

    sopalintMode = false;
}

Cheat_manager::~Cheat_manager()
{
    konamiCode.clear();
}

void Cheat_manager::checkKonami()
{
    Event Event;
    while (app.GetEvent(Event))
    {
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down))
            playerOneKonami.push_back("d");
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up))
            playerOneKonami.push_back("u");
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Left))
            playerOneKonami.push_back("l");
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Right))
            playerOneKonami.push_back("r");
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::B))
            playerOneKonami.push_back("b");
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::A))
            playerOneKonami.push_back("a");

        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Z))
            playerTwoKonami.push_back("d");
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::S))
            playerTwoKonami.push_back("u");
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Q))
            playerTwoKonami.push_back("l");
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::D))
            playerTwoKonami.push_back("r");
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::N))
            playerTwoKonami.push_back("b");
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::E))
            playerTwoKonami.push_back("a");
    }

    for(int i(0); i<playerOneKonami.size(); i++)
    {
        std::cout << playerOneKonami[i] << std::endl;
    }
    if(playerOneKonami.size() == 10)
    {
        int result(0);
        for(int i(0); i<10; i++)
        {
            if(strcmp(konamiCode[i], playerOneKonami[i]) == 0)
                result++;
        }

        if(result == 10 && !sopalintMode)
        {
            sopalintMode = true;
            std::cout << "SOPALINT MODE" << std::endl;
        }
    }

}
