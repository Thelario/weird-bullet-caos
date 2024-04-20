#pragma once

#include "LoggerManager.h"
#include "Game.h"

namespace Satellite
{
	class Engine
	{
		private:
			Game* _game;

		public:
			static Engine* Instance();

			void Start(Game* game);
			void Run();
			void Destroy();
	};
}