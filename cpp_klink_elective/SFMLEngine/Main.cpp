#include <SFML/Graphics.hpp>


int main()
{
	//Test
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	int i = 0;
	while (window.isOpen())
	{
		++i;
		switch (i)
		{
		case 0:
			shape.setFillColor(sf::Color::Green);
			break;
		case 1:
			shape.setFillColor(sf::Color::Red);
			break;
		case 2:
			shape.setFillColor(sf::Color::Yellow);
			break;
		case 3:
			shape.setFillColor(sf::Color::Blue);
			break;
		case 4:
			shape.setFillColor(sf::Color::White);
			i = 0;
			break;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}