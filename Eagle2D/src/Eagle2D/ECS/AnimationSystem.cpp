#include "egpch.h"
#include "AnimationSystem.h"

#include "Sprite.h"
#include "Animation.h"

namespace Eagle
{
	AnimationSystem::AnimationSystem(ECS::Manager* man)
		: _Manager(man)
	{
	}

	AnimationSystem::~AnimationSystem()
	{
	}

	void AnimationSystem::Init()
	{
	}

	void AnimationSystem::Update()
	{
		for (const ECS::EntityID entity : _Entities)
		{
			Sprite& sprite = _Manager->GetComponent<Sprite>(entity);
			Animation& animation = _Manager->GetComponent<Animation>(entity);

			sprite.src.x = sprite.src.w * static_cast<int>((SDL_GetTicks() / animation.speed) % animation.frames[animation.currentIndex]);
			sprite.src.y = animation.currentIndex * sprite.src.h;
		}
	}
}