#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#include "State.h"
#include "Player.h"
#include "Plane.h"
#include <vector>
#include "Bomb.h"
#include "CollisionEngine.h"
#include "Building.h"
#include "ParticleEngine.h"
#include "Cloud.h"

class Level : public State
{
    private:      
		const int groundLevel;
		SDL_Rect groundLine, skybox;
		SDL_Color groundColor, skyColor;
		TTF_Font* font;
		std::shared_ptr<GameTexture> pausedMsg;
		std::shared_ptr<GameTexture> lvlScoreMsg;
		std::shared_ptr<GameTexture> muteIcon;
		std::vector<std::shared_ptr<Building>> buildings;
		std::vector<std::shared_ptr<Cloud>> clouds;
		std::vector<std::shared_ptr<ParticleEngine>> pEngines;
		std::unique_ptr<Plane> plane;
		std::unique_ptr<Bomb> bomb;
		bool paused, planeParked;
		unsigned timeParked;
		int levelScore;

		Level& operator=(const Level&);
		Level(const Level&);

    public:
        Level(MediaCache& mc, Player& p);
        ~Level();

		void enter(Engine* engine);
		void handleEvents(SDL_Event& e, Engine* engine);
		void update(const double dTime, Engine* engine);
		void render();
		void exit(Engine* engine);

		void generateBackground();
		void generateBuildings();
		void generateClouds();
		void generateBomb();

		void udpateClouds(const double dTime);
		void updatePlane(const double dTime);
		void updateBomb(const double dTime);
		void updateParticleEngines();
		void parkPlane();
};

#endif // GAME_H_INCLUDED
