
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
  bool collisionCheck(sf::Vector2i, sf::Sprite);
  void Spawn(sf::Sprite);

 private:
  sf::RenderWindow& window;
  sf::Sprite ball;
  sf::Texture ball_texture;
  
  sf::Sprite background;
  sf::Texture background_texture;
  
  sf::Text title_text;
  sf::Font font;
  
  sf::Sprite bird;
  sf::Texture bird_texture;
  
  sf::Text menu_text;
  sf::Text bird_option_text;
  sf::Text paper_option_text;
  sf::Text play_option_text;
  sf::Text quit_option_text;

  int gamestate = 0;
  int play_selected = 0;
  int speed = 200;
  bool reverse;
  
  sf::Vector2i mouseClick;

  int score = 0;
  sf::Text score_text;

};

#endif // PLATFORMER_GAME_H
