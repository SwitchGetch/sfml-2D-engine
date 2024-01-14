#include "Includes.h"
#include "Classes.h"
#include "Functions.h"
#include "Enums.h"
#include "Defines.h"

int main()
{
	RenderWindow window(VideoMode(1000, 750), "");
	window.setFramerateLimit(60);

	menu(window);
}