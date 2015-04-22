#pragma once
#include "Planetoid.h"

class Water : public Planetoid
{
public:
	Water(D3DXVECTOR3* pOrigin, float radius);
	~Water();

	void create();
	void render();
private:
};