#include "Moon.h"

Moon::Moon(D3DXVECTOR3* pOrigin, float radius) :Planetoid(pOrigin, radius)
{
	create();
};
Moon::~Moon(){};

void Moon::create()
{
	D3DXCreateSphere(gd3dDevice, 1, 6, 6, &mObject, 0);
	load();
};
void Moon::render()
{
	worldMatrix();
	HR(gd3dDevice->SetTransform(D3DTS_WORLD, &mWorldMatix));
	HR(gd3dDevice->SetTransform(D3DTS_WORLD, &mWorldMatix));
	HR(mObject->DrawSubset(0));
};