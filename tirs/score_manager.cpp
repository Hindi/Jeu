#include "score_manager.h"

using namespace std;
using namespace sf;

Score_manager::Score_manager(RenderWindow &app):
            m_app(app)
{

}

Score_manager::~Score_manager()
{

}

void Score_manager::addScore(int score, Vector2f position)
{
    m_score = new Score(m_app, score, position);
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
