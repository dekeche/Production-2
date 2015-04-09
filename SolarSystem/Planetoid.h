#pragma once
#include "TextureList.h"
#include <vector>

class Planetoid
{
public:
	Planetoid(D3DXVECTOR3* pOrigin);
	~Planetoid();

	virtual void create() = 0;
	void update(float dt);
	virtual void render() = 0;

	D3DXVECTOR3* GetPosition(){ return &mPosition; };
	float GetRadius(){ return mRadius; };
	std::vector<Planetoid*>* GetSubList(){ return &SubPlanetoids; };


protected:
	//0 is self, 
	int currentlyViewing;

	//pointer to the objects 
	ID3DXMesh* mObject;
	D3DXVECTOR3* mpOrigin;
	D3DXVECTOR3 mPosition;

	//matrix containting rotation
	//all assume that angle = 1;
	D3DXMATRIX mOrbitMatrix;
	D3DXMATRIX mRotationMatrix;

	D3DXVECTOR3 mOrbitAxis;
	D3DXVECTOR3 mRotationAxis;
	float mAnglePerSecondRotation;
	float mAnglePerSecondOrbit;
	float mRadius;
	float mOrbitAngle;
	float mRotationAngle;


	std::vector <Planetoid*> SubPlanetoids;
};