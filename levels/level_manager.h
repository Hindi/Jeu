#ifndef LEVEL_MANAGER_H_INCLUDED
#define LEVEL_MANAGER_H_INCLUDED
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>

#include "../population.h"
#include "../timer.h"

class Level_manager
{
    public:

        static Level_manager* getInstance();

        void checkLevel(short niveau);
        unsigned int split(const std::string &txt, std::vector<std::string> &strs);


    private:
        Level_manager();
        virtual ~Level_manager();

        static Level_manager* _singleton;

        Timer timer;
        short spawnTime;
        int m_position;
        bool level1Over;

        std::ifstream fichier;


};

void tokenize(const std::string& str, std::vector<std::string>& tokens);
#endif // LEVEL_MANAGER_H_INCLUDED
