#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include "cocos2d.h"
#include "Graph.h"
#include "Pathfinder.h"
#include "GameWorld.h"

using namespace cocos2d;

class GlobalVar
{
public:	
	GlobalVar();
	virtual ~GlobalVar();
	static GlobalVar& instance();

	Pathfinder* GetPathfinder();
	void SetPathfinder(Pathfinder* pPathFinder);

	GameWorld* GetGameWorld();
	void SetGameWorld(GameWorld* pGameWorld);

	CCPoint HammerPosToCocosPos(Vector2D vec);
	Vector2D CocosPosToHammerPos(CCPoint pos);

public:
	Pathfinder*	m_pPathFinder;
	GameWorld*	m_pGameWorld;
};

#endif /*GLOBAL_VAR*/