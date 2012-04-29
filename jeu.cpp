#include "jeu.h"

using namespace std;
using namespace sf;

Jeu::Jeu(RenderWindow &app, int const SCREEN_WIDTH, int const SCREEN_HEIGHT, Menu &menu): m_app(app),m_SCREEN_HEIGHT(SCREEN_HEIGHT), m_SCREEN_WIDTH(SCREEN_WIDTH), m_menu(menu), m_quit(false)
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
    const int PANNEL_WIDTH(300), PLAYER_WIDTH(118), PLAYER_HEIGHT(93);
    const Input & input = m_app.GetInput();

    //Variables player :
    IntRect subRect(0, PLAYER_HEIGHT, PLAYER_WIDTH, 0);
    double playerXSpeed = 10, playerYSpeed = 10;
    const string filepath = "images/player.png";
    Vector2f positionPlayer(m_SCREEN_WIDTH/2 -50, m_SCREEN_HEIGHT - 100);
    Player player(1, playerXSpeed, playerYSpeed, filepath, positionPlayer, m_app);

    //Variables enemy :
    double enemyXSpeed = 10, enemyYSpeed = 10;
    const string filepathEnemy = "images/enemy.png";
    Vector2f positionEnemy(m_SCREEN_WIDTH/2 -50, 500);

    //Variable population
    Population population(m_app);

    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app);
    positionEnemy.x =10;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app);
    positionEnemy.x +=100;
    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app);


    population.createEnemy(10, enemyXSpeed, enemyYSpeed, filepathEnemy, positionEnemy, m_app);
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

    while (m_app.IsOpened() )
    {
        if(m_quit)
            break;

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
        if(!(input.IsKeyDown(Key::Down))&&!(input.IsKeyDown(Key::Up))&&!(input.IsKeyDown(Key::Left))&&!(input.IsKeyDown(Key::Right)))
        {
            player.dontMove();
        }
        if(input.IsKeyDown(Key::Space))
        {
            player.fire();
        }
        if(input.IsKeyDown(Key::Escape))
        {
            population.freeze();
            this->pause(population, Event, pannel, player);
            population.unFreeze();
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
        player.draw();
        m_app.Draw(*pannel.getSprite());
        pannel.checkPannel();
        population.checkPopulation();
        population.drawPopulation();
        m_app.Display();
        timer.sleep(1);
    }
}

void Jeu::pause(Population &population, Event Event, Pannel &pannel, Player &player)
{
    Timer timer;
    bool resume(false);
    int select(1);
    while(m_app.IsOpened() && !resume)
    {
        m_app.Clear();
        while (m_app.GetEvent(Event))
        {
            if(resume)
                break;
            m_app.Clear();
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down))
            {
                if(select == 2)
                    select +=0;
                else
                    select +=1;
            }
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up))
            {
                if(select == 1)
                    select -=0;
                else
                    select -=1;
            }
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
            {
                resume = true;
            }
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
            {
                switch(select)
                {
                    case 1:
                    {
                        resume = true;
                        break;
                    }
                    case 2:
                    {
                        resume = true;
                        m_quit = true;
                        break;
                    }
                }
            }

        timer.sleep(1);
        }
        m_app.Draw(*pannel.getSprite());
        population.drawPopulation();
        m_app.Draw(*player.getSprite());
        m_menu.drawPauseMenu(select);
        m_app.Display();
    }
}

