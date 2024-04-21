#include "BulletGame.h"

#include "../Engine/InputManager.h"
#include "../Engine/Engine.h"
#include "Player.h"

namespace BulletGame
{
	void BulletGame::Start()
	{
		Engine::Instance()->SetRenderLogicalSize(glm::vec2(480, 270));
		Engine::Instance()->SetWindowTitle("Weird Bullet Caos");
		Engine::Instance()->SetBackgroundColor({ 49, 54, 63, 255 });

		circle = new Player(glm::vec2(Engine::Instance()->GetWindowWidth() / 3, Engine::Instance()->GetWindowHeight() / 2),
			glm::vec2(.6), 0, "basic-shapes", 32, 32, false, 0, true, 0, { 238, 238, 238, 255 });

		foreground = new GameObject(glm::vec2(Engine::Instance()->GetWindowWidth() / 2, Engine::Instance()->GetWindowHeight() / 2),
			glm::vec2(1), 0, "foreground", 480, 270, false, -1, true, 0, { 34, 40, 49, 255 });

		circle->Start();
		foreground->Start();
	}

	void BulletGame::Update()
	{
		if (InputManager::GetKey(KeyCode::ESCAPE)) {
			Engine::Instance()->SetIsRunning(false);
		}

		circle->Update();
		foreground->Update();
	}

	void BulletGame::Render()
	{
		circle->Render();
		foreground->Render();
	}

	void BulletGame::Destroy()
	{
		delete foreground;
		delete circle;
	}
}