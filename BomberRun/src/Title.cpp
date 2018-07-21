#include "Title.h"
#include "Engine.h"
#include "Level.h"

Title::Title(MediaCache& mc, Player& p) : State(mc, p), 
											font(mediaCache.getFont(125)),
											menuFont(mediaCache.getFont(100))
{
	if (!mediaCache.isPlayingMusic())
	{
		mediaCache.playMusic(mediaCache.getMusic("files/sounds/understanding.ogg"), 1);
	}

	SDL_Color c = {255, 0, 0};
	title = mediaCache.getText("Bomber Run", font, c);
	title->setPosition(mediaCache.centreX(title->getW()), 0);

	menu.push_back(mediaCache.getText("Play", menuFont, c));
	menu.push_back(mediaCache.getText("High Scores", menuFont, c));
	menu.push_back(mediaCache.getText("Exit", menuFont, c));

	for(size_t i=0; i<menu.size(); ++i)
	{
		menu[i]->setPosition(mediaCache.centreX(menu[i]->getW()), mediaCache.centreY(menu[i]->getH()) + i*menu[i]->getH());
	}
}

Title::~Title()
{
}

void Title::enter(Engine*)
{
	if (!mediaCache.isPlayingMusic())
	{
		mediaCache.playMusic(mediaCache.getMusic("files/sounds/understanding.ogg"), 1);
	}
}

void Title::handleEvents(SDL_Event& e, Engine* engine)
{
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void Title::update(const double, Engine*)
{
}

void Title::render()
{
	mediaCache.renderTexture(title, title->getX(), title->getY());

	for(auto& item : menu)
	{
		mediaCache.renderTexture(item, item->getX(), item->getY());
	}
}

void Title::exit(Engine* )
{
	mediaCache.stopMusic();
}

//====================
//====================

void Title::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::checkCollision(menu[0]->getBox(), x, y))
		{
			engine->changeState(std::make_shared<Level>(mediaCache, player));
		}
		else if (CollisionEngine::checkCollision(menu[1]->getBox(), x, y))
		{
			//engine->changeState(std::make_shared<HighScore>(mediaCache));
		}
		else if (CollisionEngine::checkCollision(menu[2]->getBox(), x, y))
		{
			engine->stopRunning();
		}
	}
}