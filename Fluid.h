#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

struct Fluid
{
	float dt;
	float diff;
	float visc;

	std::vector<float> s;
	std::vector<float> density;

	std::vector<float> Vx;
	std::vector<float> Vy;

	std::vector<float> Vx0;
	std::vector<float> Vy0;

	sf::VertexArray vertexArray;

	/// <summary>
	/// Constructor for the Fluid class.
	/// </summary>
	/// <param name="diffusion">Amount the fluid should diffuse</param>
	/// <param name="viscosity">The viscosity of the fluid</param>
	/// <param name="dt">The delta time</param>
	Fluid(float diffusion, float viscosity, float dt);

	/// <summary>
	/// Add Density to the fluid at a given position.
	/// </summary>
	/// <param name="x">The x position in the grid</param>
	/// <param name="y">The y position in the grid</param>
	/// <param name="amount">Amount of density that should be added</param>
	void AddDensity(int x, int y, float amount);

	/// <summary>
	/// Add velocity to the fluid at a given position.
	/// </summary>
	/// <param name="x">The x position in the grid</param>
	/// <param name="y">The y position in the grid</param>
	/// <param name="amountX">The amount of speed in the X direction</param>
	/// <param name="amountY">The amount of speed in the Y direction</param>
	void AddVelocity(int x, int y, float amountX, float amountY);

	/// <summary>
	/// Do all the physics related calculations.
	/// </summary>
	void Step();

	/// <summary>
	/// Render the fluid density on to the window.
	/// </summary>
	/// <param name="window">The current window to render onto</param>
	void RenderDensity(sf::RenderWindow& window);

	/// <summary>
	/// Render the fluid velocity on to the window.
	/// </summary>
	/// <param name="window">The current window to render onto</param>
	void RenderVelocity(sf::RenderWindow& window);

	/// <summary>
	/// Render the fluid on to the window.
	/// </summary>
	/// <param name="window">The current window to render onto</param>
	void RenderDefault(sf::RenderWindow& window);
};

typedef struct Fluid Fluid;