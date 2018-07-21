#include "MediaCache.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"

MediaCache::MediaCache() :	mScrWidth(1024), mScrHeight(768),
							window(nullptr), ren(nullptr), 
							imgCache(ren), fontCache(ren), txtCache(ren), audioCache()
{
	window = SDL_CreateWindow("Bomber Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mScrWidth, mScrHeight, SDL_WINDOW_SHOWN);
	if(!window)
	{
		std::cout << SDL_GetError() << std::endl;
		exit(2);
	}

	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!ren)
	{
		std::cout << SDL_GetError() << std::endl;
		exit(3);
	}
}

MediaCache::~MediaCache()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);

    SDL_Quit();
}

//=====
//ImageCache
//=====

std::shared_ptr<GameTexture> MediaCache::getImage(std::string file)
{
	return imgCache.getImage(file);
}

//=====
//FontCache
//=====

TTF_Font* MediaCache::getFont(int size)
{
	return fontCache.getFont(size);
}

//=====
//TextCache
//=====

std::shared_ptr<GameTexture> MediaCache::getText(std::string message, TTF_Font* font, SDL_Color color)
{
	return txtCache.getText(message, font, color);
}

//=====
//AudioCache
//=====

Mix_Music* MediaCache::getMusic(const std::string filename) 
{
	return audioCache.getMusic(filename);
}

Mix_Chunk* MediaCache::getEffect(const std::string filename) 
{
	return audioCache.getEffect(filename);
}

const bool MediaCache::isPlayingMusic() 
{
	return audioCache.isPlayingMusic();
}

void MediaCache::playMusic(Mix_Music* m, const int loops) 
{
	return audioCache.playMusic(m, loops);
}

void MediaCache::playEffect(const int channel, Mix_Chunk* effect, const int loops) 
{
	return audioCache.playEffect(channel, effect, loops);
}

void MediaCache::stopMusic() 
{
	return audioCache.stopMusic();
}

void MediaCache::stopChannel(const int channel) 
{
	return audioCache.stopChannel(channel);
}

void MediaCache::fadeOutMusic(const int ms) 
{
	return audioCache.fadeOutMusic(ms);
}

void MediaCache::togglePause(const int channel)
{
	return audioCache.togglePause(channel);
}

void MediaCache::toggleMute() 
{
	return audioCache.toggleMute();
}

const bool MediaCache::isMuted()
{
	return audioCache.isMuted();
}

#include "Vectors.h"

void MediaCache::renderTexture(std::shared_ptr<GameTexture> tex, const int x, const int y)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
	pos.w = tex->getW();
	pos.h = tex->getH();
 
	SDL_RenderCopy(ren, tex->texture(), NULL, &pos);
}

void MediaCache::drawRectangle(SDL_Rect rect, SDL_Color c)
{
	SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(ren, &rect);
}

void MediaCache::clearScreen()
{ 
	SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE); 
	SDL_RenderClear(ren); 
}

int MediaCache::centreX(int gtWidth) const
{
	return (mScrWidth - gtWidth) / 2;
}

int MediaCache::centreY(int gtHeight) const
{
	return (mScrHeight - gtHeight) / 2;
}