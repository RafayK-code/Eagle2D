#include "egpch.h"
#include "PhysicsSystem.h"

#include "Mathematics.h"
#include "Transform.h"
#include "RigidBody.h"

static Uint32 elapsed;
static Uint32 lastFrame;

namespace Eagle
{
	PhysicsSystem::PhysicsSystem(ECS::Manager* man)
		: _Manager(man), _Window(nullptr)
	{
		EG_CORE_INFO("Physics system created.");
	}

	PhysicsSystem::~PhysicsSystem()
	{
		EG_CORE_WARN("Physics system destroyed.");
	}

	void PhysicsSystem::Init(Window* window)
	{
		_Window = window;

		for (const ECS::EntityID entity : _Entities)
		{
			Transform& t = _Manager->GetComponent<Transform>(entity);
			RigidBody& rb = _Manager->GetComponent<RigidBody>(entity);

			rb.hitbox.position += t.transform.position;
		}

		elapsed = 0;
		lastFrame = 0;
	}

	void PhysicsSystem::Update()
	{
		while (_Window->IsOpen())
		{
			lastFrame = elapsed;
			elapsed = SDL_GetTicks();
			_Window->dt = (elapsed - lastFrame) / 1000.0f;

			for (const ECS::EntityID entity : _Entities)
			{
				Transform& transform = _Manager->GetComponent<Transform>(entity);
				RigidBody& rb = _Manager->GetComponent<RigidBody>(entity);

				Vector2f pos = transform.transform.position;
				Vector2f hitbox = rb.hitbox.position;

				//transform.transform.position += rb.velocity / ((float)m_Window->GetFrameRate() / 60.0f);
				transform.transform.position += rb.velocity * _Window->dt;
				rb.hitbox.position += rb.velocity * _Window->dt;
				rb.velocity += rb.acceleration;

				if (transform.transform.position != pos)
				{
					for (const ECS::EntityID col : _Entities)
					{
						if (col != entity)
						{
							RigidBody& colRb = _Manager->GetComponent<RigidBody>(col);
							if (rb.hitbox >> colRb.hitbox)
							{
								transform.transform.position = pos;
								rb.hitbox.position = hitbox;

								EG_CORE_TRACE("Collision Detected.");

								break;
							}
						}
					}
				}
			}

			int frameTime = SDL_GetTicks() - _Window->_FrameStart;

			if (_Window->_FrameRate != 0)
			{
				if (1000 / _Window->_FrameRate > frameTime)
				{
					SDL_Delay(1000 / _Window->_FrameRate - frameTime);
				}
			}

			_Window->_FrameStart = SDL_GetTicks();
		}
	}
}