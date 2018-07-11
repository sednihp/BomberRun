#include "Level.h"
#include <algorithm>

Level::Level(MediaCache& mc, Player& p) : State(mc, p),
											groundLevel(mediaCache.scrHeight() - 40),
											plane(std::make_unique<Plane>()),
											bomb(nullptr),
											paused(false), planeParked(false),
											timeParked(0),
											font(mediaCache.getFont(30)),
											lvlScoreMsg(nullptr),
											levelScore(0)
{
	plane->setTexture(mediaCache.getImage(plane->getImage()));
	generateBackground();
	generateBuildings();
	generateClouds();

	pausedMsg = mediaCache.getText("Paused", font, { 255,0,0 });
}

Level::~Level()
{
}

void Level::enter(Engine* )
{
	if (!mediaCache.isPlayingMusic())
	{
		mediaCache.playMusic(mediaCache.getMusic("files/sounds/plane.ogg"), 1);
	}
}

void Level::handleEvents(SDL_Event& e, Engine* )
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_SPACE: generateBomb();
							break;
			
			case SDLK_p:	paused = !paused;
							mediaCache.togglePause(-1);
							break;
			
			default:		break;
		}
	}
}

void Level::update(const double dTime, Engine* )
{
	if (!paused)
	{
		updatePlane(dTime);

		udpateClouds(dTime);

		updateBomb(dTime);

		updateParticleEngines();

		if (buildings.size() == 0 && !plane->isParking())
		{
			parkPlane();
		}
		else if (!plane->isAlive())
		{
			player.setScore(levelScore);
			//stateMan.setNextState(State::GameOver);
		}
		else if (planeParked && SDL_GetTicks() - timeParked >= 1000)
		{
			player.setScore(levelScore);
			//stateMan.incrementLevelNumber();
			//stateMan.setNextState(State::LvlCmp);
		}
	}

	if (mediaCache.isMuted()) 
	{
		muteIcon = mediaCache.getImage("files/images/mutevolume.bmp");
	}
	else 
	{
		muteIcon = mediaCache.getImage("files/images/volume.bmp");
	}
}

void Level::render()
{
	mediaCache.drawRectangle(skybox, skyColor);
	mediaCache.drawRectangle(groundLine, groundColor);

	for (const auto& c : clouds)
	{
		mediaCache.renderTexture(c->getTexture(), static_cast<int>(c->getPosition().x), static_cast<int>(c->getPosition().y));
	}

	for (const auto& b : buildings)
	{
		mediaCache.drawRectangle(b->getBox(), b->getColor());

		for (int i = 0; i < b->getNumberOfStoreys(); ++i)
		{
			Point2D p(b->getPosition().x, b->getPosition().y + i * b->getStoreyHeight());
			mediaCache.renderTexture(b->getTexture(), static_cast<int>(p.x), static_cast<int>(p.y));
		}
	}

	if (bomb != nullptr)
	{
		mediaCache.renderTexture(bomb->getTexture(), static_cast<int>(bomb->getPosition().x), static_cast<int>(bomb->getPosition().y));
	}

	for (const auto& pEngine : pEngines)
	{
		mediaCache.drawSpriteCntr(*pEngine);
	}

	mediaCache.renderTexture(plane->getTexture(), static_cast<int>(plane->getPosition().x), static_cast<int>(plane->getPosition().y));

	if (paused)
	{
		mediaCache.renderTexture(pausedMsg, mediaCache.centreX(pausedMsg->getBox().w), mediaCache.centreY(pausedMsg->getBox().h));
	}

	lvlScoreMsg = mediaCache.getText(std::to_string(levelScore), font, { 255,0,0 });
	mediaCache.renderTexture(lvlScoreMsg, mediaCache.centreX(lvlScoreMsg->getBox().w), mediaCache.scrHeight() - lvlScoreMsg->getBox().h);

	mediaCache.renderTexture(muteIcon, 0, mediaCache.scrHeight() - muteIcon->getBox().h);
}

void Level::exit(Engine* )
{
	mediaCache.stopMusic();
}

//====================
//====================

void Level::generateBackground()
{
	groundLine.x = 0;
	groundLine.y = static_cast<Sint16>(groundLevel);
	groundLine.w = static_cast<Uint16>(mediaCache.scrWidth());
	groundLine.h = 1;

	groundColor.r = 120;
	groundColor.g = 75;
	groundColor.b = 50;

	skybox.x = 0;
	skybox.y = 0;
	skybox.w = static_cast<Uint16>(mediaCache.scrWidth());
	skybox.h = static_cast<Uint16>(groundLevel);

	skyColor.r = 187;
	skyColor.g = 226;
	skyColor.b = 255;
}

