#include "Building.h"

Building::Building(const int groundLevel,
					const int x, 
					const SDL_Color skyColor, 
					const int maxStoreys) : Sprite("files/images/building/building.png"),
                                                width(32),
                                                storeyHeight(25),
                                                destroyed(false)
{
	//randomly generate the number of storeys, add 1 to ensure it isn't 0
    numberOfStoreys = (rand() % maxStoreys) + 1;

	//find the height of the building and then build it's bounding SDL_Rect
    height = static_cast<Uint16>(numberOfStoreys * storeyHeight);
    mBox.x = static_cast<Sint16>(x);
    mBox.y = static_cast<Sint16>(groundLevel - height);
    mBox.w = width;
    mBox.h = height;

	//the position of a sprite is always the top left corner
	position.set(x, mBox.y);

	//randomly generate a color
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;

	//ensure the building's colour isn't too close to the skybox color
    if(color.r > skyColor.r - 20 && color.r < skyColor.r + 20)
	{
		color.r -= ((rand() % 50) + 50);
	}
	if(color.g > skyColor.g - 20 && color.g < skyColor.g + 20)
	{
		color.g -= ((rand() % 50) + 50);
	}
	if(color.b > skyColor.b - 20 && color.b < skyColor.b + 20)
	{
		color.b -= ((rand() % 50) + 50);
	}

	//the buildings score is it's height
    score = numberOfStoreys;

	//if a building is over 15 storeys high it takes 2 hits to destroy
    if(numberOfStoreys > 15)
    {
        hitpoints = 2;
    }
    else
    {
        hitpoints = 1;
    }
}

Building::~Building()
{

}

void Building::setTexture(const std::shared_ptr<GameTexture> gt) 
{
	gameTex = gt;
}

//remove a hitpoint
//if that leaves 0 hitpoints, the building is destroyed
//otherwise halve the numberOfStoreys and recalculate the SDL_Rect and position
void Building::hitByBomb(const int groundLevel)
{
	--hitpoints;

    if(hitpoints == 0)
    {
        destroyed = true;
    }
    else
    {
        numberOfStoreys /= 2;
        height = static_cast<Uint16>(numberOfStoreys * storeyHeight);
        mBox.h = height;
        mBox.y = static_cast<Sint16>(groundLevel - height);
        position.y = mBox.y;
    }
}
