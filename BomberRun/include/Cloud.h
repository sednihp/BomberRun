#ifndef CLOUD_H
#define CLOUD_H
#include "Sprite.h"


class Cloud : public Sprite
{
	private:
		const int width, height;
		int speed; 

		void setImage();

		Cloud& operator=(const Cloud&);
		Cloud(const Cloud&);

	public:
		Cloud(const int scrWidth);
		~Cloud();

		void move(const int scrWidth, const double deltaTime);
		void setTexture(const std::shared_ptr<GameTexture> gt);
};

#endif