//level 1 has 15 buildings at a max height of 15 storeys
//levels 2-4 increase the number of buildings & storeys by 2 each time
//levels 5 onwards have 25 buildings with a max height of 25 storeys
//endSpacing ensures the buildings are centred on the screen
void Level::generateBuildings()
{
	int maxStoreys, buildingCount, endSpacing;
	//int levelNum = 1;

//	if (levelNum == 1)
//	{
		maxStoreys = buildingCount = 15;
		endSpacing = 205;
	//	}
	//	else if (stateMan.getLevelNumber() < 5)
	//{
	//maxStoreys = buildingCount = 15 + 2 * (levelNum - 1);
	//endSpacing = 160 - (levelNum - 1) * 32;
	//}
	//else
	//{
	//maxStoreys = buildingCount = 25;
//	endSpacing = 0;
	//}

	for (int i = 0; i<buildingCount; ++i)
	{
		std::shared_ptr<Building> b = std::make_shared<Building>(groundLevel, endSpacing + i * 40, skyColor, maxStoreys);
		b->setTexture(mediaCache.getImage(b->getImage()));
		buildings.push_back(b);
	}
}

void Level::generateClouds()
{
	for (int i = 0; i<5; ++i)
	{
		std::shared_ptr<Cloud> c = std::make_shared<Cloud>(mediaCache.scrWidth());
		c->setTexture(mediaCache.getImage(c->getImage()));
		clouds.push_back(c);
	}
}

void Level::generateBomb()
{
	if (bomb == nullptr)
	{
		bomb = std::make_unique<Bomb>();
		bomb->setTexture(mediaCache.getImage(bomb->getImage()));

		double bombPosX = plane->getX() + (plane->getBox().w - bomb->getBox().w) / 2;

		if (bombPosX > 0 && bombPosX < mediaCache.scrWidth())
		{
			bomb->setPosition(bombPosX, plane->getPosition().y + plane->getBox().h);
		}
		else
		{
			bomb = nullptr;
		}
	}
}

void Level::parkPlane()
{
	plane->setToPark();

	Vector2D parkVector;
	parkVector.x = (mediaCache.scrWidth() - 4 * plane->getBox().w) - plane->getPosition().x;
	parkVector.y = (groundLevel - plane->getBox().h) - plane->getPosition().y;

	plane->setDirection(parkVector);
}

void Level::udpateClouds(const double deltaTime)
{
	for (auto& cloud : clouds)
	{
		cloud->move(mediaCache.scrWidth(), deltaTime);
	}
}

//if the plane isn't parked and hasn't crashed move it across and check to see if it has crashed
//if it crashes, play the sound effect, create the dust cloud, set the plane to crashed and take the player's life away
//the first time we find that it is parked, make a note of the time
void Level::updatePlane(const double deltaTime)
{
	if (!plane->isParked() && !plane->hasCrashed())
	{
		plane->move(deltaTime, mediaCache.scrWidth(), groundLevel, 1, true);

		for (const auto& building : buildings)
		{
			if (CollisionEngine::checkCollision(plane->getBox(), building->getBox()))
			{
				mediaCache.playEffect(-1, mediaCache.getEffect("files/sounds/crash.ogg"), 0);

				Point2D p(plane->getBox().x + plane->getBox().w, plane->getBox().y + 0.5*plane->getBox().h);
				pEngines.push_back(std::make_shared<ParticleEngine>(mediaCache, p));

				plane->crash();
				player.loseLife();
			}
		}
	}
	else if (plane->isParked() && timeParked == 0)
	{
		planeParked = true;
		timeParked = SDL_GetTicks();
		mediaCache.fadeOutMusic(1000);
	}
}

void Level::updateBomb(const double deltaTime)
{
	//only run the code if the bomb exists
	if (bomb != nullptr)
	{
		bomb->move(groundLevel, deltaTime);

		//flag to let us know if we need to destroy the bomb
		bool bombDestroyed = false;

		//check if the bomb hits any of the buildings
		auto b = std::begin(buildings);
		while (b != std::end(buildings))
		{
			//if it hits then play the sound effect, create a particle engine for smoke and remove the building as it's destroyed
			if (CollisionEngine::checkCollision((*b)->getBox(), bomb->getBox()))
			{
				mediaCache.playEffect(-1, mediaCache.getEffect("files/sounds/explode.ogg"), 0);

				Point2D smokePos = bomb->getPosition();
				pEngines.push_back(std::make_shared<ParticleEngine>(mediaCache, smokePos));

				(*b)->hitByBomb(groundLevel);

				if ((*b)->isDestroyed())
				{
					levelScore += (*b)->getScore();
					b = buildings.erase(b);
				}
				else
				{
					++b;
				}

				bombDestroyed = true;
			}
			else
			{
				++b;
			}
		}

		//if the bomb is offScreen (i.e. hit the ground) we need an explosion
		if (bomb->isOffScreen())
		{
			mediaCache.playEffect(-1, mediaCache.getEffect("files/sounds/explode.ogg"), 0);

			Point2D smokePos = bomb->getPosition();
			pEngines.push_back(std::make_shared<ParticleEngine>(mediaCache, smokePos));

			bombDestroyed = true;
		}

		//if the bomb has been flagged as destroyed, then delete it by pointing it at nullptr
		if (bombDestroyed)
		{
			bomb = nullptr;
		}
	}
}

void Level::updateParticleEngines()
{
	auto engine = std::begin(pEngines);
	while (engine != std::end(pEngines))
	{
		if ((*engine)->isRunning())
		{
			(*engine)->manage();
			++engine;
		}
		else
		{
			engine = pEngines.erase(engine);
		}
	}
}