#pragma once
#include <vector>

class Physics
{
private:
	static void SetBound(int b, std::vector<float>& x);

	static void LinearSolve(int b, std::vector<float>& x, std::vector<float>& x0, float a, float c);

public:
	static void Diffuse(int b, std::vector<float>& x, std::vector<float>& x0, float& diff, float dt);

	static void Project(std::vector<float>& velocX, std::vector<float>& velocY, std::vector<float>& p, std::vector<float>& div);

	static void Advection(int b, std::vector<float>& d, std::vector<float>& d0, std::vector<float>& velocX, std::vector<float>& velocY, float dt);
};

