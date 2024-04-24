#include "BulletGame.h"

#include "../Engine/LoggerManager.h"
#include "../Engine/InputManager.h"
#include "../Engine/Engine.h"
#include "Player.h"

namespace BulletGame
{
	void BulletGame::Start()
	{
		Engine::Instance()->SetRenderLogicalSize(glm::vec2(480, 270));
		Engine::Instance()->SetWindowTitle("Weird Bullet Caos");
		Engine::Instance()->SetBackgroundColor({ 0, 0, 0, 255 });

		circle = new Player(glm::vec2(Engine::Instance()->GetWindowWidth() / 3, Engine::Instance()->GetWindowHeight() / 2),
			glm::vec2(1), 0, "player", 32, 32, false, -1, true, 0, { 255, 255, 255, 255 });

		foreground = new GameObject(glm::vec2(Engine::Instance()->GetWindowWidth() / 2, Engine::Instance()->GetWindowHeight() / 2),
			glm::vec2(1), 0, "foreground", 480, 270, false, -1, true, 0, { 255, 255, 255, 255 });

		Engine::Instance()->CreateObject(circle);
		Engine::Instance()->CreateObject(foreground);
	}

	void BulletGame::Update()
	{
		if (InputManager::GetKey(KeyCode::ESCAPE)) {
			Engine::Instance()->SetIsRunning(false);
		}

		Game::Update();
	}

	void BulletGame::Destroy()
	{
		delete foreground;
		delete circle;
	}
}