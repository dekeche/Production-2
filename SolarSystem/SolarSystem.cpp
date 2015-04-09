#include "SolarSystem.h"
SolarSystem::SolarSystem()
{

};
SolarSystem::~SolarSystem()
{
	delete mpBase;
};

void SolarSystem::create()
{
	//Generate initial planet, the sun.
};
void SolarSystem::update(float dt)
{
	mpBase->update(dt);
};
void SolarSystem::render()
{
	mpBase->render();
};

void SolarSystem::GoDownLevel()
{
	std::vector <Planetoid*>* SubPlanetoids = mpCurrent->GetSubList();
	if (SubPlanetoids->size() > 0)
	{
		mLevel.push_back(0);
		mpCurrent = (*SubPlanetoids)[0];
	}
};
void SolarSystem::GoUpLevel()
{
	if (mLevel.size() > 0)
	{
		Planetoid* pTemp = mpBase;
		for (int i = 0; i < mLevel.size() - 1; i++)
		{
			pTemp = (*pTemp->GetSubList())[mLevel[i]];
		}
		mpCurrent = pTemp;
		mLevel.pop_back();
	}
};
void SolarSystem::NextObject()
{
	if (mLevel.size() > 0)
	{
		Planetoid* pTemp = mpBase;
		int i;
		for (i = 0; i < mLevel.size() - 1; i++)
		{
			pTemp = (*pTemp->GetSubList())[mLevel[i]];
		}
		std::vector <Planetoid*>* SubPlanetoids = pTemp->GetSubList();
		int target = mLevel[i] + 1;
		if (target >= SubPlanetoids->size())
			target = 0;
		mpCurrent = (*SubPlanetoids)[i];
		mLevel[i] = target;
	}
};
void SolarSystem::PrevObject()
{
	if (mLevel.size() > 0)
	{
		Planetoid* pTemp = mpBase;
		int i;
		for (i = 0; i < mLevel.size() - 1; i++)
		{
			pTemp = (*pTemp->GetSubList())[mLevel[i]];
		}
		std::vector <Planetoid*>* SubPlanetoids = pTemp->GetSubList();
		int target = mLevel[i] - 1;
		if (target < 0)
			target = SubPlanetoids->size() - 1;
		mpCurrent = (*SubPlanetoids)[i];
		mLevel[i] = target;
	}
};