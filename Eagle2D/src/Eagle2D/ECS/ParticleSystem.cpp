#include "egpch.h"
#include "ParticleSystem.h"
#include "Logging/Log.h"

#include "Particle.h"
#include "Transform.h"

static Uint32 elapsed;
static Uint32 lastFrame;

namespace Eagle
{
	ParticleSystem::ParticleSystem(ECS::Manager* man)
		: _Manager(man), _Window(nullptr)
	{
		EG_CORE_INFO("Particle system created.");
	}

	ParticleSystem::~ParticleSystem()
	{
		EG_CORE_WARN("Particle system destroyed.");
	}

	void ParticleSystem::Init(Window* window)
	{
		_Window = window;

		for (const ECS::EntityID entity : _Entities)
		{
			Particle& particle = _Manager->GetComponent<Particle>(entity);
			particle.lifeTime += SDL_GetTicks();
		}
	}

	void ParticleSystem::Update()
	{
		lastFrame = elapsed;
		elapsed = SDL_GetTicks();
		_Window->dt = (elapsed - lastFrame) / 1000.0f;

		for (const ECS::EntityID entity : _Entities)
		{
			Particle& particle = _Manager->GetComponent<Particle>(entity);
			Transform& t = _Manager->GetComponent<Transform>(entity);

			t.transform.position += particle.velocity * _Window->dt;
			particle.velocity += particle.acceleration * _Window->dt;
		}
	}
}