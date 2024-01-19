#pragma once

#include "Enums.h"

class ObjectStat
{
public:

	int index;
	Direction dx = None;
	Direction dy = None;
};

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

	bool isStanding()
	{
		/*double minX, minY, maxX, maxY, sideX, sideY;
	
		for (int i = 0; i < objects.size(); i++)
		{
			minX = min(position.x, objects[i].position.x);
			minY = min(position.y, objects[i].position.y);
			maxX = max(position.x + size.x, objects[i].position.x + objects[i].size.x);
			maxY = max(position.y + size.y, objects[i].position.y + objects[i].size.y);
	
			sideX = maxX - minX;
			sideY = maxY - minY;
	
			if (
				(sideX <= size.x + objects[i].size.x && sideY <= size.y + objects[i].size.y) &&
				(
				acceleration.x > 0 && minX == position.x ||
				acceleration.x < 0 && maxX == position.x + size.x ||
				acceleration.y > 0 && minY == position.y ||
				acceleration.y < 0 && maxY == position.y + size.y
					)
				)
			{
				return true;
			}
		}

		return false;*/

		return standing;
	}

	void move(vector<Object>& objects)
	{
		double minX, minY, maxX, maxY, sideX, sideY, x, y;
		vector<ObjectStat> collisions;
		int vector_size;

		position += speed;
		speed += acceleration;

		vector_size = objects.size();
		for (int i = 0; i < vector_size; i++)
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

				ObjectStat collision;
				collision.index = i;

				if (x >= y)
				{

				}

				if (x <= y)
				{

				}


				/*if (objects[i].type == ObjectType::Dangerous)
				{
					size = start_size;
					position = start_position;
					speed = start_speed;
					acceleration = start_acceleration;

					break;
				}

				x = size.x + objects[i].size.x - sideX;
				y = size.y + objects[i].size.y - sideY;

				if (x >= y)
				{
					if (minY == position.y)
					{
						position.y = objects[i].position.y - size.y;
					}
					else
					{
						position.y = objects[i].position.y + objects[i].size.y;
					}

					speed.y = 0;
				}

				if (x <= y)
				{
					if (minX == position.x)
					{
						position.x = objects[i].position.x - size.x;
					}
					else
					{
						position.x = objects[i].position.x + objects[i].size.x;
					}

					speed.x = 0;
				}*/
			}
		}

		vector_size = index.size();
		for (int i = 0; i < vector_size; i++)
		{
			minX = min(position.x, objects[index[i]].position.x);
			minY = min(position.y, objects[index[i]].position.y);
			maxX = max(position.x + size.x, objects[index[i]].position.x + objects[index[i]].size.x);
			maxY = max(position.y + size.y, objects[index[i]].position.y + objects[index[i]].size.y);

			sideX = maxX - minX;
			sideY = maxY - minY;

			x = size.x + objects[index[i]].size.x - sideX;
			y = size.y + objects[index[i]].size.y - sideY;
		}
	}
};
