#pragma once

void level(RenderWindow& window), menu(RenderWindow& window);

string getPlayerStats(Player player)
{
    return
        " size:\n x: " + to_string(player.size.x) + "\n y: " + to_string(player.size.y) +
        "\n\n position:\n x: " + to_string(player.position.x) + "\n y: " + to_string(player.position.y) +
        "\n\n speed:\n x: " + to_string(player.speed.x) + "\n y: " + to_string(player.speed.y) +
        "\n\n acceleration:\n x: " + to_string(player.acceleration.x) + "\n y: " + to_string(player.acceleration.y) +
        "\n\n standing: " + (player.isStanding() ? "true" : "false");
}


void menu(RenderWindow& window)
{
	Font font;
	Text text;

	font.loadFromFile("Fonts/ARLRDBD.TTF");
	text.setFont(font);
	text.setString(" PRESS SPACE TO PLAY\n PRESS ESC TO EXIT");

	while (true)
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

				case Keyboard::Scancode::Space:

					return level(window);

				case Keyboard::Scancode::Escape:

					return;
				}
			}
		}

		window.clear(Color(66, 135, 245));

		window.draw(text);

		window.display();
	}
}


void level(RenderWindow& window)
{
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;

	Player player(Vector2f(100, 100), Vector2f(0, 450), Vector2f(0, 0), Vector2f(0, 1), "Textures/player.png");

	Font font;
	Text text;
	bool stats_output = false;

	font.loadFromFile("Fonts/ARLRDBD.TTF");
	text.setFont(font);

	Object ob0(Vector2f(400, 50), Vector2f(500, 250), ObjectType::Safe, "Textures/wood.png");
	Object ob1(Vector2f(200, 100), Vector2f(100, 350), ObjectType::Safe, "Textures/grass.png");
	Object ob2(Vector2f(200, 100), Vector2f(300, 450), ObjectType::Safe, "Textures/grass.png");
	Object ob3(Vector2f(200, 100), Vector2f(500, 550), ObjectType::Safe, "Textures/grass.png");
	Object ob4(Vector2f(100, 100), Vector2f(800, 650), ObjectType::Safe, "Textures/grass.png");
	Object ob5(Vector2f(100, 100), Vector2f(200, 450), ObjectType::Safe, "Textures/dirt.png");
	Object ob6(Vector2f(100, 100), Vector2f(400, 550), ObjectType::Safe, "Textures/dirt.png");
	Object ob7(Vector2f(300, 100), Vector2f(0, 650), ObjectType::Safe, "Textures/dirt.png");
	Object ob8(Vector2f(100, 100), Vector2f(0, 550), ObjectType::Safe, "Textures/dirt.png");
	Object ob9(Vector2f(100, 100), Vector2f(0, 250), ObjectType::Safe, "Textures/grass.png");
	Object ob10(Vector2f(100, 100), Vector2f(250, 150), ObjectType::Safe, "Textures/wood.png");
	Object ob11(Vector2f(100, 100), Vector2f(0, 350), ObjectType::Safe, "Textures/dirt.png");
	Object ob12(Vector2f(100, 100), Vector2f(900, 650), ObjectType::Dangerous, "Textures/spikes.png");
	vector<Object> objects{ ob0, ob1, ob2, ob3, ob4, ob5, ob6, ob7, ob8, ob9, ob10, ob11, ob12 };

	Object bg0(Vector2f(200, 100), Vector2f(0, 450), ObjectType::Safe, "Textures/bg_dirt.png");
	Object bg1(Vector2f(300, 100), Vector2f(100, 550), ObjectType::Safe, "Textures/bg_dirt.png");
	Object bg2(Vector2f(500, 100), Vector2f(300, 650), ObjectType::Safe, "Textures/bg_dirt.png");
	vector<Object> background{ bg0, bg1, bg2 };

	while (true)
	{
		start = high_resolution_clock::now();

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
				case Keyboard::Scancode::F:

					stats_output = (stats_output ? false : true);

					break;

				case Keyboard::Scancode::Escape:

					return menu(window);
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) player.position.x += -5;
		if (Keyboard::isKeyPressed(Keyboard::D)) player.position.x += 5;

		if (player.isStanding())
		{
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				if (player.acceleration.y) player.speed.y = 15 * (player.acceleration.y > 0 ? -1 : 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.acceleration.y = -1;
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.acceleration.y = 1;
			}
		}

		player.position += player.speed;
		player.speed += player.acceleration;

		player.move(window, objects);


		if (player.acceleration.y)
		{
			window.clear((player.acceleration.y > 0 ? Color(66, 135, 245) : Color(235, 158, 52)));
		}

		for (int i = 0; i < background.size(); i++) window.draw(background[i].getShape());
		window.draw(player.getShape());
		for (int i = 0; i < objects.size(); i++) window.draw(objects[i].getShape());

		if (stats_output)
		{
			text.setString(getPlayerStats(player));
			window.draw(text);
		}

		window.display();


		end = high_resolution_clock::now();

		window.setTitle("FPS: " + to_string(1e9f / duration_cast<chrono::nanoseconds>(end - start).count()));
	}
}
