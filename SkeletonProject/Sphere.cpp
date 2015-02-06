//=============================================================================
//                              BaseObject3D
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendergin via Vertex and Index buffer
//=============================================================================
#define _USE_MATH_DEFINES
#include "Sphere.h"
#include "3DClasses\Vertex.h"
#include "GfxStats.h"
#include <math.h>
//=============================================================================
Sphere::Sphere(float radius, int sideFacetsNum) : BaseObject3D((sideFacetsNum*sideFacetsNum + 2),2*sideFacetsNum*sideFacetsNum)
{
	mRadius = radius;
	mSideFacetsNum = sideFacetsNum;

}

//-----------------------------------------------------------------------------
Sphere::~Sphere(void)
{
	ReleaseCOM(m_VertexBuffer);
	ReleaseCOM(m_IndexBuffer);
}

//-----------------------------------------------------------------------------
void Sphere::Create(IDirect3DDevice9* gd3dDevice)
{
	buildDemoCubeVertexBuffer(gd3dDevice);
	buildDemoCubeIndexBuffer(gd3dDevice);
}

//-----------------------------------------------------------------------------
void Sphere::Render(IDirect3DDevice9* gd3dDevice,
	D3DXMATRIX& view, D3DXMATRIX& projection)
{
	// Update the statistics singlton class
	GfxStats::GetInstance()->addVertices(8);
	GfxStats::GetInstance()->addTriangles(12);

	// Set the buffers and format
	HR(gd3dDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VertexPos)));
	HR(gd3dDevice->SetIndices(m_IndexBuffer));
	HR(gd3dDevice->SetVertexDeclaration(VertexPos::Decl));

	// Set matrices and model relevant render date
	HR(gd3dDevice->SetTransform(D3DTS_WORLD, &m_World));
	HR(gd3dDevice->SetTransform(D3DTS_VIEW, &view));
	HR(gd3dDevice->SetTransform(D3DTS_PROJECTION, &projection));

	// Send to render
	HR(gd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_VertexNum, 0, m_IndexNum));
}

//-----------------------------------------------------------------------------
void Sphere::buildDemoCubeVertexBuffer(IDirect3DDevice9* gd3dDevice)
{
	// Obtain a pointer to a new vertex buffer.
	HR(gd3dDevice->CreateVertexBuffer(m_VertexNum * sizeof(VertexPos), D3DUSAGE_WRITEONLY,
		0, D3DPOOL_MANAGED, &m_VertexBuffer, 0));


	int m = mSideFacetsNum;
	float angle = 2 * M_PI / m;
	float diam = 2 * mRadius;
	float portion = (diam / (mSideFacetsNum + 1));


	// Now lock it to obtain a pointer to its internal data, and write the
	// cube's vertex data.

	VertexPos* v = 0;
	HR(m_VertexBuffer->Lock(0, 0, (void**)&v, 0));

	int mNum = 0;
	v[mNum++] = VertexPos(0,0,-mRadius);
	for (int i = 0; i < mSideFacetsNum; i++)
	{
		float currentAngle = 0;
		float z = portion*(i+1) -mRadius;
		float tempRadius = sqrt((mRadius*mRadius) - (z*z));
		for (int j = 0; j < mSideFacetsNum; j++)
		{
			float x = tempRadius*cos(currentAngle);
			float y = tempRadius*sin(currentAngle);
			v[mNum++] = VertexPos(x, y, z);
			currentAngle += angle;
		}
	}
	v[mNum] = VertexPos(0, 0, mRadius);

	HR(m_VertexBuffer->Unlock());
}

//-----------------------------------------------------------------------------
void Sphere::buildDemoCubeIndexBuffer(IDirect3DDevice9* gd3dDevice)
{
	// Obtain a pointer to a new index buffer.
	HR(gd3dDevice->CreateIndexBuffer(m_IndexNum * 3 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_IndexBuffer, 0));
	// Now lock it to obtain a pointer to its internal data, and write the
	// cube's index data.

	WORD* k = 0;

	HR(m_IndexBuffer->Lock(0, 0, (void**)&k, 0));

	int num = 0;

	//construct the base;
	int i;
	for (i = 1; i < mSideFacetsNum; i++)
	{
		k[num++] = 0;
		k[num++] = i;
		k[num++] = i + 1;
	}
	k[num++] = 0;
	k[num++] = mSideFacetsNum;
	k[num++] = 1;

	//construct the Cone;

	for (int j = 0; j < mSideFacetsNum - 1; j++)
	{
		for (i = 0; i < mSideFacetsNum; i++)
		{
			int base = i + 1 + (j* mSideFacetsNum);
			if (i == mSideFacetsNum - 1)
			{
				k[num++] = base;
				k[num++] = base + mSideFacetsNum;
				k[num++] = base - mSideFacetsNum + 1;

				k[num++] = base - mSideFacetsNum + 1;
				k[num++] = base + mSideFacetsNum;
				k[num++] = base + 1;
			}
			else
			{
				k[num++] = base;
				k[num++] = base + mSideFacetsNum;
				k[num++] = base + 1;

				k[num++] = base + 1;
				k[num++] = base + mSideFacetsNum;
				k[num++] = base + 1 + mSideFacetsNum;
			}
		}
	}
	
	//construct the cap
	int cap = m_VertexNum - 1;
	for (i = 1; i < mSideFacetsNum; i++)
	{
		k[num++] = cap;
		k[num++] = cap - i;
		k[num++] = cap - i - 1;
	}
	k[num++] = cap;
	k[num++] = cap - i;
	k[num++] = cap - 1;
	

	HR(m_IndexBuffer->Unlock());
}
//=============================================================================
