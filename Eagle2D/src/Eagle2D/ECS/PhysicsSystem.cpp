#include "egpch.h"
#include "PhysicsSystem.h"

#include "Mathematics.h"
#include "Transform.h"
#include "RigidBody.h"

Uint32 elapsed;
Uint32 lastFrame;

namespace Eagle
{
	PhysicsSystem::PhysicsSystem(ECS::Manager* man)
		: m_Manager(man)
	{
		EG_CORE_INFO("Physics system created.");
	}

	PhysicsSystem::~PhysicsSystem()
	{
		EG_CORE_WARN("Physics system destroyed.");
	}

	void PhysicsSystem::Init(Window* window)
	{
		m_Window = window;

		for (const ECS::EntityID entity : m_Entities)
		{
			Transform& t = m_Manager->GetComponent<Transform>(entity);
			RigidBody& rb = m_Manager->GetComponent<RigidBody>(entity);

			rb.hitbox.position += t.transform.position;
		}

		elapsed = 0;
		lastFrame = 0;
	}

	void PhysicsSystem::Update()
	{
		lastFrame = elapsed;
		elapsed = SDL_GetTicks();
		m_Window->dt = (elapsed - lastFrame) / 1000.0f;

		for (const ECS::EntityID entity : m_Entities)
		{
			Transform& transform = m_Manager->GetComponent<Transform>(entity);
			RigidBody& rb = m_Manager->GetComponent<RigidBody>(entity);

			Vector2f pos = transform.transform.position;
			Vector2f hitbox = rb.hitbox.position;

			//transform.transform.position += rb.velocity / ((float)m_Window->GetFrameRate() / 60.0f);
			transform.transform.position += rb.velocity * m_Window->dt;
			rb.hitbox.position += rb.velocity * m_Window->dt;
			rb.velocity += rb.acceleration;

			if (transform.transform.position != pos)
			{
				for (const ECS::EntityID col : m_Entities)
				{
					if (col != entity)
					{
						RigidBody& colRb = m_Manager->GetComponent<RigidBody>(col);
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
	}
}