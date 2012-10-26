#include "level_manager.h"

using namespace std;
using namespace sf;

Level_manager *Level_manager::_singleton= NULL;

Level_manager::Level_manager()
{

}

Level_manager::~Level_manager()
{

}

Level_manager* Level_manager::getInstance()
{
    if (NULL == _singleton)
      {
        std::cout << "Level_manager : creating singleton." << std::endl;
        _singleton =  new Level_manager;
      }

    return _singleton;
}

void Level_manager::startLevel(short level)
{/*
    std::ostringstream oss;
    oss << ("level");
    oss << (level);
    string filename = oss.str();*/

    ifstream fichier("levels/level1.txt", ios::in);  // on ouvre le fichier en lecture
    if(fichier)  // si l'ouverture a réussi
    {
        string ligne;
        string type, movement;
        int positionX, positionY;
        bool spawner;
        while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
        {
            fichier >> type >> movement >> positionX >> positionY >>spawner;
            cout << " " << type << " "  << movement << " "  <<positionX << " "  << positionY << " "  << spawner << " "  << endl;
        }

        fichier.close();  // on ferme le fichier
    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier level" << level << " !" << endl;

}
