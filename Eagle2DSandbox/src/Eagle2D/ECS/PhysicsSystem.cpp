#include "PhysicsSystem.h"

#include "Mathematics.h"
#include "Transform.h"
#include "RigidBody.h"

namespace Eagle
{
	PhysicsSystem::PhysicsSystem(ECS::Manager* man)
		: manager(man)
	{
	}

	PhysicsSystem::~PhysicsSystem()
	{
	}

	void PhysicsSystem::Init()
	{
		for (const ECS::EntityID entity : m_Entities)
		{
			Transform& t = manager->GetComponent<Transform>(entity);
			RigidBody& rb = manager->GetComponent<RigidBody>(entity);

			rb.hitbox.position += t.transform.position;
		}
	}

	void PhysicsSystem::Update()
	{
		for (const ECS::EntityID entity : m_Entities)
		{
			Transform& transform = manager->GetComponent<Transform>(entity);
			RigidBody& rb = manager->GetComponent<RigidBody>(entity);

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
						RigidBody& colRb = manager->GetComponent<RigidBody>(col);
						if (rb.hitbox >> colRb.hitbox)
						{
							transform.transform.position = pos;
							rb.hitbox.position = hitbox;
							break;
						}
					}
				}
			}
		}
	}
}