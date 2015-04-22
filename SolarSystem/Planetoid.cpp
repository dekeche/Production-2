#include "Planetoid.h"
const float MAXRADIANS = 2 * D3DX_PI;
Planetoid::Planetoid(D3DXMATRIX* pLocalMatrix, D3DXVECTOR3* pOrigin, float radius)
{
	mpLocalMatrix = pLocalMatrix;
	mpOrigin = pOrigin;
	mRadius = radius;
};
Planetoid::~Planetoid()
{
	for (int i = 0; i < SubPlanetoids.size(); i++)
	{
		if (SubPlanetoids[i] != 0)
			delete SubPlanetoids[i];
	}
	SubPlanetoids.empty();
};

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
void Planetoid::load()
{
	ID3DXMesh* clone = 0;

	D3DVERTEXELEMENT9 elements[64];
	UINT numElements = 0;
	VertexNMap::Decl->GetDeclaration(elements, &numElements);
	HR(mObject->CloneMesh(D3DXMESH_SYSTEMMEM, elements, gd3dDevice, &clone));

	ReleaseCOM(mObject);

	VertexNMap* vertices = 0;
	HR(clone->LockVertexBuffer(0, (void**)&vertices));

	for (UINT i = 0; i < clone->GetNumVertices(); i++)
	{
		D3DXVECTOR3 p = vertices[i].pos;

		float theta = atan2f(p.z, p.x) + D3DX_PI;
		float phi = acosf(p.y / sqrtf(p.x*p.x + p.y*p.y + p.z*p.z));

		float u = theta / (2.0f*(D3DX_PI));
		float v = phi / D3DX_PI;

		vertices[i].tex0.x = u;
		vertices[i].tex0.y = v;
	}

	HR(clone->UnlockVertexBuffer());

	ID3DXMesh* TNB;
	HR(clone->CloneMesh(D3DXMESH_MANAGED, elements, gd3dDevice, &TNB));
	ReleaseCOM(clone);
	HR(D3DXComputeTangentFrameEx(TNB, D3DDECLUSAGE_TEXCOORD, 0,
		D3DDECLUSAGE_BINORMAL, 0, D3DDECLUSAGE_TANGENT, 0,
		D3DDECLUSAGE_NORMAL, 0, 0, 0, 0.01f, 0.25f, 0.01f,
		&mObject, 0));

	ReleaseCOM(TNB);
	int mVerts = mObject->GetNumVertices();
	int mTris = mObject->GetNumFaces();
	GfxStats::GetInstance()->addVertices(mVerts);
	GfxStats::GetInstance()->addTriangles(mTris);
}
void Planetoid::worldMatrix()
{
	mWorldMatix = mOrbitMatrix;
}