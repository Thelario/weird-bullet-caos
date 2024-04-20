#include "../../SatelliteEngine2D/Engine.h"

#include "BulletGame.h"

using namespace Satellite;

int main(int argc, char* args[])
{
	Engine* engine = Engine::Instance();

	Game* my_game = new BulletGame();

	engine->Start(my_game);
	engine->Run();
	engine->Destroy();

	delete my_game;

	return 0;
}