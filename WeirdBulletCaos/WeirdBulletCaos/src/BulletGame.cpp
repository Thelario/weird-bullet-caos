#include "BulletGame.h"

#include "../../SatelliteEngine2D/Engine.h"

void BulletGame::Start()
{
	Engine::instance()->GetLogger()->Log("Correctly starting game.");
}

void BulletGame::Update()
{
	Engine::instance()->GetLogger()->Log("Correctly updating game.");
}

void BulletGame::Destroy()
{
	Engine::instance()->GetLogger()->Log("Correctly destroying game.");
}
