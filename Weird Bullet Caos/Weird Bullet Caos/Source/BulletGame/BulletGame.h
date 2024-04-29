#pragma once

#include "../Engine/Game.h"
#include "../Engine/GameObject.h"
#include "../Engine/Text.h"

using namespace Satellite;

namespace BulletGame
{
	class BulletGame : public Game
	{
	private:
		bool game_has_started;

		int current_score;

		Text* start_game_text;
		Text* score_text;

	public:
		void StopGame();

		void Start() override;
		void Update() override;
		void Render() override;

		void ScoreUp();
	};
}