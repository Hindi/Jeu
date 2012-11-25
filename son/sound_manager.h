#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H
#include <SFML/audio.hpp>
#include <map>
#include <iostream>

class sound_manager
{
    public:
        const sf::SoundBuffer& getBuffer( const std::string& filename );
        static sound_manager* getInstance();

    private:
        sf::SoundBuffer buffer;

        std::map< std::string, sf::SoundBuffer > m_buffer;


        sound_manager();
        virtual ~sound_manager();
        static sound_manager* _singleton;
};

#endif // SOUND_MANAGER_H
