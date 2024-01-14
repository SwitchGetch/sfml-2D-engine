#pragma once

#include "Enums.h"

class Object
{
	RectangleShape object;

public:

	Vector2f size;
	Vector2f position;
	ObjectType type;
	Texture texture;

	Object() = default;

	Object(Vector2f size, Vector2f position, ObjectType type, string texture_file_name) : size(size), position(position), type(type)
	{
		texture.loadFromFile(texture_file_name);
		object.setTexture(&texture);
	}

	RectangleShape getShape()
	{
		object.setSize(size);
		object.setPosition(position);

		return object;
	}
};

class Player
{
	RectangleShape player;
	bool standing = false;

	Vector2f start_size;
	Vector2f start_position;
	Vector2f start_speed;
	Vector2f start_acceleration;

public:

	Vector2f size;
	Vector2f position;
	Vector2f speed;
	Vector2f acceleration;
	Texture texture;

	Player() = default;

	Player(Vector2f size, Vector2f position, Vector2f speed, Vector2f acceleration, string texture_file_name) :
		size(size), position(position), speed(speed), acceleration(acceleration),
		start_size(size), start_position(position), start_speed(speed), start_acceleration(acceleration)
	{
		texture.loadFromFile(texture_file_name);
		player.setTexture(&texture);
	}

	RectangleShape getShape()
	{
		player.setSize(size);
		player.setPosition(position);

		return player;
	}

	bool isStanding(vector<Object>& objects)
	{
		return standing;
	}

	void move(RenderWindow& window, vector<Object>& objects)
	{
		bool changed = false;

		/*if (position.x < 0)
		{
			position.x = 0;
			speed.x = 0;

			if (acceleration.x && !standing) standing = acceleration.x < 0;
		}
		if (position.x + size.x > window.getSize().x)
		{
			position.x = window.getSize().x - size.x;
			speed.x = 0;

			if (acceleration.x && !standing) standing = acceleration.x > 0;
		}
		if (position.y < 0)
		{
			position.y = 0;
			speed.y = 0;

			if (acceleration.y && !standing) standing = acceleration.y < 0;
		}
		if (position.y + size.y > window.getSize().y)
		{
			position.y = window.getSize().y - size.y;
			speed.y = 0;

			if (acceleration.y && !standing) standing = acceleration.y > 0;
		}*/

		double minX, minY, maxX, maxY, sideX, sideY, x, y;

		for (int i = 0; i < objects.size(); i++)
		{
			minX = min(position.x, objects[i].position.x);
			minY = min(position.y, objects[i].position.y);
			maxX = max(position.x + size.x, objects[i].position.x + objects[i].size.x);
			maxY = max(position.y + size.y, objects[i].position.y + objects[i].size.y);

			sideX = maxX - minX;
			sideY = maxY - minY;

			if (sideX < size.x + objects[i].size.x && sideY < size.y + objects[i].size.y)
			{
				x = size.x + objects[i].size.x - sideX;
				y = size.y + objects[i].size.y - sideY;

				if (x <= y)
				{
					if (minX == position.x)
					{
						position.x = objects[i].position.x - size.x;

						if (acceleration.x && !changed)
						{
							standing = acceleration.x > 0;
							changed = true;
						}
					}
					else
					{
						position.x = objects[i].position.x + objects[i].size.x;

						if (acceleration.x && !changed)
						{
							standing = acceleration.x < 0;
							changed = true;
						}
					}

					speed.x = 0;
				}

				if (x >= y)
				{
					if (minY == position.y)
					{
						position.y = objects[i].position.y - size.y;

						if (acceleration.y && !changed)
						{
							standing = acceleration.y > 0;
							changed = true;
						}
					}
					else
					{
						position.y = objects[i].position.y + objects[i].size.y;

						if (acceleration.y && !changed)
						{
							standing = acceleration.y < 0;
							changed = true;
						}
					}

					speed.y = 0;
				}

				if (objects[i].type == ObjectType::Dangerous)
				{
					size = start_size;
					position = start_position;
					speed = start_speed;
					acceleration = start_acceleration;

					break;
				}
			}
		}
	}
};
