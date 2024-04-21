#pragma once

#include "../Engine/Game.h"
#include "../Engine/GameObject.h"

using namespace Satellite;

namespace BulletGame
{
	class BulletGame : public Game
	{
	private:
		GameObject* foreground;
		GameObject* circle;

	public:
		void Start() override;
		void Update() override;
		void Render() override;
		void Destroy() override;
	};
}