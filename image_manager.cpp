#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "image_manager.h"

image_manager::image_manager() :
            m_images(),
            m_directories()
{

}

image_manager::~image_manager()
{
	m_images.clear();
	m_directories.clear();
}

const sf::Image& image_manager::getImage( const std::string& filename )
{
	//On vérifie que l'image n'existe pas déjà
	for( std::map<std::string, sf::Image>::const_iterator it = m_images.begin(); it != m_images.end(); ++it)
	{
		if( filename == it->first )
		{
			//std::cout << "DEBUG_MESSAGE: " << filename << " | using existing image.\n";
			return it->second;
		}
	}

	//L'image n'existe pas, on la créé et on la sauvegarde
	sf::Image image;

	//On cherche dans le dossier principal du projet
	if( image.LoadFromFile( filename ) )
	{
		m_images[filename] = image;
		//std::cout << "DEBUG_MESSAGE: " << filename << " | loading image from main or specified directory.\n";
		return m_images[filename];
	}

	//Si l'image n'a toujours pas été trouvée, on cherche dans tous les répertoires enregistrés
	for( std::vector< std::string >::iterator it = m_directories.begin(); it != m_directories.end(); ++it )
	{
		if( image.LoadFromFile( (*it) + filename ) )
		{
			m_images[filename] = image;
			//std::cout << "DEBUG_MESSAGE: " << filename << " | searching in all directories was necessary to load the image.\n";
			return m_images[filename];
		}

	}

	//std::cout << "GAME_ERROR: Image was not found. It is filled with an empty image.\n";
	m_images[filename] = image;
	return m_images[filename];
}

void image_manager::addResourceDirectory( const std::string& directory )
{
	//On vérifie si le chemin existe
	for( std::vector<std::string>::const_iterator it  = m_directories.begin(); it != m_directories.end(); ++it )
	{
		//Il existe, on ne le rajoute pas à nouveau
		if( directory == (*it) )
			return;
	}

	//Il n'existe pas, on le rajoute
	m_directories.push_back( directory );
}
/*
void image_manager::deleteImage( const sf::Image& image )
{
	for( std::map<std::string, sf::Image>::const_iterator it = m_images.begin(); it != m_images.end(); ++it)
	{
		if( &image == &it->second )
		{
			m_images.erase( it );
            return;
		}
	}
}*/
/*
void image_manager::deleteImage( const std::string& filename )
{
	std::map<std::string, sf::Image>::const_iterator it = m_images.find( filename );
	if( it != m_images.end() )
		m_images.erase( it );
}*/


/*
void image_manager::removeResourceDirectory( const std::string& directory )
{
	for( std::vector<std::string>::const_iterator it  = m_directories.begin(); it != m_directories.end(); )
	{
		// The path exists. So it isn't necessary to add id once more.
		if( directory == (*it) )
			it = m_directories.erase( it );
		else
			++it;
	}
}*/
