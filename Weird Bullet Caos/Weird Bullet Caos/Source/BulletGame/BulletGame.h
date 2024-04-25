#pragma once

#include "../Engine/Game.h"
#include "../Engine/GameObject.h"

using namespace Satellite;

namespace BulletGame
{
	class BulletGame : public Game
	{
	public:
		void Start() override;
		void Update() override;
	};
}