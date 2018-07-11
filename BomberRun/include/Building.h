#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED
#include "SDL.h"
#include <string>
#include "Sprite.h"

class Building : public Sprite
{
    private:
		const Uint16 width;
        const int storeyHeight;
        int numberOfStoreys;
		Uint16 height;
        SDL_Rect mBox;
        SDL_Color color;
        int score, hitpoints;
        bool destroyed;

		Building& operator=(const Building&);
		Building(const Building&);

    public:
        Building(const int groundLevel, const int x, const SDL_Color skyColor, const int maxStoreys = 25);
        ~Building();

		void setTexture(const std::shared_ptr<GameTexture> gt);
        const SDL_Rect getBox() const { return mBox; }
        const SDL_Color getColor() const { return color; }
        const int getNumberOfStoreys() const { return numberOfStoreys; }
        const int getStoreyHeight() const { return storeyHeight; }
        const int getScore() const { return score; }
        const bool isDestroyed() const { return destroyed; }

        void hitByBomb(const int groundLevel);
};

#endif // BUILDING_H_INCLUDED
