#pragma once

#include "../Engine/Engine.h"

using namespace Satellite;

class BulletGame : public Game
{
	public:
		void Start() override;
		void Update() override;
		void Render(SDL_Renderer* renderer) override;
		void Destroy() override;
};