#pragma once
#include "TextureList.h"
#include <vector>
#include "d3dUtil.h"
#include "GfxStats.h"
#include "d3dApp.h"
#include "Vertex.h"

class Planetoid
{
public:
	Planetoid(D3DXMATRIX* pLocalMatrix, D3DXVECTOR3* pOrigin, float radius);
	~Planetoid();

	virtual void create() = 0;
	virtual void render() = 0;
	void update(float dt);
	void load();
	void worldMatrix();

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

	D3DXMATRIX* mpLocalMatrix;
	D3DXMATRIX mWorldMatix;

	D3DXVECTOR3 mOrbitAxis;
	D3DXVECTOR3 mRotationAxis;
	float mAnglePerSecondRotation;
	float mAnglePerSecondOrbit;
	float mRadius;
	float mOrbitAngle;
	float mRotationAngle;


	std::vector <Planetoid*> SubPlanetoids;
};