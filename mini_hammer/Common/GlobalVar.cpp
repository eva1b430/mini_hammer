#include "GlobalVar.h"

GlobalVar::GlobalVar()
	: m_pPathFinder(NULL)
{

}

GlobalVar::~GlobalVar()
{

}

GlobalVar& GlobalVar::instance()
{
	static GlobalVar inst;
	return inst;
}

Pathfinder* GlobalVar::GetPathfinder()
{
	return m_pPathFinder;
}

void GlobalVar::SetPathfinder(Pathfinder* pPathFinder)
{
	m_pPathFinder = pPathFinder;
}

GameWorld* GlobalVar::GetGameWorld()
{
	return m_pGameWorld;
}

void GlobalVar::SetGameWorld(GameWorld* pGameWorld)
{
	m_pGameWorld = pGameWorld;
}

CCPoint GlobalVar::HammerPosToCocosPos(Vector2D vec)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	return ccp(vec.x, winSize.height - vec.y);
}

Vector2D GlobalVar::CocosPosToHammerPos(CCPoint pos)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	return Vector2D(pos.x, winSize.height - pos.y);
}
