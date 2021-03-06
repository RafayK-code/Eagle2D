#pragma once
#pragma warning(push)
#pragma warning(disable:4251)

#include "Core.h"

#include "ECS/ECS.h"

#include "Graphics/Window.h"
#include "Graphics/AssetManager.h"

#include "Mathematics.h"

namespace Eagle
{
	void EventScript(SDL_Event event);
}

#include "EventHandler.h"

#pragma warning(pop)