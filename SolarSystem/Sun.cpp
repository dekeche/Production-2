#include "Sun.h"
#include "Earth.h"
#include "Water.h"

Sun::Sun(D3DXVECTOR3* pOrigin):Planetoid(pOrigin,0)
{
	create();
};
Sun::~Sun()
{};

void Sun::create()
{
	Planetoid* earth = new Earth(&mPosition, 5);
	Planetoid* water = new Water(&mPosition, 8);
	SubPlanetoids.push_back(earth);
	SubPlanetoids.push_back(water);
	
	D3DXCreateSphere(gd3dDevice, 3, 6, 6, &mObject, 0);
	load();
};
void Sun::render()
{
	worldMatrix();
	HR(gd3dDevice->SetTransform(D3DTS_WORLD, &mWorldMatix));
	HR(mObject->DrawSubset(0));
	SubPlanetoids[0]->render();
	SubPlanetoids[1]->render();
};