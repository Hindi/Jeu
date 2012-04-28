#include "jeu.h"

using namespace std;
using namespace sf;

Jeu::Jeu(RenderWindow &app, int const SCREEN_WIDTH, int const SCREEN_HEIGHT): m_app(app),m_SCREEN_HEIGHT(SCREEN_HEIGHT), m_SCREEN_WIDTH(SCREEN_WIDTH)
{
}

Jeu::~Jeu()
{

}

void Jeu::start()
{
    bool invincible(false);
    int invincibleStart;
    Timer timer;

    //Variables :
    const Input & input = m_app.GetInput();
    const int PANNEL_WIDTH(300), PLAYER_WIDTH(118), PLAYER_HEIGHT(93), ENEMY_WIDTH(36), ENEMY_HEIGHT(51);

    //Variables player :
    IntRect subRect(0, PLAYER_HEIGHT, PLAYER_WIDTH, 0);
    double playerXSpeed = 10, playerYSpeed = 10;
    const string filepath = "images/player.png";
    Vector2f positionPlayer(m_SCREEN_WIDTH/2 -50, m_SCREEN_HEIGHT - 100);
    Player player(1, playerXSpeed, playerYSpeed, filepath, positionPlayer, m_app, subRect);

    //Variables enemy :
    double enemyXSpeed = 10, enemyYSpeed = 10;
    const string filepathEnemy = "images/enemy.png";
    Vector2f positionEnemy(m_SCREEN_WIDTH/2 -50, 500);

    //Variable population
    Population population(m_app);
    IntRect subRectEnemy(0, ENEMY_HEIGHT, ENEMY_WIDTH, 0);

    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app, subRectEnemy);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app, subRectEnemy);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app, subRectEnemy);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app, subRectEnemy);
    positionEnemy.x =10;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app, subRectEnemy);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app, subRectEnemy);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app, subRectEnemy);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app, subRectEnemy);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app, subRectEnemy);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app, subRectEnemy);


    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app, subRectEnemy);
    positionEnemy.x +=100;
    //pannel
    const string filepathPanel = "images/pannel.png";
    Vector2f positionPannel(m_SCREEN_WIDTH-PANNEL_WIDTH, 0);
    Pannel pannel(m_app, filepathPanel, positionPannel, player);

    //Collision
    Vector2f windowSize(m_SCREEN_WIDTH-PANNEL_WIDTH, m_SCREEN_HEIGHT);
    Collision collision(windowSize, player, population);

    //Projectiles
    list<Projectile*> projectiles;

    while (m_app.IsOpened())
    {
        m_app.Clear();
        //Entrées touches :
        Event Event;
        while (m_app.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                m_app.Close();

            if((Event.Type = sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::Left))
            {
                player.getSprite()->SetSubRect(subRect);
            }
            if((Event.Type = sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::Right))
            {
                player.getSprite()->SetSubRect(subRect);
            }
        }

        //Déplacements :
        if(input.IsKeyDown(Key::Up))
        {
            player.moveUp();
            collision.manageCollisionsY();
        }
        if(input.IsKeyDown(Key::Down))
        {
            player.moveDown();
            collision.manageCollisionsY();
        }
        if(input.IsKeyDown(Key::Right))
        {
            player.moveRight();
            collision.manageCollisionsX();

        }
        if(input.IsKeyDown(Key::Left))
        {
            player.moveLeft();
            collision.manageCollisionsX();
        }
        if(input.IsKeyDown(Key::Space))
        {
            player.fire();
        }
        if(input.IsKeyDown(Key::Escape))
        {
            m_app.Close();
        }

        if(player.HaveProjectilesInProgress())
        {
            player.moveProjectile();
            collision.manageProjectileCollision();
            player.drawProjectile();
        }

        if(player.getLostlife())
        {
            if(!invincible)
            {
                timer.start();
                invincibleStart = timer.getTime();
                invincible = true;
            }
            else if(timer.getTime() - invincibleStart > 4 )
            {
                player.resetLostLife();
                invincible = false;
            }
        }

        m_app.Draw(*pannel.getSprite());
        pannel.checkPannel();
        population.checkPopulation();
        population.drawPopulation();
        m_app.Draw(*player.getSprite());
        m_app.Display();
    }
}

void Jeu::pause()
{

}
