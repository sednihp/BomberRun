#include "Plane.h"

Plane::Plane(const double planeStartY) : Sprite("files/images/plane/plane.bmp"),
										width(84),
										height(39),                                            
										stepDown(height),
										speed(120),
										planeX(-width),
										offScreen(false), crashed(false),
										parking(false), landed(false), parked(false)
{
    position.set(planeX, planeStartY);
    direction.set(1, 0);

    mBox.w = width;
    mBox.h = height;
}

Plane::~Plane()
{

}

void Plane::setTexture(const std::shared_ptr<GameTexture> gt)
{
	gameTex = gt;
}

const SDL_Rect Plane::getBox()
{
    mBox.x = static_cast<Sint16>(position.x);
    mBox.y = static_cast<Sint16>(position.y);
    return mBox;
}

void Plane::setToPark()
{ 
	parking = true; 
}

const bool Plane::isParking() const
{ 
	return parking; 
}

const bool Plane::isParked() const 
{ 
	return parked; 
}

void Plane::crash() 
{ 
	crashTime = SDL_GetTicks(); 
	crashed = true; 
}

const bool Plane::isAlive()
{
	if(!crashed)
	{
		return true;
	}
	else
	{
		if(SDL_GetTicks() - crashTime > 350)
		{
			return false;
		}

		return true;
	}
}

void Plane::move(const double deltaTime, const int screenWidth, const int groundLevel, const int level, const bool moveDown)
{
	//if the plane isn't in parking mode move it across the screen
	//when it goes off the screen move it back to the left and move it down and speed it up if allowed
	if(!parking && !crashed)
	{
		position.x += direction.x * speed * deltaTime;

		if (position.x > screenWidth)
		{
			offScreen = true;
			position.x = planeX;
			if(moveDown)
			{
				position.y += stepDown;
				speed += 4*level;
			}
		}
	}
	//if the plane is parking and is over halfway across the screen, move it across until it goes off the screen
	//then move it back across to the LHS of the screen, land it and then park it
	else if(parking)
	{
		speed = 150;
		int landingX = screenWidth - 4*width;
		int parkingX = screenWidth - 2*width;
		int parkingY = groundLevel - height;

		direction.normalize();
		
		if(position.x >= screenWidth / 2)
		{
			position.x += 1 * speed * deltaTime;

			if(position.x > screenWidth)
			{
				position.x = planeX;

				Vector2D landingVector;
				landingVector.x = landingX - position.x;
				landingVector.y = parkingY  - position.y;

				setDirection(landingVector);

				direction.normalize();
			}			
		}
		else
		{
			position.x += direction.x * speed * deltaTime;
		}

		position.y += direction.y * speed * deltaTime;

		if(!landed && position.x >= landingX && position.y >= parkingY)
		{
			landed = true;
			direction.set(parkingX - position.x, 0);
		}
		else if(landed && position.x >= parkingX)
		{
			parked = true;
		}
	}
}