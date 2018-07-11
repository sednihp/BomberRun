#ifndef PARTICLE_H
#define PARTICLE_H
#include "Sprite.h"

class Particle : public Sprite
{
    private:
        int frame;

        inline const double distance(const Point2D p1, const Point2D p2) const;
		void chooseImage(const Point2D point);
        void setImage(const std::string colour);
		const std::string smokeImage();

    public:
        Particle(Point2D point);
        ~Particle() {};

		void setTexture(const std::shared_ptr<GameTexture> gt);

        void manage();
        bool isDead();
};

#endif // PARTICLE_H
