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
		Engine::Instance()->SetBackgroundColor({ 21, 52, 72, 255 });
		
		SoundsManager::Instance()->AddSound("sfx_shoot.wav", "shoot");
		SoundsManager::Instance()->AddSound("sfx_asteroid_hit.wav", "asteroid-hit");
		SoundsManager::Instance()->AddSound("sfx_player_hit.wav", "player-hit");
	}

	void BulletGame::Update()
	{
		// Update all the gameobjects this game currently has
		Game::Update();

		// Stop game
		if (InputManager::GetKeyDown(KeyCode::ESCAPE)) {
			game_has_started = false;
			DestroyObjects();
		}

		// Set debug mode
		if (InputManager::GetKeyUp(KeyCode::Q)) {
			Engine::Instance()->SetDebugging(Engine::Instance()->Debugging() ? false : true);
		}

		// Start game
		if (game_has_started == false && InputManager::GetKeyUp(KeyCode::SPACE))
		{
			game_has_started = true;

			GameObject* player = CreateObject(new Player(glm::vec2(Engine::Instance()->GetWindowWidth() / 2,
				Engine::Instance()->GetWindowHeight() / 2), glm::vec2(1), 0, "ship", 128, 128, false, -1, true, 0,
				{ 223, 208, 184, 255 }, true, true, true, glm::vec2(70, 70), glm::vec2(0), ColliderTag::PLAYER));

			CreateObject(new Spawner(glm::vec2(Engine::Instance()->GetWindowWidth() / 2, Engine::Instance()->GetWindowHeight() / 2),
				glm::vec2(1), 0, "", 0, 0, false, -1, true, 0, { 255, 255, 255, 255 }, true, false, player));
		}
	}
}