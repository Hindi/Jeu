#ifndef LEVEL_MANAGER_H_INCLUDED
#define LEVEL_MANAGER_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "../population.h"
#include "../timer.h"

class Level_manager
{
    public:

        static Level_manager* getInstance();

        void startLevel(short niveau);


    private:
        Level_manager();
        virtual ~Level_manager();

        static Level_manager* _singleton;

        Timer timer;
        short spawnTime;


};


#endif // LEVEL_MANAGER_H_INCLUDED
