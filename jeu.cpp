#include "jeu.h"

using namespace std;
using namespace sf;


Jeu::Jeu(RenderWindow &app, int const SCREEN_WIDTH, int const SCREEN_HEIGHT, Menu &menu, image_manager imageManager):
            m_app(app),
            m_SCREEN_WIDTH(SCREEN_WIDTH),
            m_SCREEN_HEIGHT(SCREEN_HEIGHT),
            m_menu(menu),
            m_quit(false),
            m_imageManager(imageManager)
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

    //gestionnaires de projectiles
    Projectile_manager projectile_manager(m_app);

    //Variables player :
    IntRect subRect(0, PLAYER_HEIGHT, PLAYER_WIDTH, 0);
    double playerXSpeed = 10, playerYSpeed = 10;
    const string filepath = "images/player.png";
    Vector2f positionPlayer(m_SCREEN_WIDTH/2 -50, m_SCREEN_HEIGHT - 100);
    Player player(1, playerXSpeed, playerYSpeed, filepath, positionPlayer, m_app, m_imageManager, projectile_manager);

    //Variables enemy :
    Vector2f positionEnemy(50, 50);

    Drop_manager drop_manager(m_app, m_imageManager);

    //Variable population
    Population population(m_app, projectile_manager, drop_manager, player, m_imageManager);
    Script s1( 1, "I am standing on the left.", m_imageManager, player, projectile_manager, population);
	s1.Launch();

    population.createShip(positionEnemy, "roundtrip");
    positionEnemy.x +=100;
    population.createShip(positionEnemy, "roundtrip");
    positionEnemy.x +=100;
    population.createShip(positionEnemy, "roundtrip");
    positionEnemy.x +=100;
    population.createFlyingSaucer(positionEnemy, "roundtrip");
    positionEnemy.x +=100;
    population.createShip(positionEnemy, "roundtrip");
    positionEnemy.x +=100;
    population.createShip(positionEnemy, "roundtrip");
    positionEnemy.x +=100;

    //population.createFlyingSaucer(positionEnemy, player, m_imageManager);
    positionEnemy.x +=100;
    population.createShip(positionEnemy, "roundtrip");
    positionEnemy.x +=100;
    //population.createFlyingSaucer(positionEnemy, player, m_imageManager);
    population.createBoss(positionEnemy, "roundtrip");

    //gestionnaires de missiles
    Missile_manager missile_manager(m_app, population,player, m_imageManager);

    //Activateur d'armes
    Weapon_manager weapon_manager(player);

    //pannel
    const string filepathPanel = "images/pannel.png";
    Vector2f positionPannel(m_SCREEN_WIDTH-PANNEL_WIDTH, 0);
    Pannel pannel(m_app, filepathPanel, positionPannel, player, m_imageManager);

    //Collision
    Vector2f windowSize(m_SCREEN_WIDTH-PANNEL_WIDTH, m_SCREEN_HEIGHT);
    Collision collision(windowSize, player, population, projectile_manager, missile_manager, drop_manager);

    //Background
    Background background(m_app, 1, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, m_imageManager);

    while (m_app.IsOpened() )
    {
        if(m_quit)
            break;

        m_app.Clear();
        background.manage();
        //Entrées touches :
        Event Event;
        while (m_app.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                m_app.Close();
        }
        //Déplacements :
        if(input.IsKeyDown(Key::Up))
        {
            player.moveUp();
            collision.manageCollisionsY();
        }
        else if(input.IsKeyDown(Key::Down))
        {
            player.moveDown();
            collision.manageCollisionsY();
        }
        if(input.IsKeyDown(Key::Right))
        {
            player.moveRight();
            collision.manageCollisionsX();
        }
        else if(input.IsKeyDown(Key::Left))
        {
            player.moveLeft();
            collision.manageCollisionsX();
        }
        if(!(input.IsKeyDown(Key::Down))&&!(input.IsKeyDown(Key::Up))&&!(input.IsKeyDown(Key::Left))&&!(input.IsKeyDown(Key::Right)))
        {
            player.dontMove();
            collision.manageCollisionsX();
            collision.manageCollisionsY();
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
        if(projectile_manager.havePlayerProjectilesInProgress() || missile_manager.haveMissilesInProgress())
        {
            collision.manageProjectileCollision();
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
        weapon_manager.manage();
        drop_manager.manage();
        player.draw();
        population.manage();
        missile_manager.manage();
        pannel.checkPannel();
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
                timer.sleep(70);
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
        population.drawPopulation();
        population.manageExplosion();
        m_app.Draw(*player.getSprite());
        m_app.Draw(*pannel.getSprite());
        m_menu.drawPauseMenu(select);
        m_app.Display();
    }
}

