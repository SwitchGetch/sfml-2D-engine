#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Object
{
	RectangleShape object;

public:

	Vector2f size;
	Vector2f position;
	Color color;

	Object() = default;

	Object(Vector2f size, Vector2f position, Color color) : size(size), position(position), color(color) {}

	RectangleShape getShape()
	{
		object.setSize(size);
		object.setPosition(position);
		object.setFillColor(color);

		return object;
	}
};

class Player
{
	RectangleShape player;

	void collision(Object& object)
	{
		double minX = min(position.x, object.position.x);
		double minY = min(position.y, object.position.y);
		double maxX = max(position.x + size.x, object.position.x + object.size.x);
		double maxY = max(position.y + size.y, object.position.y + object.size.y);

		double sideX = maxX - minX;
		double sideY = maxY - minY;

		if (sideX < size.x + object.size.x && sideY < size.y + object.size.y)
		{
			double x = size.x + object.size.x - sideX;
			double y = size.y + object.size.y - sideY;

			if (x <= y)
			{
				if (minX == position.x) position.x = object.position.x - size.x;
				else position.x = object.position.x + object.size.x;
			}

			if (x >= y)
			{
				if (minY == position.y) position.y = object.position.y - size.y;
				else position.y = object.position.y + object.size.y;
			}
		}
	}

public:

	Vector2f size;
	Vector2f position;
	Color color;

	Player() = default;

	Player(Vector2f size, Vector2f position, Color color) : size(size), position(position), color(color) {}

	RectangleShape getShape()
	{
		player.setSize(size);
		player.setPosition(position);
		player.setFillColor(color);

		return player;
	}

	void move(RenderWindow& window, vector<Object>& objects)
	{
		if (position.x < 0) position.x = 0;
		if (position.x + size.x > window.getSize().x) position.x = window.getSize().x - size.x;
		if (position.y < 0) position.y = 0;
		if (position.y + size.y > window.getSize().y) position.y = window.getSize().y - size.y;

		for (int i = 0; i < objects.size(); i++)
		{
			double minX = min(position.x, objects[i].position.x);
			double minY = min(position.y, objects[i].position.y);
			double maxX = max(position.x + size.x, objects[i].position.x + objects[i].size.x);
			double maxY = max(position.y + size.y, objects[i].position.y + objects[i].size.y);

			double sideX = maxX - minX;
			double sideY = maxY - minY;

			if (sideX < size.x + objects[i].size.x && sideY < size.y + objects[i].size.y)
			{
				double x = size.x + objects[i].size.x - sideX;
				double y = size.y + objects[i].size.y - sideY;

				if (x <= y)
				{
					if (minX == position.x) position.x = objects[i].position.x - size.x;
					else position.x = objects[i].position.x + objects[i].size.x;
				}

				if (x >= y)
				{
					if (minY == position.y) position.y = objects[i].position.y - size.y;
					else position.y = objects[i].position.y + objects[i].size.y;
				}
			}
		}
	}
};

int main()
{
	RenderWindow window(VideoMode(1000, 750), "");
	window.setFramerateLimit(60);

	Player player(Vector2f(100, 100), Vector2f(100, 100), Color::Red);

	vector<Object> objects
	{
		Object(Vector2f(50, 50), Vector2f(50, 100), Color::Blue),
		Object(Vector2f(50, 50), Vector2f(200, 150), Color::Green),
		Object(Vector2f(50, 50), Vector2f(350, 400), Color::Cyan),
		Object(Vector2f(50, 50), Vector2f(600, 550), Color::Yellow)
	};

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::KeyPressed)
			{
				switch (event.key.scancode)
				{

				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			player.position.y += -5;
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			player.position.x += -5;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player.position.y += 5;
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			player.position.x += 5;
		}

		player.move(window, objects);


		window.clear();

		window.draw(player.getShape());
		for (int i = 0; i < objects.size(); i++) window.draw(objects[i].getShape());

		window.display();
	}
}
