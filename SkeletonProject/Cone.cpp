//=============================================================================
//                              BaseObject3D
//
// Writen by Jesse McKinley, 2015
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Cone class to generate a 3d cone object.
//=============================================================================
#define _USE_MATH_DEFINES
#include "Cone.h"
#include "3DClasses\Vertex.h"
#include "GfxStats.h"
#include <math.h>
//=============================================================================
Cone::Cone(int height, float radius, int sideFacetsNum) : BaseObject3D((sideFacetsNum)*(height) + 2, (2 * sideFacetsNum)*(height))
{
	mHeight = height;
	mRadius = radius;
	mSideFacetsNum = sideFacetsNum;
}

//-----------------------------------------------------------------------------
Cone::~Cone(void)
{
	ReleaseCOM(m_VertexBuffer);
	ReleaseCOM(m_IndexBuffer);
}

//-----------------------------------------------------------------------------
void Cone::Create(IDirect3DDevice9* gd3dDevice)
{
	buildDemoCubeVertexBuffer(gd3dDevice);
	buildDemoCubeIndexBuffer(gd3dDevice);
}

//-----------------------------------------------------------------------------
void Cone::Render(IDirect3DDevice9* gd3dDevice,
	D3DXMATRIX& view, D3DXMATRIX& projection)
{
	// Update the statistics singlton class
	GfxStats::GetInstance()->addVertices(m_VertexNum);
	GfxStats::GetInstance()->addTriangles(m_IndexNum);

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
void Cone::buildDemoCubeVertexBuffer(IDirect3DDevice9* gd3dDevice)
{
	// Obtain a pointer to a new vertex buffer.
	HR(gd3dDevice->CreateVertexBuffer(m_VertexNum * sizeof(VertexPos), D3DUSAGE_WRITEONLY,
		0, D3DPOOL_MANAGED, &m_VertexBuffer, 0));


	int m = mSideFacetsNum;
	float angle = 2 * M_PI / m;


	// Now lock it to obtain a pointer to its internal data, and write the
	// cube's vertex data.

	VertexPos* v = 0;
	HR(m_VertexBuffer->Lock(0, 0, (void**)&v, 0));

	int mNum = 0;
	v[mNum++] = VertexPos(0, 0, -(mHeight / 2));
	for (int i = 0; i < mHeight; i++)
	{
		float currentAngle = 0;
		float height = i - (mHeight / 2);
		for (int j = 0; j < mSideFacetsNum; j++)
		{
			float x = mRadius*cos(currentAngle) * ((mHeight-i)/mHeight);
			float y = mRadius*sin(currentAngle) * ((mHeight - i) / mHeight);
			v[mNum++] = VertexPos(x, y, height);
			currentAngle += angle;
		}
	}
	v[mNum] = VertexPos(0, 0, mHeight / 2);

	HR(m_VertexBuffer->Unlock());
}

//-----------------------------------------------------------------------------
void Cone::buildDemoCubeIndexBuffer(IDirect3DDevice9* gd3dDevice)
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

	for (int j = 0; j < mHeight-1; j++)
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
