#pragma once
#include "Planetoid.h"

class Moon: public Planetoid
{
public:
	Moon(D3DXVECTOR3* pOrigin, float radius);
	~Moon();

	void create();
	void render();
private:
};