#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "Fluid.h"
#include "Constants.h"

sf::Color BACKGROUND_COLOR(30, 30, 30);

float RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

float Clamp(float x, float min, float max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

int main()
{
	srand(time(NULL));

	// create a window & settings
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT, 32), "Fluid Simulation");
	sf::View view = window.getDefaultView();
	window.setFramerateLimit(FPS);


	// create fluid
	Fluid fluid(DIFFUSION, VISCOSITY, DT);

	// cycle through render modes
	int n = 0;

	// for random velocity vector
	int cx = 0.5 * N;
	int cy = 0.5 * N;
	float r = 3;
	float vx = RandomFloat(-r, r);
	float vy = RandomFloat(-r, r);

	// while the window is kept open
	while (window.isOpen())
	{
		// store and loop through each event
		sf::Event event;
		while (window.pollEvent(event))
		{
			// if closing window
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					n++;
				}
				break;

			default:
				break;
			}
		}


		// clear frame
		window.clear(BACKGROUND_COLOR);


		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				fluid.AddDensity(cx + i, cy + j, RandomFloat(25, 100));
			}
		}

		// generate a random velocity vector
		//vx += Clamp(RandomFloat(-r, r), -r, r);
		//vy += Clamp(RandomFloat(-r, r), -r, r);
		fluid.AddVelocity(cx, cy, vx, vy);

		fluid.Step();

		if (n % 3 == 0)
		{
			fluid.RenderDefault(window);
		}
		else if (n % 3 == 1)
		{
			fluid.RenderDensity(window);
		}
		else if (n % 3 == 2)
		{
			fluid.RenderVelocity(window);
		}

		// show frame / draw calls
		window.display();
	}

	return 0;
}