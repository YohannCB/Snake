# include <SFML/graphics.hpp>
# include <iostream>
# include <cstdlib>
#include <SFML/Audio.hpp>


using namespace std;
using namespace sf;

int Size = 20;
int width = Size * Size, height = Size * Size;
int corps = 3;
int direction = 1;
int check_move;
int fin = 0;
int restart = 1;
int sco = 0;
int num = 0;


struct snake
{
    int x, y;
}s[100];

//le fruit
struct fruit
{
    int x, y;
}f;



void Mouvement()
{
    //mouvement du corps du serpent
    for (int i = corps; i > 0; i--)
    {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }
    //suivi de la t�te par le reste du corps
    if (direction == 0) s[0].y -= 1;
    if (direction == 1) s[0].x += 1;
    if (direction == 2) s[0].y += 1;
    if (direction == 3) s[0].x -= 1;

    if (s[0].x == f.x && s[0].y == f.y)//si la position de la t�te est �gale a celle du fruit
    {
        corps++;
        f.x = rand() % Size;
        f.y = rand() % Size;
        sco = sco + 1;
        num = num + 14;

    }

    //passer d'un bord a l'autre

    if (s[0].x < 0) s[0].x = 20;
    if (s[0].x > Size) s[0].x = 0;
    if (s[0].y < 0) s[0].y = 20;
    if (s[0].y > Size) s[0].y = 0;
}

int main(int,char const**)
{
    bool startScreen = false;
    bool gameoverScreen = false;

    Texture MainMenu, fond;
    MainMenu.loadFromFile("serpentt.png");

    Texture GameOver, fondecran;

    GameOver.loadFromFile("game-over.png");
    Sprite spriteGO;
    spriteGO.setTexture(GameOver);
    spriteGO.setScale(0.7,0.7);

    Sprite spriteMenu;
    spriteMenu.setTexture(MainMenu);
    spriteMenu.setScale(0.6,0.45);

    sf::Texture texture ;
    texture.loadFromFile("galaxy.png");

    sf::Sprite sprite ;
    sprite.setTexture (texture);

    RenderWindow appli(VideoMode(width , height  ), "------------SNAKE DE L'ESPACE------------", Style::Titlebar);
    appli.setFramerateLimit(60);

    RectangleShape carre(Vector2f(Size, Size));
    carre.setFillColor(Color::Red);

    RectangleShape pomme(Vector2f(Size, Size));
    pomme.setFillColor(Color::Blue);

    Clock timer;

    appli.clear();
    appli.draw(sprite);

    f.x = rand() % Size;
    f.y = rand() % Size;



    while (appli.isOpen())
    {
        Event event;
        while (appli.pollEvent(event))
        {
            if (event.type == Event::Closed)
                appli.close();
        }

        while (startScreen == false)
        {
            appli.clear();
            appli.draw(spriteMenu);
            appli.display();

            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                startScreen = true;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Up) && direction != 2)
            direction = 0;
        else if (direction == 0)
        {
            if (Keyboard::isKeyPressed(Keyboard::Down))
                direction = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) && direction != 3)
            direction = 1;

        else if (direction == 1)
        {
            if (Keyboard::isKeyPressed(Keyboard::Left))
                direction = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) && direction != 0)
            direction = 2;
        else if (direction == 2)
        {
            if (Keyboard::isKeyPressed(Keyboard::Up))
                direction = 2;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left) && direction != 1)
            direction = 3;
        else if (direction == 3)
        {
            if (Keyboard::isKeyPressed(Keyboard::Right))
                direction = 3;
        }

        if (timer.getElapsedTime().asMilliseconds() > 200 - num)
            //vitesse d'execution du mouvement du corps

        {
           Mouvement();
            if (s[0].x < 0 || s[0].y<0 || s[0].x>= Size || s[0].y >= Size )
            {
                appli.close();
                appli.clear();
                appli.draw(spriteGO);
                appli.display();
            }
                for (int i = 1; i < corps; i++)
                    while (s[0].x == s[i].x && s[0].y == s[i].y)

                {
                    {
                        appli.clear();
                        appli.draw(spriteGO);
                        appli.display();
                    }
                }

            timer.restart();
        }

        appli.clear();
        appli.draw(sprite);

        for (int i = 0; i < corps; i++) //tout dessiner
        {
            carre.setPosition(s[i].x * Size, s[i].y * Size);
            appli.draw(carre);
        }
        pomme.setPosition(f.x * Size, f.y * Size);
        appli.draw(pomme);

        appli.display();
    }
    sf::RenderWindow loser (sf::VideoMode(505,462), "T'as Perduuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu", Style::Default);

    while(loser.isOpen())
    {
    sf::Event event;
    Sprite spriteGO;
    spriteGO.setTexture(GameOver);
    spriteGO.setScale(2,2);

    Texture GameOver, fondecran;
    GameOver.loadFromFile("game-over.png");

       while (loser.pollEvent(event))
     {
         if(event.type)
        {
             sf::Event::KeyReleased;
             sf::Text text;
             sf::Font font;

        appli.clear();
        appli.draw(spriteGO);
        appli.display();

          if (event.type == sf::Event::Closed)
          {
            appli.close();
          }

        }
     }
     }

}
