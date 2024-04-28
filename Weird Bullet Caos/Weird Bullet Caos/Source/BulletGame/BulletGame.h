#pragma once

#include "../Engine/Game.h"
#include "../Engine/GameObject.h"

using namespace Satellite;

namespace BulletGame
{
	class BulletGame : public Game
	{
	private:
		bool game_has_started = false;

	public:
		void Start() override;
		void Update() override;
	};
}