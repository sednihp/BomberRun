#ifndef MEDIACACHE_H
#define MEDIACACHE_H

#include "SDL.h"
#include <string>
#include "ImageCache.h"
#include "FontCache.h"
#include "TextCache.h"
#include "AudioCache.h"

class MediaCache
{
	private:
		const int mScrWidth, mScrHeight;
		SDL_Window* window;
		SDL_Renderer* ren;

		ImageCache imgCache;
		FontCache fontCache;
		TextCache txtCache;
		AudioCache audioCache;

		MediaCache& operator=(const MediaCache&);
		MediaCache(const MediaCache&);

	public:
		MediaCache();
		~MediaCache();

		//ImageCache
		std::shared_ptr<GameTexture> getImage(const std::string file);
		
		//FontCache
		TTF_Font* getFont(const int size);
		
		//TextCache
		std::shared_ptr<GameTexture> getText(const std::string message, TTF_Font* font, const SDL_Color color);

		//AudioCache
		Mix_Music* getMusic(const std::string filename);
		Mix_Chunk* getEffect(const std::string filename);
		const bool isPlayingMusic();
		void playMusic(Mix_Music* m, const int loops);
		void playEffect(const int channel, Mix_Chunk* effect, const int loops);
		void stopMusic();
		void stopChannel(const int channel);
		void fadeOutMusic(const int ms);
		void togglePause(const int channel);
		void toggleMute();
		const bool isMuted();

		void renderTexture(std::shared_ptr<GameTexture> tex, const int x, const int y);
		void drawRectangle(SDL_Rect rect, const SDL_Color color);

		void clearScreen();
		void updateScreen() { SDL_RenderPresent(ren); }

		int scrWidth() const { return mScrWidth; }
		int scrHeight() const { return mScrHeight; }
		int centreX(int gtWidth) const;
		int centreY(int gtHeight) const;

		template <typename T>
		void drawSpriteCntr(T& cntr)
		{
			for (const auto& s : cntr)
			{
				renderTexture(s->getTexture(), static_cast<int>(s->getPosition().x), static_cast<int>(s->getPosition().y));
			}
		}
};

#endif