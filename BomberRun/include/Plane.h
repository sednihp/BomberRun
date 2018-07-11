#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

#include "Sprite.h"
#include "SDL.h"

class Plane : public Sprite
{
    private:
        const Uint16 width, height;
		const int stepDown;
        const double planeX;
		double speed;
        SDL_Rect mBox;
		unsigned crashTime;
        bool offScreen, crashed, parking, landed, parked;

		Plane& operator=(const Plane&);
		Plane(const Plane&);

    public:
        Plane(const double planeY = 5);
        ~Plane();

		void setTexture(const std::shared_ptr<GameTexture> gt);

        const double getX() const { return position.x; }
        const bool isOffScreen() const { return offScreen; }
        const SDL_Rect getBox();
		void setDirection(const Vector2D newDir) { direction = newDir; }

        void move(const double deltaTime, const int screenWidth, const int groundLevel, const int level, const bool stepDown);

		void crash();
		const bool hasCrashed() const { return crashed; }
		const bool isAlive();
		void setToPark();
		const bool isParking() const;
		const bool isParked() const;
};

#endif // CANNON_H_INCLUDED
