#ifndef Lilith_H_INCLUDED
#define Lilith_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>

#include "../boss.h"
#include "../adds.h"
#include "../../player.h"
#include "../../tirs/projectile.h"
#include "../../animation.h"
#include "../../Animated.hpp"
#include "../../image_manager.h"
#include "../../tirs/projectile_manager.h"
#include "../../const.h"

class Lilith : public Boss
{
    public:
        Lilith(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2);
        //Destruteur
        ~Lilith();

        void createAdd();
        void move();

    protected:
        const char* m_name;
        short m_level;
        sf::Vector2f m_position;


};
#endif // Lilith_H_INCLUDED
