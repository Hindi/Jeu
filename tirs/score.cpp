#include "score.h"

using namespace std;
using namespace sf;

Score::Score(RenderWindow &app):
            m_app(app)
{
    if (!m_fontCubic.LoadFromFile("font/cubic.ttf"))
    {
        cout << "Erreur au chargement de cubic.ttf" << endl;
    }

}

Score::~Score()
{

}

void Score::addScore(int score)
{
    //Converti int en string
    stringstream oss;
    oss << score;
    std::string s = oss.str();

    //On l'ajoute a sf::string
    string.SetText(s);
    m_strings.push_back(&string);
}
