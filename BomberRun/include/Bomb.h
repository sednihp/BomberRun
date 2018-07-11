#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "Sprite.h"
#include "SDL.h"

class Bomb : public Sprite
{
    private:
        const double speed;
        const Uint16 height, width;
        bool offScreen;
        SDL_Rect mBox;
		
		Bomb& operator=(const Bomb&);
		Bomb(const Bomb&);

    public:
		Bomb();
        ~Bomb();

		void setTexture(const std::shared_ptr<GameTexture> gt);
		void setPosition(const double x, const double y);

		const bool isOffScreen() const;
		void setOffScreen(const bool newOffScreen);
        const SDL_Rect getBox();

        void move(const int groundLevel, const double deltaTime);
};

#endif // BULLET_H_INCLUDED
