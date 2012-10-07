#include "score.h"

using namespace std;
using namespace sf;

Score::Score(unsigned short score, Vector2f position):
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
    string.Scale(0.4f, 0.4f);
    string.SetFont(m_fontCubic);

    timer.start();
}

Score::~Score()
{

}

void Score::draw()
{
    app.Draw(string);
}

bool Score::isOld()
{
    if(timer.getTime() > 1)
        return true;
    else
        return false;
}

String Score::getString()
{
    return string;
}

void Score::move()
{
    Vector2f position(string.GetPosition());
    string.SetPosition(position.x, position.y-0.5);
}
