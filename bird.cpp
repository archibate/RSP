#include <iostream>
#include <array>

using namespace std;

class Brain {
	float x1x, x1y;
	float y1x, y1y;

	float zx, zy;

public:
	float calc(float x0, float y0)
	{
		float x1 = x1x * x0 + x1y * y0;
		float y1 = y1x * x0 + y1y * y0;

		return zx * x1 + zy * y1;
	}
};

class Bird {
public:
	Brain *brain;
	float y;

	Bird() : y(0)
	{}

	void doMove(float x, float dy)
	{
		if (brain->calc(x, y) > 0)
			y += dy;
	}
};

#define NR_BIRDS 8
#define DX 0.01f
#define DY 0.08f

int main()
{
	array<Brain, NR_BIRDS> brains;
	array<Bird, NR_BIRDS> birds;

	for (int i = 0; i < NR_BIRDS; i++) {
		birds[i].brain = &brains[i];
	}

again:
	float rest = 1.0f;
	for (auto &bird: birds) {
		bird.doMove(rest, DY);
		rest -= DX;
		if (rest < 0)
			goto again;
	}
};
