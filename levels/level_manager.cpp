#include "level_manager.h"

using namespace std;
using namespace sf;

Level_manager *Level_manager::_singleton= NULL;

Level_manager::Level_manager():
            spawnTime(0),
            m_position(0),
            levelOver(false)
{
    timer.start();
}

Level_manager::~Level_manager()
{
    currentLevel.clear();
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
{
    currentLevel.clear();
    levelNumber = level;
    levelOver = false;
    vectorPosition = 0;
    const char* filepath;
    switch(level)
    {
        case 1:
            filepath = "levels/level1.txt";
            break;
        case 2:
            filepath = "levels/level2.txt";
            break;
    }
    ifstream fichier(filepath, ios::in);
    if(fichier)  // si l'ouverture a réussi
    {
        string ligne;
        while(!strcmp(ligne.data(), "OVER")==0)
        {
            getline(fichier, ligne);
            currentLevel.push_back(ligne);
        }
        fichier.close();
    }
    else
        cout << "impossible d'ouvrir : " << filepath  << endl;
}

void Level_manager::checkLevel()
{
    if(vectorPosition < currentLevel.size())
    {
         if(timer.getTime() > spawnTime)
        {
            vector<string> tokens;
            tokenize(currentLevel[vectorPosition], tokens);

            const char* buffer = tokens[0].c_str();


                //On compare ce qu'il lfaut
                //On gère d'abord le timer
                if(strcmp(buffer, "timer") == 0)
                {
                    std::istringstream iss( tokens[1] );
                    // convertir en un int
                    int nombre;
                    iss >> nombre;
                    //On remet à zéro le timer et on fixe le début de la prochaine vague
                    spawnTime = nombre;
                    //cout << "La prochaine vague arrive dans " << nombre << endl;
                }
                //On regarde si on est pas à la fin de la vague
                else if(strcmp(buffer, "END")==0)
                {
                    //On remet le timer à zéro pour sortir du if et attendre le bon moment pour continuer la lecture du fichier
                    timer.reinitialize();
                    //cout << "Les spawns sont terminés pour cette vague !" << endl;
                }
                else if(strcmp(buffer, "OVER")==0)
                {
                    //On remet le timer à zéro pour sortir du if et attendre le bon moment pour continuer la lecture du fichier
                    timer.reinitialize();
                    //cout << "Fin du niveau !" << endl;
                }
                else if(strcmp(buffer, "spawn")==0)
                {
                    Vector2f position((1366 / 100) * atoi(tokens[3].c_str()), (768 / 100) * atoi(tokens[4].c_str()));
                    bool b = stringToBool(tokens[5]);
                    if(strcmp(tokens[1].data(),"ship")==0)
                        Population::getInstance()->createShip(position, tokens[2].data(), b);
                    else if(strcmp(tokens[1].data(),"flyingSaucer")==0)
                        Population::getInstance()->createFlyingSaucer(position, tokens[2].data(), b);
                }
                else if(strcmp(buffer, "boss")==0)
                {
                    if(Population::getInstance()->haveEnnemyInProgress())
                    {
                        vectorPosition--;
                    }
                    else
                    {
                        if(strcmp(tokens[1].data(),"lilith")==0)
                        Population::getInstance()->createLilith();
                    }
                }

                //On libère la mémoire
                delete [] buffer;

            vectorPosition++;
        }
    }
    else
    {
        if(timer.getTime() > 4)
            levelOver = true;
    }
}


void tokenize(const string& str, vector<string>& tokens)
{
    string::size_type lastPos = str.find_first_not_of(" ", 0);
    //Le premier "non délimiteur"
    string::size_type pos = str.find_first_of(" ", lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // On trouve un token, on l'ajoute au vecteur
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // On passe le délimiteur
        lastPos = str.find_first_not_of(" ", pos);
        // On repère le prochain token
        pos = str.find_first_of(" ", lastPos);
    }
    if(tokens.empty())
        tokens.push_back("empty");
}

short Level_manager::getLevelNumber()
{
    return levelNumber;
}

bool Level_manager::isFinished()
{
    return levelOver;
}


bool stringToBool(std::string s)
{
    std::istringstream is(s);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}
