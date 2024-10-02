
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
	in_menu = true;

	if (!font.loadFromFile("D:/Wack-a-fool/Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "font did not load \n";
	}
	menu_text.setString("Welcome to Whack-a-mole");
	menu_text.setFont(font);
	menu_text.setCharacterSize(50);
	menu_text.setScale(0.5, 0.5);
	menu_text.setFillColor(sf::Color(255, 255, 255, 128));
	menu_text.setPosition(
		window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2,
		window.getSize().y / 4 - menu_text.getGlobalBounds().height / 2);
	
	if (!font.loadFromFile("D:/Wack-a-fool/Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "font did not load \n";
	}
	play_option_text.setString("Play");
	play_option_text.setFont(font);
	play_option_text.setCharacterSize(50);
	play_option_text.setScale(0.5, 0.5);
	play_option_text.setFillColor(sf::Color(255, 255, 255, 128));
	play_option_text.setPosition(
		window.getSize().x / 4 - play_option_text.getGlobalBounds().width / 2,
		window.getSize().y / 2 - play_option_text.getGlobalBounds().height / 2);
	
	if (!font.loadFromFile("D:/Wack-a-fool/Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "font did not load \n";
	}
	quit_option_text.setString("Quit");
	quit_option_text.setFont(font);
	quit_option_text.setCharacterSize(50);
	quit_option_text.setScale(0.5, 0.5);
	quit_option_text.setFillColor(sf::Color(255, 255, 255, 128));
	quit_option_text.setPosition(
		window.getSize().x*3 / 4 - quit_option_text.getGlobalBounds().width / 2,
		window.getSize().y / 2 - quit_option_text.getGlobalBounds().height / 2);


	if (!background_texture.loadFromFile("D:/Wack-a-fool/Data/WhackaMole Worksheet/background.png"))
	{
		std::cout << "background texture did not load \n";
	}
	background.setTexture(background_texture);

	if (!font.loadFromFile("D:/Wack-a-fool/Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "font did not load \n";
	}
	title_text.setString("Whack-a-mole");
	title_text.setFont(font);
	title_text.setCharacterSize(200);
	title_text.setScale(0.5, 0.5);
	title_text.setFillColor(sf::Color(255, 255, 255, 128));
	title_text.setPosition(
		window.getSize().x / 2 - title_text.getGlobalBounds().width / 2,
		window.getSize().y / 2 - title_text.getGlobalBounds().height / 2);


	if (!font.loadFromFile("D:/Wack-a-fool/Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "font did not load \n";
	}
	score_text.setString("0");
	score_text.setFont(font);
	score_text.setCharacterSize(50);
	score_text.setScale(0.5, 0.5);
	score_text.setFillColor(sf::Color(250, 250, 250, 250));
	score_text.setPosition(
		window.getSize().x*11 / 12 - score_text.getGlobalBounds().width / 2,
		window.getSize().y / 8 - score_text.getGlobalBounds().height / 2);

	if (!bird_texture.loadFromFile("D:/Wack-a-fool/Data/WhackaMole Worksheet/bird.png"))
	{
		std::cout << "bird texture did not load \n";
	}
	bird.setTexture(bird_texture);
	bird.setPosition(100, 100);
	bird.setScale(0.5, 0.5);

  return true;
}

void Game::update(float dt)
{
	if (in_menu == false)
	{
		if ((bird.getPosition().x > (window.getSize().x - bird.getGlobalBounds().width)) ||
			(bird.getPosition().x < 0))
		{
			reverse = !reverse;
		}

		if (reverse)
		{
			bird.move(1.0f * speed * dt, 0);
			bird.setTextureRect(sf::IntRect(
				0, 0, bird.getLocalBounds().width, bird.getLocalBounds().height));
		}
		else
		{
			bird.move(-1.0f * speed * dt, 0);
			bird.setTextureRect(sf::IntRect(
				bird.getLocalBounds().width,
				0,
				-bird.getLocalBounds().width,
				bird.getLocalBounds().height));
		}
	}
}

void Game::render()
{
	if (in_menu == true)
	{
		window.draw(menu_text);
		window.draw(play_option_text);
		window.draw(quit_option_text);
	}
	else
	{
		window.draw(background);
		window.draw(title_text);
		window.draw(bird);
		window.draw(score_text);
	}
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  Game::mouseClick = sf::Mouse::getPosition(window);

  if (Game::collisionCheck(Game::mouseClick, bird))
  {
	  Spawn(bird);
	  score++;
	  score_text.setString(std::to_string(score));
  }


}

void Game::keyPressed(sf::Event event)
{
	if (in_menu == true)
	{
		if (
			(event.key.code == sf::Keyboard::Left) ||
			(event.key.code == sf::Keyboard::Right))
		{
			play_selected = !play_selected;

			if (play_selected)
			{
				play_option_text.setString("> Play <");
				quit_option_text.setString("Quit");
			}
			else
			{
				play_option_text.setString("Play");
				quit_option_text.setString("> Quit <");
			}
		}
		else if (event.key.code == sf::Keyboard::Enter)
		{
			if (play_selected)
			{
				in_menu = false;
			}
			else
			{
				window.close();
			}
		}
	}
	else if (in_menu == false)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}
	}
}

bool Game::collisionCheck(sf::Vector2i, sf::Sprite)
{
	if ((mouseClick.x >= bird.getPosition().x) &&  
		(mouseClick.x <= bird.getPosition().x + bird.getGlobalBounds().width))
	{
		if ((mouseClick.y >= bird.getPosition().y) &&
			(mouseClick.y <= bird.getPosition().y + bird.getGlobalBounds().height))
		{
			return true;
		}
	}
	return false;
}

void Game::Spawn(sf::Sprite)
{
	bird.setPosition(rand() % int(window.getSize().x - bird.getGlobalBounds().width),
					rand() % int(window.getSize().y - bird.getGlobalBounds().height));
}

