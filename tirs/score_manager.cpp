#include "score_manager.h"

using namespace std;
using namespace sf;

Score_manager::Score_manager()
{

}

Score_manager::~Score_manager()
{

}

void Score_manager::addScore(int score, Vector2f position)
{
    m_score = new Score(score, position);
    m_scores.push_back(m_score);
}

void Score_manager::draw()
{
    list<Score*>::iterator lit(m_scores.begin());
    for(; lit != m_scores.end(); lit++)
    {
        (*lit)->draw();
    }
}

void Score_manager::manage()
{
    if(haveScoreInProgress())
    {
        list<Score*>::iterator lit(m_scores.begin());
        for(; lit != m_scores.end(); lit++)
        {
            if((*lit)->isOld())
                lit = m_scores.erase(lit);
            else
            {
                String string = (*lit)->string;
                string.SetPosition(Vector2f(100,100));
            }
        }

        this->draw();
    }
}

bool Score_manager::haveScoreInProgress()
{
    if(m_scores.size() >= 1)
        return true;
    else
        return false;
}
