#include "score_manager.h"

using namespace std;
using namespace sf;

Score_manager *Score_manager::_singleton = NULL;

Score_manager::Score_manager()
{

}

Score_manager::~Score_manager()
{
    this->reset();
}

void Score_manager::addScore(int score, Vector2f position)
{
    std::tr1::shared_ptr<Score> m_score(new Score(score, position));
    m_scores.push_back(m_score);
}

void Score_manager::draw()
{
    list<std::tr1::shared_ptr<Score> >::iterator lit(m_scores.begin());
    for(; lit != m_scores.end(); lit++)
    {
        (*lit)->draw();
    }
}

void Score_manager::manage()
{
    if(haveScoreInProgress())
    {
        list<std::tr1::shared_ptr<Score> >::iterator lit(m_scores.begin());
        for(; lit != m_scores.end(); lit++)
        {
            if((*lit)->isOld())
                lit = m_scores.erase(lit);
            else
            {
                (*lit)->move();
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

Score_manager* Score_manager::getInstance()
  {
    if (NULL == _singleton)
      {
        std::cout << "score manager : creating singleton." << std::endl;
        _singleton =  new Score_manager;
      }

    return _singleton;
  }

void Score_manager::kill ()
  {
    if (NULL != _singleton)
      {
        delete _singleton;
        _singleton = NULL;
      }
  }

void Score_manager::reset()
{

}
