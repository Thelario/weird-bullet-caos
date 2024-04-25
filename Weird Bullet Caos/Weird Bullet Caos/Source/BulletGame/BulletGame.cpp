#include "BulletGame.h"

#include "../Engine/InputManager.h"
#include "../Engine/Engine.h"
#include "Player.h"

namespace BulletGame
{
	void BulletGame::Start()
	{
		Engine::Instance()->SetRenderLogicalSize(glm::vec2(960, 540));
		Engine::Instance()->SetWindowTitle("Weird Bullet Caos");
		Engine::Instance()->SetBackgroundColor({ 0, 0, 0, 255 });

		Engine::Instance()->CreateObject(new Player(glm::vec2(Engine::Instance()->GetWindowWidth() / 2, Engine::Instance()->GetWindowHeight() / 2),
			glm::vec2(.5), 0, "ship", 128, 128, false, -1, true, 0, { 255, 255, 255, 255 }));
	}

	void BulletGame::Update()
	{
		Game::Update();

		if (InputManager::GetKey(KeyCode::ESCAPE)) {
			Engine::Instance()->SetIsRunning(false);
		}
	}
}