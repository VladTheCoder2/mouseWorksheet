#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window),
	character(nullptr),
	passport(nullptr),
	passport_accepted(false),
	passport_rejected(false),
	should_accept(false),
	dragged(nullptr)
{
	srand(time(NULL));
}

Game::~Game()
{
	delete[] animals;
	delete[] passports;
	delete character;
	delete passport;
}

bool Game::init()
{
	//passport initialising
	character = new sf::Sprite;
	passport = new sf::Sprite;

	if (!acceptStamp_texture.loadFromFile("../Data/Images/Critter Crossing Customs/accept.png"))
	{
		std::cout << "accept texture did not load\n";
	}
	acceptStamp.setTexture(acceptStamp_texture);
	acceptStamp.setScale(1, 1);

	if (!rejectStamp_texture.loadFromFile("../Data/Images/Critter Crossing Customs/reject.png"))
	{
		std::cout << "reject texture did not load\n";
	}
	rejectStamp.setTexture(rejectStamp_texture);
	rejectStamp.setScale(1, 1);

	//accept btn initialising
	if (!accept_texture.loadFromFile("../Data/Images/Critter Crossing Customs/accept button.png"))
	{
		std::cout << "accept button texture did not load\n";
	}
	accept.setTexture(accept_texture);
	accept.setScale(1, 1);
	accept.setPosition(window.getSize().x / 1.5, window.getSize().y / 1.5);
	//reject btn initialising
	if (!reject_texture.loadFromFile("../Data/Images/Critter Crossing Customs/reject button.png"))
	{
		std::cout << "reject button texture did not load\n";
	}
	reject.setTexture(reject_texture);
	reject.setScale(1, 1);
	reject.setPosition(window.getSize().x / 1.5, window.getSize().y / 1.2);

	//background initialising
	if (!background_texture.loadFromFile("../Data/WhackaMole Worksheet/background.png"))
	{
		std::cout << "background texture did not load\n";
	}
	background.setTexture(background_texture);

	if (!animals[0].loadFromFile("../Data/Images/Critter Crossing Customs/moose.png"))
	{
		std::cout << "moose texture did not load\n";

	}
	character->setTexture(animals[0], true);

	if (!animals[1].loadFromFile("../Data/Images/Critter Crossing Customs/elephant.png"))
	{
		std::cout << "elephant texture did not load\n";
	}
	character->setTexture(animals[1], true);

	if (!animals[2].loadFromFile("../Data/Images/Critter Crossing Customs/penguin.png"))
	{
		std::cout << "penguin texture did not load\n";
	}
	character->setTexture(animals[2], true);

	if (!passports[0].loadFromFile("../Data/Images/Critter Crossing Customs/elephant passport.png"))
	{
		std::cout << "elephant passport texture did not load\n";
	}
	passport->setTexture(passports[0], true);

	if (!passports[1].loadFromFile("../Data/Images/Critter Crossing Customs/moose passport.png"))
	{
		std::cout << "moose passport texture did not load\n";
	}
	passport->setTexture(passports[1], true);

	if (!passports[2].loadFromFile("../Data/Images/Critter Crossing Customs/penguin passport.png"))
	{
		std::cout << "penguin passport texture did not load\n";
	}
	passport->setTexture(passports[2], true);

	//initialize the first animal
	newAnimal();

	return true;
}

void Game::update(float dt)
{
	dragSprite(dragged);
}

void Game::render()
{
	window.draw(background);
	window.draw(*character);
	window.draw(*passport);
	window.draw(accept);
	window.draw(reject);
	if (passport_accepted)
	{
		acceptStamp.setPosition(passport->getPosition().x + 50, passport->getPosition().y + 50); // Adjust position as needed
		window.draw(acceptStamp);
	}
	if (passport_rejected)
	{
		rejectStamp.setPosition(passport->getPosition().x + 50, passport->getPosition().y + 50); // Adjust position as needed
		window.draw(rejectStamp);
	}
}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
}

void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}
	character->setTexture(animals[animal_index], true);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);

	passport->setTexture(passports[passport_index]);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);
}

void Game::dragSprite(sf::Sprite* sprite)
{
	if (sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		sf::Vector2f drag_position = mouse_positionf - drag_offset;
		sprite->setPosition(drag_position.x, drag_position.y);
	}
}

void Game::mouseButtonPressed(sf::Event event)
{
	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
	sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

	if (character->getGlobalBounds().contains(mouse_positionf))
	{
		dragged = character;
		drag_offset = mouse_positionf - character->getPosition();
	}
	else if (passport->getGlobalBounds().contains(mouse_positionf))
	{
		dragged = passport;
		drag_offset = mouse_positionf - passport->getPosition();
	}
	else if (accept.getGlobalBounds().contains(mouse_positionf))
	{
		passport_accepted = true;
		passport_rejected = false;
	}
	else if (reject.getGlobalBounds().contains(mouse_positionf))
	{
		passport_rejected = true;
		passport_accepted = false;
	}
}

void Game::mouseButtonReleased(sf::Event event)
{
	dragged = nullptr;
}