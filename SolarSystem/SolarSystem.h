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

	D3DXVECTOR3* GetCurrentPos(){ return mpCurrent->GetPosition(); };

	void GoDownLevel();
	void GoUpLevel();
	void NextObject();
	void PrevObject();
private:
	Planetoid* mpBase;
	std::vector<int> mLevel;
	Planetoid* mpCurrent;

	D3DXVECTOR3 mPos;
};