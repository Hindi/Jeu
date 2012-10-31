#include "jeu.h"

using namespace std;
using namespace sf;


Jeu::Jeu(int const SCREEN_WIDTH, int const SCREEN_HEIGHT, Menu &menu):
            m_SCREEN_WIDTH(SCREEN_WIDTH),
            m_SCREEN_HEIGHT(SCREEN_HEIGHT),
            m_menu(menu),
            m_quit(false),
            scorePlayer1(1),
            scorePlayer2(1)
{

}

Jeu::~Jeu()
{

}

void Jeu::start(short niveau)
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

    std::tr1::shared_ptr<Player> player(new Player(0, 1, positionPlayer));
    std::tr1::shared_ptr<Player> player2(new Player(1, 1,positionPlayer));
    player->addScore(scorePlayer1);
    player2->addScore(scorePlayer2);

    Drop_manager *drop_manager;
    drop_manager = Drop_manager::getInstance();
    //Variable population
    Population *population;
    population = Population::getInstance();
    population->setPlayer(player, player2);

    Level_manager *level_manager;
    level_manager = Level_manager::getInstance();

    //gestionnaires de missiles
    Missile_manager *missile_manager;
    missile_manager = Missile_manager::getInstance();
    missile_manager->setPlayer(player);

    //Activateur d'armes
    Weapon_manager *weapon_manager;
    weapon_manager = Weapon_manager::getInstance();
    weapon_manager->setParams(player, player2);

    //pannel
    const string filepathPanel = "images/pannel.png";
    Vector2f positionPannel(m_SCREEN_WIDTH-PANNEL_WIDTH, 0);
    Pannel pannel(filepathPanel, positionPannel, player, player2);

    //Collision
    Vector2f windowSize(m_SCREEN_WIDTH-PANNEL_WIDTH, m_SCREEN_HEIGHT);
    Collision collision(windowSize, player, player2);

    //Background
    Background background(1, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, app);

    Level_manager::getInstance()->startLevel(niveau);

    population->createLilith();

    while (app.IsOpened() )
    {
        if(m_quit || (level_manager->isFinished() && (!population->haveEnnemyInProgress() && !population->haveBossInProgress() )))
        {
            if(level_manager->isFinished())
            {
                this->saveDatas(player, player2);
                m_menu.setLevel(level_manager->getLevelNumber() + 1);
            }
            else
                m_menu.setLevel(1);
            drop_manager->reset();
            population->reset();
            weapon_manager->reset();
            missile_manager->reset();
            scoreManager->reset();
            projectile_manager->reset();
            m_quit = false;
            break;
        }

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
            player->moveUp();
            collision.manageCollisionsY();
        }
        else if(input.IsKeyDown(Key::Down))
        {
            player->moveDown();
            collision.manageCollisionsY();
        }
        if(input.IsKeyDown(Key::Right))
        {
            player->moveRight();
            collision.manageCollisionsX();
        }
        else if(input.IsKeyDown(Key::Left))
        {
            player->moveLeft();
            collision.manageCollisionsX();
        }
        if(!(input.IsKeyDown(Key::Down))&&!(input.IsKeyDown(Key::Up))&&!(input.IsKeyDown(Key::Left))&&!(input.IsKeyDown(Key::Right)))
        {
            player->dontMove();
            collision.manageCollisionsX();
            collision.manageCollisionsY();
        }
        if(input.IsKeyDown(Key::Z))
        {
            player2->moveUp();
            collision.manageCollisionsY2();
        }
        else if(input.IsKeyDown(Key::S))
        {
            player2->moveDown();
            collision.manageCollisionsY2();
        }
        if(input.IsKeyDown(Key::D))
        {
            player2->moveRight();
            collision.manageCollisionsX2();
        }
        else if(input.IsKeyDown(Key::Q))
        {
            player2->moveLeft();
            collision.manageCollisionsX2();
        }
        if(!(input.IsKeyDown(Key::S))&&!(input.IsKeyDown(Key::Z))&&!(input.IsKeyDown(Key::Q))&&!(input.IsKeyDown(Key::D)))
        {
            player2->dontMove();
            collision.manageCollisionsX2();
            collision.manageCollisionsY2();
        }
        if(input.IsKeyDown(Key::A))
        {
            population->freeze();
        }
        if(input.IsKeyDown(Key::Space))
        {
            player->fire0();
        }
        if(input.IsKeyDown(Key::E))
        {
            player2->fire1();
        }
        if(input.IsKeyDown(Key::Escape))
        {
            population->stop();
            this->pause(Event, pannel, player, player2);
            population->unStop();
        }
        if(input.IsKeyDown(Key::H))
        {
            if(player->getPlayerKTA())
            {
                population->killThemAll();
                Projectile_manager::getInstance()->killThemAll();
                player->setPlayerKTA(false);
            }
        }
        if(input.IsKeyDown(Key::J))
        {
            population->killThemAll();
            Projectile_manager::getInstance()->killThemAll();
        }
        if(Projectile_manager::getInstance()->havePlayerProjectilesInProgress() || Missile_manager::getInstance()->haveMissilesInProgress())
        {
            collision.manageProjectileCollision();
        }

        if(player->getLostlife())
        {
            if(!invincible)
            {
                timer.start();
                invincibleStart = timer.getTime();
                invincible = true;
            }
            else if(timer.getTime() - invincibleStart > 4 )
            {
                player->resetLostLife();
                invincible = false;
            }
        }
        level_manager->checkLevel();
        weapon_manager->manage();
        drop_manager->manage();
        player->draw();
        player2->draw();
        population->manage();
        missile_manager->manage();
        pannel.checkPannel();
        scoreManager->manage();
        app.Display();
        timer.sleep(1);
    }

}

void Jeu::pause(Event Event, Pannel &pannel, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2)
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
        player->draw();
        player2->draw();
        pannel.checkPannel();
        m_menu.drawPauseMenu(select);
        app.Display();
    }

}

void Jeu::saveDatas(std::tr1::shared_ptr<Player> player1, std::tr1::shared_ptr<Player> player2)
{
    scorePlayer1 = player1->getScore();
    scorePlayer2 = player2->getScore();
}
