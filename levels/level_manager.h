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

        void checkLevel();
        void startLevel(short level);
        short getLevelNumber();
        void setLevelNumber(short number);
        bool  isFinished();
        float getLevelProgress();

        void setGameOver();
        bool endOfGame();

        unsigned int split(const std::string &txt, std::vector<std::string> &strs);


    private:
        short levelMax;
        Level_manager();
        virtual ~Level_manager();
        static Level_manager* _singleton;

        Timer timer, timerProgression;
        float spawnTime;
        short levelNumber;
        int m_position;
        bool levelOver;
        std::vector<std::string> currentLevel;

        std::ifstream fichier;

        int vectorPosition;
        int totalTime;

};

bool stringToBool(std::string s);
void tokenize(const std::string& str, std::vector<std::string>& tokens);
#endif // LEVEL_MANAGER_H_INCLUDED
