#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H
#include "Particle.h"
#include <vector>

class ParticleEngine
{
    private:
        const unsigned int numberOfParticles;
        const unsigned int engineTime;
        Point2D position;
        std::vector<std::shared_ptr<Particle>> particles;
        const int startTime;
		MediaCache& mediaCache;

		ParticleEngine& operator=(const ParticleEngine&);
		ParticleEngine(const ParticleEngine&);

    public:
        ParticleEngine(MediaCache& mc, Point2D point);
        ~ParticleEngine();

        void manage();
        const bool isRunning();

		std::vector<std::shared_ptr<Particle>>::iterator begin() { return particles.begin(); }
		std::vector<std::shared_ptr<Particle>>::iterator end() { return particles.end(); }
};

#endif // PARTICLEENGINE_H
