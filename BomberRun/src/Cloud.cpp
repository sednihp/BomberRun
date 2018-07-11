#include "Cloud.h"


Cloud::Cloud(const int scrWidth) : Sprite(""),
									width(250),
									height(150),
									speed(rand() % 50 + 10)
{
	//create the cloud at a random position, with a random image and moving either left or right
	position.set(rand() % scrWidth, rand() % 400);

	setImage();

	switch(rand() % 2)
	{
		case 0: direction.set(1,0);
				break;
		case 1: direction.set(-1,0);
				break;
	}
}

#include <iostream>

//randomize the cloud's appearance
void Cloud::setImage()
{
	switch(rand() % 4)
	{
		case 0: image = "files/images/clouds/cloud.bmp";
				break;
		case 1: image = "files/images/clouds/cloud2.bmp";
				break;
		case 2: image = "files/images/clouds/cloud3.bmp";
				break;
		case 3: image = "files/images/clouds/cloud4.bmp";
				break;
	}
}

Cloud::~Cloud()
{
}

//if the cloud goes off screen, reverse it's direction and randomize the y coordinate, speed and image
void Cloud::move(const int scrWidth, const double deltaTime)
{
	position.x += direction.x * speed * deltaTime;

	if(position.x + width < 0 || position.x > scrWidth)
	{
		direction.x *= -1;
		position.y = rand() % 300;
		speed = rand() % 50 + 10;
		setImage();
	}
}

void Cloud::setTexture(const std::shared_ptr<GameTexture> gt) 
{
	gameTex = gt;
}