#pragma once
#include "Planetoid.h"

class Earth : public Planetoid
{
public:
	Earth(D3DXVECTOR3* pOrigin, float radius);
	~Earth();

	void create();
	void render();
};