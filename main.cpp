#include <SFML/Graphics.hpp>
#include<iostream>
using namespace sf;
using namespace std;
struct Flappy {
    Sprite sprite;
    float velocity = -0.3f;
    float gravity = 0.15f;
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

    Texture bgTexture, landTexture, flappyTexture[3];

    bgTexture.loadFromFile("images/background.png");
    landTexture.loadFromFile("images/land.png");
    flappyTexture[0].loadFromFile("images/flappy1.png");
    flappyTexture[1].loadFromFile("images/flappy2.png");
    flappyTexture[2].loadFromFile("images/flappy3.png");

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
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Space) {
                    flappy.sprite.move(0.0f, flappy.gravity);
                }
            }
        }

        float fx = flappy.sprite.getPosition().x;
        float fy = flappy.sprite.getPosition().y;
        if (fx == 0) flappy.sprite.setPosition(50, 350);

        if(fy > 665) {
          flappy.velocity = 0;
          flappy.velocity = 0;
        }
        flappy.sprite.move(0.0f, flappy.gravity);
        cout << fy << endl;

        if(Keyboard::isKeyPressed(Keyboard::Space)) {
          flappy.sprite.move(0.0f, flappy.velocity);
        }
        if(Game.frames % 10 == 0 ) flappy.frame += 1;

        if (Game.frames == 3) flappy.frame = 0;

        flappy.sprite.setTexture(flappyTexture[flappy.frame], true);

        window.clear();

        window.draw(Game.Background);
        window.draw(Game.Land[0]);
        window.draw(Game.Land[1]);
        window.draw(flappy.sprite);

        moveLand();
        window.display();

        Game.frames++;
        if(Game.frames== 60) Game.frames = 0;
    }

    return 0;
}