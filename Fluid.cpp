#include "Fluid.h"
#include <array>
#include "Constants.h"
#include "Physics.h"

#include <iostream>

int IX(int x, int y);
sf::Color Hsv(int hue, float sat, float val, float d);
float MapToRange(float val, float minIn, float maxIn, float minOut, float maxOut);

Fluid::Fluid(float diffusion, float viscosity, float dt)
{
	this->dt = dt;
	this->diff = diffusion;
	this->visc = viscosity;

	// create vectors with size N*N filled with 0
	//this->cells.resize(N * N, sf::RectangleShape(sf::Vector2f(SCALE, SCALE)));

	this->s.resize(N * N, 0);

	this->density.resize(N * N, 5);

	this->Vx.resize(N * N, 0);
	this->Vy.resize(N * N, 0);

	this->Vx0.resize(N * N, 0);
	this->Vy0.resize(N * N, 0);


	sf::VertexArray cellVertexArray(sf::Quads);

	// create particles
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int x = i * SCALE;
			int y = j * SCALE;

			float s = SCALE / 2.0f;

			sf::Vertex v1(sf::Vector2f(x - s, y - s));
			sf::Vertex v2(sf::Vector2f(x - s, y + s));
			sf::Vertex v3(sf::Vector2f(x + s, y + s));
			sf::Vertex v4(sf::Vector2f(x + s, y - s));

			// random colors
			v1.color = v2.color = v3.color = v4.color = sf::Color::White;

			// add to vertex array
			cellVertexArray.append(v1);
			cellVertexArray.append(v2);
			cellVertexArray.append(v3);
			cellVertexArray.append(v4);

			int index = IX(i, j);
		}
	}

	// set vertex array
	this->vertexArray = cellVertexArray;
}


void Fluid::AddDensity(int x, int y, float amount)
{
	this->density[IX(x, y)] += amount;
}

void Fluid::AddVelocity(int x, int y, float amountX, float amountY)
{
	this->Vx[IX(x, y)] += amountX;
	this->Vy[IX(x, y)] += amountY;
}

void Fluid::Step()
{
	Physics::Diffuse(1, this->Vx0, this->Vx, this->visc, this->dt);
	Physics::Diffuse(2, this->Vy0, this->Vy, this->visc, this->dt);

	Physics::Project(this->Vx0, this->Vy0, this->Vx, this->Vy);

	Physics::Advection(1, this->Vx, this->Vx0, this->Vx0, this->Vy0, this->dt);
	Physics::Advection(2, this->Vy, this->Vy0, this->Vx0, this->Vy0, dt);

	Physics::Project(this->Vx, this->Vy, this->Vx0, this->Vy0);

	Physics::Diffuse(0, this->s, this->density, this->diff, this->dt);
	Physics::Advection(0, this->density, this->s, this->Vx, this->Vy, this->dt);
}

void Fluid::RenderDensity(sf::RenderWindow& window)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int index = IX(i, j);

			float d = this->density[index];

			sf::Color newColor = Hsv(d, 1, 1, 255);

			// update vertex colors
			vertexArray[index * 4].color = newColor;
			vertexArray[index * 4 + 1].color = newColor;
			vertexArray[index * 4 + 2].color = newColor;
			vertexArray[index * 4 + 3].color = newColor;
		}
	}

	window.draw(this->vertexArray);
}

void Fluid::RenderVelocity(sf::RenderWindow& window)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int index = IX(i, j);
			float vx = this->Vx[index];
			float vy = this->Vy[index];
			int r = MapToRange(vx, -0.05f, 0.05f, 0, 255);
			int g = MapToRange(vy, -0.05f, 0.05f, 0, 255);

			sf::Color newColor = sf::Color(r, g, 255);

			// update vertex colors
			vertexArray[index * 4].color = newColor;
			vertexArray[index * 4 + 1].color = newColor;
			vertexArray[index * 4 + 2].color = newColor;
			vertexArray[index * 4 + 3].color = newColor;
		}
	}

	window.draw(this->vertexArray);
}

void Fluid::RenderDefault(sf::RenderWindow& window)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int index = IX(i, j);

			float d = std::min(255.f, this->density[index]);

			sf::Color newColor = sf::Color(255, 255, 255, d);

			// update vertex colors
			vertexArray[index * 4].color = newColor;
			vertexArray[index * 4 + 1].color = newColor;
			vertexArray[index * 4 + 2].color = newColor;
			vertexArray[index * 4 + 3].color = newColor;
		}
	}

	window.draw(this->vertexArray);
}