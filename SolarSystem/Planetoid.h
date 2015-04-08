#pragma once
#include "TextureList.h"
#include <vector>

class Planetoid
{
public:
	Planetoid();
	~Planetoid();

	virtual void create();

	D3DXVECTOR3* Viewing();

	void ViewNext();
	void GoDownLevel();

	void update();
	virtual void render();

protected:

	int currentlyViewing;

	ID3DXMesh* mObject;
	//pointer to the objects 
	D3DXVECTOR3* mpOrigin;
	D3DXVECTOR3 mPosition;

	//matrix containting rotation
	D3DXMATRIX mMovement;
	D3DXMATRIX mRotation;
	float mAngle;
	float mRotationFactor;


	std::vector <Planetoid*> SubPlanetoids;
};