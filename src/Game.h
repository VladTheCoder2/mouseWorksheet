
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void newAnimal();
  bool passport_accepted;
  bool passport_rejected;
  bool should_accept;
  void dragSprite(sf::Sprite* sprite);
  void mouseButtonPressed(sf::Event event);
  void mouseButtonReleased(sf::Event event);

 private:
  sf::RenderWindow& window;
  sf::Sprite ball;
  sf::Texture ball_texture;

  sf::Sprite background;
  sf::Texture background_texture;

  //passport
  sf::Sprite* character;
  sf::Sprite* character_texture;
  sf::Sprite* passport;
  sf::Sprite* passport_texture;

  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];

  sf::Sprite* dragged = nullptr;
  sf::Vector2f drag_offset;

  sf::Sprite accept;
  sf::Texture accept_texture;

  sf::Sprite reject;
  sf::Texture reject_texture;

  sf::Sprite acceptStamp;
  sf::Texture acceptStamp_texture;

  sf::Sprite rejectStamp;
  sf::Texture rejectStamp_texture;

};

#endif // PLATFORMER_GAME_H
