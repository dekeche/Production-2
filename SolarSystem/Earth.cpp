#include "Earth.h"
#include "Moon.h"

Earth::Earth(D3DXVECTOR3* pOrigin, float radius) :Planetoid(pOrigin, radius)
{
	create();
};
Earth::~Earth()
{
	delete SubPlanetoids[0];
};

void Earth::create()
{
	D3DXCreateSphere(gd3dDevice, 2, 6, 6, &mObject, 0);

	Planetoid* moon = new Moon(&mPosition,2);
	SubPlanetoids.push_back(moon);
	load();
};
void Earth::render()
{
	worldMatrix();
	HR(gd3dDevice->SetTransform(D3DTS_WORLD, &mWorldMatix));
	HR(mObject->DrawSubset(0));
	SubPlanetoids[0]->render();
};