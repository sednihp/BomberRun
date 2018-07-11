#include "Particle.h"
#include <stdlib.h>

Particle::Particle(Point2D point) : Sprite("")
{
    //Set where the particle will appear relative to 'point'
    int xDir = 0, yDir = 0;
    switch(rand() % 4)
    {
        case 0: xDir = 1; yDir = 1; break;
        case 1: xDir = -1; yDir = 1; break;
        case 2: xDir = 1; yDir = -1; break;
        case 3: xDir = -1; yDir = -1; break;
    }

    //ensure that the smoke appears in a circular shape
    do
    {
		position.set(point.x + (xDir * (rand() % 75)), point.y + (yDir * (rand() % 75)));
    }
    while(distance(point, position) > 75);

	chooseImage(point);

    //randomize animation
    frame = rand() % 5;
}

void Particle::setTexture(const std::shared_ptr<GameTexture> gt)
{
	gameTex = gt;
}

//use pythag to find the distance between two points
inline const double Particle::distance(const Point2D p1, const Point2D p2) const
{
    return sqrt( (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y) );
}

//set the particle's image depending on how far from the centre it is
void Particle::chooseImage(const Point2D point)
{
	double dist = distance(point, position);
	if(dist < 20)
	{
		image = "files/images/particles/red.bmp";
	}
	else if(dist < 40)
	{
		image = "files/images/particles/orange.bmp";
	}
	else if(dist < 60)
	{
		image = "files/images/particles/yellow.bmp";
	}
	else
	{
		image = smokeImage();
	}
}

//randomize between light and dark grey particles
const std::string Particle::smokeImage()
{
	switch(rand() % 2)
	{
		case 0 : return "files/images/particles/light grey.bmp";
		case 1 : return "files/images/particles/dark grey.bmp";

		default: return "files/images/particles/black.bmp";
	}   
}

//increase the frame number
void Particle::manage()
{
    ++frame;
}

//if the frame count is over 10, the particle has expired
bool Particle::isDead()
{
    return frame > 10;
}
