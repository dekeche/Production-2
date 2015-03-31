//=============================================================================
//              Adopted from Franc Luna's CubeDemo sample project.
//
// Please use this file to add classes / inherit and create various vertex classes
//=============================================================================
#ifndef VERTEX_H
#define VERTEX_H
//=============================================================================
#include <d3dx9.h>
//=============================================================================
// Call in constructor and destructor, respectively, of derived application class.
void InitAllVertexDeclarations();
void DestroyAllVertexDeclarations();


//===============================================================
struct VertexPos
{
	VertexPos() :pos(0.0f, 0.0f, 0.0f){}
	VertexPos(float x, float y, float z) :pos(x, y, z){}
	VertexPos(const D3DXVECTOR3& v) :pos(v){}

	D3DXVECTOR3 pos;
	static IDirect3DVertexDeclaration9* Decl;
};

//===============================================================
struct VertexCol
{
	VertexCol() :pos(0.0f, 0.0f, 0.0f), col(0x00000000){}
	VertexCol(float x, float y, float z, D3DCOLOR c) :pos(x, y, z), col(c){}
	VertexCol(const D3DXVECTOR3& v, D3DCOLOR c) :pos(v), col(c){}

	D3DXVECTOR3 pos;
	D3DCOLOR    col;
	static IDirect3DVertexDeclaration9* Decl;
};

//===============================================================
struct VertexPN
{
	VertexPN()
	:pos(0.0f, 0.0f, 0.0f),
	normal(0.0f, 0.0f, 0.0f){}
	VertexPN(float x, float y, float z,
		float nx, float ny, float nz) :pos(x, y, z), normal(nx, ny, nz){}
	VertexPN(const D3DXVECTOR3& v, const D3DXVECTOR3& n)
		:pos(v), normal(n){}

	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	static IDirect3DVertexDeclaration9* Decl;
};

//===============================================================
struct VertexPNT
{
	VertexPNT()
	:pos(0.0f, 0.0f, 0.0f),
	normal(0.0f, 0.0f, 0.0f),
	tex0(0.0f, 0.0f){}
	VertexPNT(float x, float y, float z,
		float nx, float ny, float nz,
		float v, float u) :pos(x, y, z), normal(nx, ny, nz), tex0(v, u){}
	VertexPNT(const D3DXVECTOR3& v, const D3DXVECTOR3& n, const D3DXVECTOR2& vu)
		:pos(v), normal(n), tex0(vu){}

	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 tex0;
	static IDirect3DVertexDeclaration9* Decl;
};
//=============================================================================
struct VertexBN
{
	VertexBN()
	:normal(0, 0, 0),
	tangent(0, 0, 0),
	binormal(0, 0, 0),
	tex0(0, 0){}
	VertexBN(float nx, float ny, float nz,
		float tx, float ty, float tz,
		float bnx, float bny, float bnz,
		float v, float u) :normal(nx, ny, nz), tangent(tx, ty, tz), binormal(bnx, bny, bnz), tex0(v, u){}
		
	D3DXVECTOR3 normal;
	D3DXVECTOR3 tangent;
	D3DXVECTOR3 binormal;
	D3DXVECTOR2 tex0;
};
#endif // VERTEX_H