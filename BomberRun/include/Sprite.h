#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#include "Vectors.h"
#include <string>
#include "GameTexture.h"
#include "MediaCache.h"

class Sprite
{
    protected:
        Point2D position;
        Vector2D direction;
        std::string image;
		std::shared_ptr<GameTexture> gameTex;

    public:
        Sprite(const std::string imgFile) :  position(),
											direction(),
											image(imgFile) {}
        virtual ~Sprite() {};

        virtual const Point2D getPosition() const { return position; }
        virtual const Vector2D getDirection() const { return direction; }
        virtual const std::string getImage() const { return image; }
		virtual const std::shared_ptr<GameTexture> getTexture() const { return gameTex; }
		virtual void setTexture(const std::shared_ptr<GameTexture> gt) = 0;
};

#endif // SPRITE_H_INCLUDED
