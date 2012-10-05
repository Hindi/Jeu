#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "player.h"

extern sf::RenderWindow app(sf::VideoMode(1366, 768), "Jeu");
extern Player player(1, sf::Vector2f(1000, 600));

#endif // CONST_H_INCLUDED
