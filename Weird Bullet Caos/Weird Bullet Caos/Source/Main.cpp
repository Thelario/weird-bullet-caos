#include "Engine/Engine.h"
#include "BulletGame/BulletGame.h"

using namespace Satellite;

int main(int argc, char* args[])
{
	Engine* engine = Engine::Instance();

	Game* game = new BulletGame();

	engine->Start(game);
	engine->Run();
	engine->Destroy();

	delete game;

	return 0;
}