#include "Bomb.h"

Bomb::Bomb() : Sprite("files/images/bomb/bomb.bmp"),
				speed(150),
				height(24),
				width(13),
				offScreen(false)
{
	position.set(0, 0);
	direction.set(0, 1);

	mBox.w = width;
	mBox.h = height;
}

Bomb::~Bomb()
{

}

void Bomb::setTexture(const std::shared_ptr<GameTexture> gt)
{
	gameTex = gt;
}

void Bomb::setPosition(const double x, const double y)
{
	position.set(x, y);
}

const SDL_Rect Bomb::getBox() 
{
	mBox.x = static_cast<Sint16>(position.x);
	mBox.y = static_cast<Sint16>(position.y);
	return mBox;
}

const bool Bomb::isOffScreen() const 
{ 
	return offScreen; 
}


void Bomb::setOffScreen(const bool newOffScreen) 
{ 
	offScreen = newOffScreen; 
}

void Bomb::move(const int groundLevel, const double deltaTime)
{
    position.y += direction.y * speed * deltaTime;

    if(position.y + height > groundLevel)
    {
		offScreen = true;
	}
}
