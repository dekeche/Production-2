#include "Planetoid.h"
const float MAXRADIANS = 2 * D3DX_PI;
Planetoid::Planetoid(D3DXVECTOR3* pOrigin)
{
	mpOrigin = pOrigin;
	create();
};
Planetoid::~Planetoid(){};

void Planetoid::update(float dt)
{
	mOrbitAngle += mAnglePerSecondOrbit*dt;
	mRotationAngle += mAnglePerSecondRotation*dt;
	if (mOrbitAngle > MAXRADIANS)
	{
		mOrbitAngle -= MAXRADIANS;
	}
	else if (mOrbitAngle < 0)
	{
		mOrbitAngle += MAXRADIANS;
	}
	if (mRotationAngle > MAXRADIANS)
	{
		mRotationAngle -= MAXRADIANS;
	}
	else if (mRotationAngle < 0)
	{
		mRotationAngle += MAXRADIANS;
	}

	D3DXMatrixRotationAxis(&mOrbitMatrix, &mOrbitAxis, mOrbitAngle);
	D3DXMatrixRotationAxis(&mRotationMatrix, &mRotationAxis, mRotationAngle);

	D3DXVECTOR3 origin(mRadius, 0, 0);
	D3DXVec3TransformCoord(&mPosition, &origin, &mOrbitMatrix);
	for (int i = 0; i < SubPlanetoids.size(); i++)
	{
		SubPlanetoids[i]->update(dt);
	}
};
