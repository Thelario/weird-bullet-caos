#include "BulletGame.h"

#include "../Engine/LoggerManager.h"
#include "../Engine/SoundsManager.h"
#include "../Engine/InputManager.h"
#include "../Engine/FontsManager.h"
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
		
		FontsManager::Instance()->AddFont("arial", "arial.ttf", 100);

		SoundsManager::Instance()->AddSound("sfx_shoot.wav", "shoot");
		SoundsManager::Instance()->AddSound("sfx_asteroid_hit.wav", "asteroid-hit");
		SoundsManager::Instance()->AddSound("sfx_player_hit.wav", "player-hit");

		game_has_started = false;
		current_score = 0;

		start_game_text = new Text(glm::vec2(Engine::Instance()->GetWindowWidth() / 2, Engine::Instance()->GetWindowHeight() / 2),
			glm::vec2(1), "Press Space to start...", "arial", true);

		score_text = new Text(glm::vec2(Engine::Instance()->GetWindowWidth() / 2, Engine::Instance()->GetWindowHeight() / 2),
			glm::vec2(5), std::to_string(current_score), "arial", false, { 30, 61, 81, 255 });
	}

	void BulletGame::Update()
	{
		// Update all the gameobjects this game currently has
		Game::Update();

		// Stop game
		if (InputManager::GetKeyDown(KeyCode::ESCAPE)) {
			StopGame();
		}

		// Set debug mode
		if (InputManager::GetKeyUp(KeyCode::Q)) {
			Engine::Instance()->SetDebugging(Engine::Instance()->Debugging() ? false : true);
		}

		// Start game
		if (game_has_started == false && InputManager::GetKeyUp(KeyCode::SPACE))
		{
			game_has_started = true;
			start_game_text->enabled = false;
			score_text->enabled = true;

			Player* player = new Player(glm::vec2(Engine::Instance()->GetWindowWidth() / 2,
				Engine::Instance()->GetWindowHeight() / 2), glm::vec2(1), 0, "ship", 128, 128, false, -1, true, 0,
				{ 223, 208, 184, 255 }, true, true, true, glm::vec2(70, 70), glm::vec2(0), ColliderTag::PLAYER, this);

			CreateObject(player);

			CreateObject(new Spawner(glm::vec2(Engine::Instance()->GetWindowWidth() / 2, Engine::Instance()->GetWindowHeight() / 2),
				glm::vec2(1), 0, "", 0, 0, false, -1, true, 0, { 255, 255, 255, 255 }, true, false, player));

			player->CreateHearts();
		}
	}

	void BulletGame::Render()
	{
		// Render before all gameobjects

		if (score_text->enabled) {
			score_text->SetText(std::to_string(current_score));
			score_text->Render();
		}

		// Reder all gameobjects

		Game::Render();

		// Render after all gameobjects

		if (start_game_text->enabled) {
			start_game_text->Render();
		}
	}

	void BulletGame::StopGame()
	{
		game_has_started = false;
		start_game_text->enabled = true;
		score_text->enabled = false;
		current_score = 0;
		DestroyObjects();
	}

	void BulletGame::ScoreUp()
	{
		current_score++;
	}
}