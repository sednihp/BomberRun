#include "ParticleEngine.h"
#include "SDL.h"
#include <algorithm>

ParticleEngine::ParticleEngine(MediaCache& mc, Point2D point) : mediaCache(mc),
																numberOfParticles(300),
																engineTime(350),
																position(point.x + 4, point.y + 10),
																startTime(SDL_GetTicks())
{
    for(unsigned p = 0; p < numberOfParticles; p++ )
    {
		std::shared_ptr<Particle> particle = std::make_shared<Particle>(position);
		particle->setTexture(mediaCache.getImage(particle->getImage()));
        particles.push_back(particle);
    }
}

ParticleEngine::~ParticleEngine()
{
}

//as soon as the engine has been running for longer than engineTime this will return false
const bool ParticleEngine::isRunning()
{
    return SDL_GetTicks() - startTime < engineTime;
}

//manage every particle then delete, nullify, remove and erase all dead particles and top up particles so there are 400 of them
void ParticleEngine::manage()
{
	auto particle = std::begin(particles);
	while (particle != std::end(particles))
	{
		(*particle)->manage();

		if ((*particle)->isDead())
		{
			particle = particles.erase(particle);
		}
		else
		{
			++particle;
		}
	}

	for(unsigned i=0; i < numberOfParticles - particles.size(); ++i)
	{
		std::shared_ptr<Particle> p = std::make_shared<Particle>(position);
		p->setTexture(mediaCache.getImage(p->getImage()));
		particles.push_back(p);
	}
}
