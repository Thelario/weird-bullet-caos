#pragma once

#include "../../SatelliteEngine2D/Engine.h"

using namespace Satellite;

class BulletGame : public Game
{
	public:
		void Start() override;
		void Update() override;
		void Destroy() override;
};