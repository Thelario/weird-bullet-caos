#pragma once

namespace Satellite
{
	class Game
	{
		public:
			virtual void Start();
			virtual void Update();
			virtual void Destroy();
	};
}