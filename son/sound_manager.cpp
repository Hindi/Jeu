#include "sound_manager.h"

sound_manager* sound_manager::_singleton = NULL;

sound_manager::sound_manager()
{
    if( buffer.LoadFromFile( "son/Acronis.ogg" ) )
	{
		m_buffer["son/Acronis.ogg"] = buffer;
	}
}

sound_manager::~sound_manager()
{
    //dtor
}

sound_manager* sound_manager::getInstance()
  {
    if (NULL == _singleton)
      {
        std::cout << "sound manager : creating singleton." << std::endl;
        _singleton =  new sound_manager;
      }

    return _singleton;
  }

const sf::SoundBuffer& sound_manager::getBuffer( const std::string& filename )
{
	//On vérifie que Le son n'existe pas déjà
	for( std::map<std::string, sf::SoundBuffer>::const_iterator it = m_buffer.begin(); it != m_buffer.end(); ++it)
	{
		if( filename == it->first )
		{
			//std::cout << "DEBUG_MESSAGE: " << filename << " | using existing image.\n";
			return it->second;
		}
	}

	//Le son n'existe pas, on la créé et on la sauvegarde
	sf::SoundBuffer buffer;

	//On cherche dans le dossier principal du projet
	if( buffer.LoadFromFile( filename ) )
	{
		m_buffer[filename] = buffer;
		//std::cout << "DEBUG_MESSAGE: " << filename << " | loading image from main or specified directory.\n";
		return m_buffer[filename];
	}
	std::cout << "GAME_ERROR: Buffer was not found. It is filled with an empty buffer.\n";
	m_buffer[filename] = buffer;
	return m_buffer[filename];
}
