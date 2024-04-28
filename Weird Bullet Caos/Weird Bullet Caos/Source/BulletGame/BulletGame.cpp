#include "BulletGame.h"

#include "../Engine/LoggerManager.h"
#include "../Engine/SoundsManager.h"
#include "../Engine/InputManager.h"
#include "../Engine/Engine.h"

#include "Player.h"

#include "Spawner.h"

namespace BulletGame
{
	void BulletGame::Start()
	{
		// Game configuration

		Engine::Instance()->SetDebugging(false);
		Engine::Instance()->SetRenderLogicalSize(glm::vec2(1920, 1080));
		Engine::Instance()->SetWindowTitle("Weird Bullet Caos");
		Engine::Instance()->SetBackgroundColor({ 0, 0, 0, 255 });
		
		SoundsManager::Instance()->AddSound("sfx_shoot.wav", "shoot");
		SoundsManager::Instance()->AddSound("sfx_asteroid_hit.wav", "asteroid-hit");
		SoundsManager::Instance()->AddSound("sfx_player_hit.wav", "player-hit");
	}

	void BulletGame::Update()
	{
		Game::Update();

		// Stop game
		if (InputManager::GetKeyDown(KeyCode::ESCAPE)) {
			Engine::Instance()->DestroyObjects();
		}

		// Set debug mode
		if (InputManager::GetKeyUp(KeyCode::Q)) {
			Engine::Instance()->SetDebugging(Engine::Instance()->Debugging() ? false : true);
		}

		// Start game
		if (InputManager::GetKeyUp(KeyCode::SPACE))
		{
			GameObject* player = Engine::Instance()->CreateObject(new Player(glm::vec2(Engine::Instance()->GetWindowWidth() / 2,
				Engine::Instance()->GetWindowHeight() / 2), glm::vec2(1), 0, "ship", 128, 128, false, -1, true, 0,
				{ 255, 255, 255, 255 }, true, true, true, glm::vec2(70, 70), glm::vec2(0), ColliderTag::PLAYER));

			Engine::Instance()->CreateObject(new Spawner(glm::vec2(Engine::Instance()->GetWindowWidth() / 2, Engine::Instance()->GetWindowHeight() / 2),
				glm::vec2(1), 0, "", 0, 0, false, -1, true, 0, { 255, 255, 255, 255 }, true, false, player));
		}
	}
}