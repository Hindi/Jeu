#include "level_manager.h"

using namespace std;
using namespace sf;

Level_manager *Level_manager::_singleton= NULL;

Level_manager::Level_manager():
            spawnTime(0),
            m_position(0),
            level1Over(false)
{
    timer.start();

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

void Level_manager::checkLevel(short level)
{
    if(!level1Over)
    {

    ifstream fichier("levels/level1.txt", ios::out);  // on ouvre le fichier en lecture
    if(fichier)  // si l'ouverture a réussi
    {
        string ligne;
        char* t="t";
        vector<string> tokens;

        if(timer.getTime() > spawnTime && !fichier.eof())
        {

            fichier.seekg(m_position, ios::beg);

            while ( getline(fichier, ligne) )
               {
                    split(ligne, tokens);
                    cout << "tokenize :" << tokens[0] << tokens[1] << endl;
               }

            /*On récupère la ligne*/


            /*On découpe la string entokens*/
            //split(ligne, tokens, *t);


            /*On convertit le string en char * pour comparer */
            // créer le buffer pour copier la chaîne
            const char* buffer = tokens[0].c_str();


            /*On compare ce qu'il lfaut*/
            //On gère d'abord le timer
            if(strcmp(buffer, "timer") == 0)
            {
                std::istringstream iss( tokens[1] );
                // convertir en un int
                int nombre;
                iss >> nombre;
                //On remet à zéro le timer et on fixe le début de la prochaine vague
                spawnTime = nombre;
                cout << "La prochaine vague arrive dans " << nombre << endl;
            }
            //On regarde si on est pas à la fin de la vague
            else if(strcmp(buffer, "END")==0)
            {
                //On remet le timer à zéro pour sortir du if et attendre le bon moment pour continuer la lecture du fichier
                timer.reinitialize();
                cout << "Les spawns sont terminés pour cette vague !" << endl;
            }
            else if(strcmp(buffer, "OVER")==0)
            {
                //On remet le timer à zéro pour sortir du if et attendre le bon moment pour continuer la lecture du fichier
                timer.reinitialize();
                cout << "Fin du niveau !" << endl;
                level1Over = true;
            }
            else if(strcmp(buffer, "spawn")==0)
                cout << "Je spawn un " << tokens[1] << " qui a comme déplacement " << endl;

            /*On libère la mémoire*/
            delete [] buffer;

        }
        m_position = fichier.tellg();
        fichier.close();  // on ferme le fichier

    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier level" << level << " !" << endl;
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
/*
unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    unsigned int pos = txt.find( ch );
    unsigned int initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos )
    {
        strs.push_back( txt.substr( initialPos, pos - initialPos + 1 ) );
        initialPos = pos + 1;
        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}*/

unsigned int Level_manager::split(const std::string &txt, std::vector<std::string> &strs)
{
    unsigned int pos = m_position;
    unsigned int initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos )
    {
        strs.push_back( txt.substr( initialPos, pos - initialPos + 1 ) );
        initialPos = pos + 1;
        pos = txt.find( m_position, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}
