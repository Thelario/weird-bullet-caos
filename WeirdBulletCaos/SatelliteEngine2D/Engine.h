#pragma once

#include "LoggerManager.h"
#include "Game.h"

namespace Satellite
{
	class Engine
	{
		private:
			LoggerManager* _logger;
			Game* _game;

		public:
			static Engine* instance();

			void Start(Game* game);
			void Run();
			void Destroy();

			LoggerManager* GetLogger() { return _logger; }
	};
}