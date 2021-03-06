#include "egpch.h"
#include "PhysicsSystem.h"

#include "Mathematics.h"
#include "Transform.h"
#include "RigidBody.h"

namespace Eagle
{
	PhysicsSystem::PhysicsSystem(ECS::Manager* man)
		: m_Manager(man)
	{
		EG_INFO("Physics system created.");
	}

	PhysicsSystem::~PhysicsSystem()
	{
		EG_WARN("Physics system destroyed.");
	}

	void PhysicsSystem::Init()
	{
		for (const ECS::EntityID entity : m_Entities)
		{
			Transform& t = m_Manager->GetComponent<Transform>(entity);
			RigidBody& rb = m_Manager->GetComponent<RigidBody>(entity);

			rb.hitbox.position += t.transform.position;
		}
	}

	void PhysicsSystem::Update()
	{
		for (const ECS::EntityID entity : m_Entities)
		{
			Transform& transform = m_Manager->GetComponent<Transform>(entity);
			RigidBody& rb = m_Manager->GetComponent<RigidBody>(entity);

			Vector2f pos = transform.transform.position;
			Vector2f hitbox = rb.hitbox.position;

			transform.transform.position += rb.velocity;
			rb.hitbox.position += rb.velocity;
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

							EG_TRACE("Collision Detected.");

							break;
						}
					}
				}
			}
		}
	}
}