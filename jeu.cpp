#include "jeu.h"

using namespace std;
using namespace sf;


Jeu::Jeu(int const SCREEN_WIDTH, int const SCREEN_HEIGHT, Menu &menu):
            m_SCREEN_WIDTH(SCREEN_WIDTH),
            m_SCREEN_HEIGHT(SCREEN_HEIGHT),
            m_menu(menu),
            m_quit(false)
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
    const int PANNEL_WIDTH(300);
    const Input & input = app.GetInput();

    //gestionnaires de projectiles
    Projectile_manager *projectile_manager;
    projectile_manager = Projectile_manager::getInstance();

    //Affichage onscreen des scores
    Score_manager *scoreManager;
    scoreManager = Score_manager::getInstance();

    //Variables player :
    Vector2f positionPlayer(m_SCREEN_WIDTH/2 -50, m_SCREEN_HEIGHT - 100);

    Player player(1, positionPlayer);
    Drop_manager *drop_manager;
    drop_manager = Drop_manager::getInstance();

    //Variable population
    Population *population;
    population = Population::getInstance();
    population->setPlayer(&player);
    Script s1( 1, "I am standing on the left.");
	s1.Launch();

    //gestionnaires de missiles
    Missile_manager *missile_manager;
    missile_manager = Missile_manager::getInstance();
    missile_manager->setPlayer(&player);

    //Activateur d'armes
    Weapon_manager *weapon_manager;
    weapon_manager = Weapon_manager::getInstance();
    weapon_manager->setParams(&player);

    //pannel
    const string filepathPanel = "images/pannel.png";
    Vector2f positionPannel(m_SCREEN_WIDTH-PANNEL_WIDTH, 0);
    Pannel pannel(filepathPanel, positionPannel, player);

    //Collision
    Vector2f windowSize(m_SCREEN_WIDTH-PANNEL_WIDTH, m_SCREEN_HEIGHT);
    Collision collision(windowSize, player);

    //Background
    Background background(1, m_SCREEN_WIDTH, m_SCREEN_HEIGHT);


    population->createShip(Vector2f(100, 100), "don't move",true);

    while (app.IsOpened() )
    {
        if(m_quit)
            break;

        app.Clear();
        background.manage();
        //Entrées touches :
        Event Event;
        while (app.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                app.Close();
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
            population->freeze();
            this->pause(Event, pannel, player);
            population->unFreeze();
        }
        if(Projectile_manager::getInstance()->havePlayerProjectilesInProgress() || Missile_manager::getInstance()->haveMissilesInProgress())
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
        weapon_manager->manage();
        drop_manager->manage();
        player.draw();
        population->manage();
        missile_manager->manage();
        pannel.checkPannel();
        scoreManager->manage();
        app.Display();
        timer.sleep(1);
    }
}

void Jeu::pause(Event Event, Pannel &pannel, Player &player)
{
    Timer timer;
    bool resume(false);
    int select(1);
    while(app.IsOpened() && !resume)
    {
        app.Clear();
        while (app.GetEvent(Event))
        {
            if(resume)
                break;
            app.Clear();
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
        Population::getInstance()->drawPopulation();
        Population::getInstance()->manageExplosion();
        app.Draw(*player.getSprite());
        app.Draw(*pannel.getSprite());
        m_menu.drawPauseMenu(select);
        app.Display();
    }
}

