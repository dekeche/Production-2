#include "Water.h"

Water::Water(D3DXVECTOR3* pOrigin, float radius) :Planetoid(pOrigin, radius)
{
	create();
};
Water::~Water(){};

void Water::create()
{
	D3DXCreateSphere(gd3dDevice, 2, 6, 6, &mObject, 0);
	load();
};
void Water::render()
{
	worldMatrix();
	HR(gd3dDevice->SetTransform(D3DTS_WORLD, &mWorldMatix));
	HR(mObject->DrawSubset(0));
};