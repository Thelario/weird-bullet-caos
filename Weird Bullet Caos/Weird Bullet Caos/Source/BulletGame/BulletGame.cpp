#include "BulletGame.h"

#include "../Engine/LoggerManager.h"

void BulletGame::Start()
{
	LoggerManager::Log("Correctly starting game.");
}

void BulletGame::Update()
{
	LoggerManager::Log("Correctly updating game.");
}

void BulletGame::Render(SDL_Renderer* renderer)
{
	LoggerManager::Log("Correctly rendering game.");
}

void BulletGame::Destroy()
{
	LoggerManager::Log("Correctly destroying game.");
}
