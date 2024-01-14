#include "Includes.h"
#include "Classes.h"
#include "Functions.h"
#include "Enums.h"
#include "Defines.h"

int main()
{
	RenderWindow window(VideoMode(1800, 1000), "");
	window.setFramerateLimit(60);

	View view;

	menu(window, view);
}
