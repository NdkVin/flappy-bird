#include <SFML/Graphics.hpp>
#include<iostream>
using namespace sf;
using namespace std;
struct Flappy {
    Sprite sprite;
    float velocity = -0.5f;
    float gravity = 0.2f;
    int frame = 0;
} flappy;

struct Game {
    Sprite Flappy[3];
    Sprite Background;
    Sprite Land[2];
    Sprite Obstacle;
    int frames = 0;
    float y_floor = 590.0f;
} Game;

void moveLand() {
  int ln = sizeof(Game.Land)/sizeof(Game.Land[0]);
  for(int i =0; i< ln; i++) {
    Game.Land[i].move(-0.1, 0);
    Vector2f vbg = Game.Land[i].getPosition();
    float width = Game.Land[i].getScale().x*780;
    if(vbg.x < -width) {
      Game.Land[i].setPosition(vbg.x+width*2, vbg.y);
    } 
  }
}

int main() {
    RenderWindow window(VideoMode(350, 665), "Flapy Bird");

    Texture bgTexture, landTexture, birdTexture[3];

    bgTexture.loadFromFile("images/background.png");
    landTexture.loadFromFile("images/land.png");

	  Game.Background.setTexture(bgTexture, true);
	  Game.Background.setScale(1.25, 1.15);
	  Game.Background.setPosition(0, 0);

    int ln = sizeof(Game.Land)/sizeof(Game.Land[0]);
    for(int i =0; i< ln; i++) {
	    Game.Land[i].setTexture(landTexture, true);
	    Game.Land[i].setScale(0.7, 0.7);
	    Game.Land[i].setPosition(0.7*780*i, 590);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(Game.Background);
        window.draw(Game.Land[0]);
        window.draw(Game.Land[1]);

        moveLand();
        window.display();
    }

    return 0;
}