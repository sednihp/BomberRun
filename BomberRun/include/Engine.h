#ifndef ENGINE_H
#define ENGINE_H

#include "MediaCache.h"
#include "StateMachine.h"
#include <memory>
#include "Player.h"

class Engine
{
	private: 
		bool running;
		double deltaTime;
		MediaCache mediaCache;
		Player player;
		std::unique_ptr<StateMachine> stateMachine;

		void handleEvents();
		void update();
		void render();

	public:
		Engine();
		~Engine();

		void run();
		const bool isRunning() const { return running; }
		void stopRunning() { running = false; }

		void changeState(std::shared_ptr<State> newState);
};

#endif