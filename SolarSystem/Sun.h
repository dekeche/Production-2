#pragma once
#include "Planetoid.h"

class Sun : public Planetoid
{
public:
	Sun(D3DXVECTOR3* pOrigin);
	~Sun();

	void create();
	void render();
private:
};