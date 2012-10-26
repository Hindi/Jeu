#include "level_manager.h"

using namespace std;
using namespace sf;

Level_manager *Level_manager::_singleton= NULL;

Level_manager::Level_manager():
            spawnTime(0)
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
    timer.reinitialize();
    /*
    std::ostringstream oss;
    oss << ("level");
    oss << (level);
    string filename = oss.str();*/

    ifstream fichier("levels/level1.txt", ios::in);  // on ouvre le fichier en lecture
    if(fichier)  // si l'ouverture a r�ussi
    {
        string ligne;
        vector<string> tokens;

        if(timer.getTime() > spawnTime)
        {
            /*On r�cup�re la ligne*/
            getline(fichier, ligne);

            /*On d�coupe la string entokens*/
            tokenize(ligne, tokens);

            /*On convertit le string en char * pour comparer */
            // cr�er le buffer pour copier la cha�ne
            size_t size = tokens[0].size() + 1;
            char * buffer = new char[ size ];
            // copier la cha�ne
            strncpy( buffer, tokens[0].c_str(), size );


            /*On compare ce qu'il lfaut*/
            //On g�re d'abord le timer
            if(strcmp(buffer, "timer") == 0)
            {
                std::istringstream iss( tokens[2] );
                // convertir en un int
                int nombre;
                iss >> nombre;
                //On remet � z�ro le timer et on fixe le d�but de la prochaine vague
                spawnTime = nombre;
            }
            //On regarde si on est pas � la fin de la vague
            else if(strcmp(buffer, "END"))
            {
                //On remet le timer � z�ro pour sortir du if et attendre le bon moment pour continuer la lecture du fichier
                timer.reinitialize();
            }
            else if(strcmp(buffer, "spawn"))
                cout << "Je spawn un " << tokens[1] << " qui a comme d�placement " << tokens[2] << " comme position [" << tokenize[3] << "," << "]" << endl;

            /*On lib�re la m�moire*/
            delete [] buffer;

        }
        fichier.close();  // on ferme le fichier
    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier level" << level << " !" << endl;
}


void tokenize(const string& str, vector<string>& tokens)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(" ", 0);
    // Find first "non-delimiter".
    string::size_type pos = str.find_first_of(" ", lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(" ", pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(" ", lastPos);
    }
}
