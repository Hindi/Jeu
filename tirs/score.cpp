#include "score.h"

using namespace std;
using namespace sf;

Score::Score(RenderWindow &app, unsigned short score, Vector2f position):
            m_app(app),
            m_score(score),
            m_position(position)
{
    if (!m_fontCubic.LoadFromFile("font/cubic.ttf"))
    {
        cout << "Erreur au chargement de cubic.ttf" << endl;
    }

    //Converti int en string
    stringstream oss;
    oss << score;
    std::string s = oss.str();

    //On l'ajoute a sf::string
    string.SetText(s);
    string.SetPosition(m_position);

    timer.start();
}

Score::~Score()
{

}

void Score::draw()
{
    m_app.Draw(string);
}

bool Score::isOld()
{
    if(timer.getTime() > 2)
        return true;
    else
        return false;
}

String Score::getString()
{
    return string;
}
