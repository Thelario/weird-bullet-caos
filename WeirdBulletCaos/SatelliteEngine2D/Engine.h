#pragma once

#include "Game.h"

namespace Satellite
{
	class Engine
	{
		private:
			Game* _game;

		public:
			void Start(Game* game);
			void Run();
			void Destroy();
	};
}