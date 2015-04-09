#pragma once
#include "Planetoid.h"
class SolarSystem
{
public:
	SolarSystem();
	~SolarSystem();

	void create();
	void update(float dt);
	void render();

	void GoDownLevel();
	void GoUpLevel();
	void NextObject();
	void PrevObject();
private:
	Planetoid* mpBase;
	std::vector<int> mLevel;
	Planetoid* mpCurrent;
};