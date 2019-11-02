#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <list>

int main()
{
	std::vector<sf::Drawable*> drawables;

	const float moveSpeed = 50.f;
	sf::RenderWindow stackWindow(sf::VideoMode(800, 600), "SFML works!");

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
	shape.setPosition(sf::Vector2f(stackWindow.getSize().x / 2.0f, stackWindow.getSize().y / 2.0f));

	sf::RectangleShape shape2(sf::Vector2f(50, 25));
	shape2.setFillColor(sf::Color::Yellow);

	sf::Sprite mySprite;
	sf::Texture myTexture;
	if (myTexture.loadFromFile("./FE_Lyn.png"))
	{
		mySprite.setTexture(myTexture);
	}

	sf::Clock clock;
	sf::Time lastFrameTime;

	drawables.push_back(&shape);
	drawables.push_back(&shape2);
	drawables.push_back(&mySprite);

	while (stackWindow.isOpen())
	{
		//Game Loop
		sf::Time currentTime = clock.getElapsedTime();
		float deltaSeconds = (currentTime - lastFrameTime).asMicroseconds() / 1000.0f / 1000.0f;

		std::cout << deltaSeconds << "\n";

		sf::Event event;
		while (stackWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				stackWindow.close();
			}
		}

		sf::Vector2f moveVector;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			moveVector.y -= moveSpeed * deltaSeconds;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			moveVector.x -= moveSpeed * deltaSeconds;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			moveVector.y += moveSpeed * deltaSeconds;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			moveVector.x += moveSpeed * deltaSeconds;
		}

		std::vector<int> myVec; //List in C#
		std::list<int> myList; //Linked List in C#

		mySprite.move(moveVector);

		stackWindow.clear();

		//Display all drawables
		for (int i = 0; i < drawables.size(); i++)
		{
			stackWindow.draw(*drawables[i]);
		}

		stackWindow.display();

		lastFrameTime = currentTime;
	}

	return 0;
}