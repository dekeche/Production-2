//=============================================================================
//                          SkeletonClass.h
//
// Adopted from CubeDemo.cpp by Frank Luna (C) 2005 All Rights Reserved.
//
// Edited and changed by Adi Bar-Lev, 2013
// EGP-300-101 - Computer Graphics II, Spring 2013.
//
// This project creates a skeleton workspace and base classes for the student to be 
// able to start working with sample classes and develop evolve it according to the 
// given exercises
//
// Controls: Use mouse to orbit and zoom; use the 'W' and 'S' keys to 
//           alter the height of the camera.
//=============================================================================
#ifndef _SKELETON_CLASS_H
#define _SKELETON_CLASS_H
//=============================================================================
#pragma once
//=============================================================================
#include "d3dApp.h"
#include "BaseMaterial.h"

#include <vector>
//=============================================================================
class BaseObject3D;
//=============================================================================
class SkeletonClass : public D3DApp
{
public:
	SkeletonClass(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP);
	~SkeletonClass();

	bool checkDeviceCaps();
	void onLostDevice();
	void onResetDevice();
	void updateScene(float dt);
	void drawScene();

	// Helper methods
	void buildViewMtx();
	void buildProjMtx();

	//	method to change objects to view
	void ChangeObject();

private:
	BaseMaterial *mConeMaterial;

	float mCameraRotationY;
	float mCameraRotationX;
	float mCameraRadius;
	float mCameraHeight;

	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	D3DXMATRIX mWorld;


	//	World Light variables
	D3DXVECTOR3 m_Light_vector_W;		//	Light Vector in the World
	D3DXCOLOR m_Light_ambient;
	D3DXCOLOR m_Light_diffuse;
	D3DXCOLOR m_Light_specular;


    std::vector<BaseObject3D*>      m_Objects;

	//	Variables added to "cycle" through different objects
	int m_currentobject_index;
	bool m_key_O_down = false;
	bool m_key_W_down = false;
	bool m_key_T_down = false;
	bool m_key_S_down = false;
	bool m_key_D_down = false;
	bool m_key_E_down = false;



	//	Variables added to "cycle" through different shaders
					//	Shader Indices
					/*	0 - None(?)
						1 - Phong
						2 - Spotlight
					*/
	int m_current_shader_index = 0;


	//	Variables added to toggle various features
		//	Solid & WireFrame
	bool i_Solid_frame = true;
		//	With/Without Texture
	bool i_texture_on = false;
		//	Specular on/off
	bool i_spec_on = true;
		//	Diffuse on/off
	bool i_diff_on = true;

	//	Shaders
	ID3DXEffect* m_current_effect;
	ID3DXEffect* m_phong_FX;
	const std::string PHONG_TECHNIQUE = "Technique";
	ID3DXEffect* m_spot_FX;
		//	HANDLES
	D3DXHANDLE mh_Technique;				//	technique to use for the Shader
					//	For BEST simplicity, have the technique be called "Technique" unless stated otherwise
	D3DXHANDLE mh_WVP;						//	world view projection matrix
	D3DXHANDLE mh_WorldInverseTranspose;	//	Inverse of the World matrix
	D3DXHANDLE mh_LightVecW;				//	World vector of Light
//	D3DXHANDLE mh_diffuseMtrl;				//	Diffuse material of the mesh(object)
	D3DXHANDLE mh_diffuseLight;				//	Diffuse of the Light
//	D3DXHANDLE mh_ambientMtrl;				//	Ambient material to use
	D3DXHANDLE mh_ambientLight;				//	Ambient of the Lgith
//	D3DXHANDLE mh_specularMtrl;				//	Specular material/component
	D3DXHANDLE mh_specularLight;			//	Specular of the Light
	D3DXHANDLE mh_specularPower;			//	"Shininess" of specular component
	D3DXHANDLE mh_eyePos;					//	Position of the Eye(camera) in the World.
	D3DXHANDLE mh_World;					//	Matrix of the WORLD.

	D3DXHANDLE mh_LightPosW;				//	Position of a light in the WORLD
	D3DXHANDLE mh_LightDirectW;				//	Direction of a light in the WORLD
	D3DXHANDLE mh_attenuation;				//	attenuation of the LIGHT

	D3DXHANDLE mh_spotPower;				//	power of a SPOTLIGHT
		
	
		//	Function for SHADER
	void buildPhongFX();
	void obtainPhongHandles();
	void buildSpotFX();
	void obtainSpotHandles();


};
//=============================================================================
#endif // _SKELETON_CLASS_H_