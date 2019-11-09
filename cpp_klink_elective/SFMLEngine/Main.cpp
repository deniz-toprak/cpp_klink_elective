#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <list>

#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

struct EntityId
{
	EntityId()
		: index(0)
		, salt(0)
	{ }

	EntityId(sf::Uint16 _index, sf::Uint16 _salt)
		: index(_index)
		, salt(_salt)
	{ }

	sf::Uint16 index;
	sf::Uint16 salt;

	bool operator==(EntityId& rhs) const
	{
		return index == rhs.index && salt == rhs.salt;
	}
};

EntityId s_invalidEntityId = EntityId();

class Entity
{
public:

	EntityId myId;
	std::string name;

	sf::Drawable* pDrawable = nullptr;

	bool IsAlive() const
	{
		return myId.index != s_invalidEntityId.index;
	}
};

std::array<Entity, std::numeric_limits<sf::Uint16>::max()> entities;


EntityId AddEntity()
{
	for (int i = 1; i < entities.size(); i++)
	{
		const bool isAlive = entities[i].IsAlive();
		if (!isAlive)
		{
			EntityId newId(i, entities[i].myId.salt + 1);
			entities[i].myId = newId;
			return newId;
		}
	}

	return EntityId();
}

Entity* GetEntityByID(EntityId id)
{
	if (id.index == 0 || id.salt == 0)
	{
		return nullptr;
	}

	if (entities[id.index].IsAlive() && entities[id.index].myId.salt == id.salt)
	{
		//salt values match, reffering to same entity
		return &entities[id.index];
	}
	return nullptr;
}

bool DestroyEntity(EntityId id)
{
	Entity* pEntity = GetEntityByID(id);
	if (pEntity != nullptr)
	{
		pEntity->myId.index = 0;
		return false;
	}

	return false;
}

int main()
{
	//random generator
	srand(time(0));

	std::vector<EntityId> entityIds;

	const float moveSpeed = 50.f;
	sf::RenderWindow stackWindow(sf::VideoMode(800, 600), "SFML works!");

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
	shape.setPosition(sf::Vector2f(stackWindow.getSize().x / 2.0f, stackWindow.getSize().y / 2.0f));

	//Create circle shapes
	entityIds.push_back(AddEntity());
	GetEntityByID(entityIds.back())->pDrawable = &shape;

	//Create rectangle shapes
	sf::RectangleShape shape2(sf::Vector2f(50, 25));
	shape2.setFillColor(sf::Color::Yellow);

	entityIds.push_back(AddEntity());
	GetEntityByID(entityIds.back())->pDrawable = &shape2;

	//Create sprite shapes
	sf::Sprite mySprite;
	sf::Texture myTexture;
	if (myTexture.loadFromFile("./FE_Lyn.png"))
	{
		mySprite.setTexture(myTexture);
	}

	entityIds.push_back(AddEntity());
	GetEntityByID(entityIds.back())->pDrawable = &mySprite;

	//Create random circle
	sf::CircleShape cshape((rand() % 100) + 1);
	cshape.setFillColor(sf::Color::Green);
	cshape.setOrigin(sf::Vector2f(cshape.getRadius(), cshape.getRadius()));
	cshape.setPosition(
		sf::Vector2f(
		(rand() % stackWindow.getSize().x),
			(rand() % stackWindow.getSize().y)
		)
	);

	entityIds.push_back(AddEntity());
	GetEntityByID(entityIds.back())->pDrawable = &cshape;

	sf::Clock clock;
	sf::Time lastFrameTime;

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


		DestroyEntity(entityIds.back());

		sf::CircleShape cshape((rand() % 100) + 1);
		cshape.setFillColor(sf::Color::Green);
		cshape.setOrigin(sf::Vector2f(cshape.getRadius(), cshape.getRadius()));
		cshape.setPosition(
			sf::Vector2f(
			(rand() % stackWindow.getSize().x),
				(rand() % stackWindow.getSize().y)
			)
		);

		entityIds.push_back(AddEntity());
		GetEntityByID(entityIds.back())->pDrawable = &cshape;

		

		




		stackWindow.clear();

		//Display all drawables
		for (int i = 0; i < entityIds.size(); i++)
		{
			Entity* pEntity = GetEntityByID(entityIds[i]);
			if (pEntity)
			{
				stackWindow.draw(*pEntity->pDrawable);

			}
		}

		stackWindow.display();

		lastFrameTime = currentTime;
	}

	return 0;
}