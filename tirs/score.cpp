#include "score.h"

using namespace std;
using namespace sf;

Score::Score(RenderWindow &app, int score, Vector2f position):
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
}

Score::~Score()
{

}

void Score::draw()
{
    m_app.Draw(string);
}
