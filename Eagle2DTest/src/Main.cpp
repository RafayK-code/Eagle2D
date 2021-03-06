#include "egpch.h"
#include "Eagle2D.h"
#include <SDL.h>
#include <SDL_image.h>


#include "ECS/Transform.h"
#include "ECS/Sprite.h"
#include "ECS/RigidBody.h"

#include "ECS/RenderSystem.h"
#include "ECS/PhysicsSystem.h"

Eagle::Window window;
Eagle::ECS::Manager manager;
Eagle::AssetManager aManager;

Eagle::ECS::EntityID goblin;

std::shared_ptr<Eagle::RenderSystem> renderSystem;
std::shared_ptr<Eagle::PhysicsSystem> physicsSystem;

void Eagle::EventHandler::EventScript(SDL_Event event)
{
	Transform& t = manager.GetComponent<Transform>(goblin);
	RigidBody& rb = manager.GetComponent<RigidBody>(goblin);

	if (event.type == SDL_QUIT)
	{
		window.Close();
	}

	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			rb.velocity.y = -3.0f;
			break;
		case SDLK_s:
			rb.velocity.y = 3.0f;
			break;
		case SDLK_a:
			rb.velocity.x = -3.0f;
			break;
		case SDLK_d:
			rb.velocity.x = 3.0f;
			break;
		}
	}

	if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			rb.velocity.y = 0;
			break;
		case SDLK_s:
			rb.velocity.y = 0;
			break;
		case SDLK_a:
			rb.velocity.x = 0;
			break;
		case SDLK_d:
			rb.velocity.x = 0;
			break;
		}
	}
}

int main(int agrc, char** argv)
{
	Eagle::Log::Init("APP");

	EG_ERROR("Welcome to test");

	window.Init("App", 1280, 720, SDL_WINDOW_OPENGL, SDL_RENDERER_ACCELERATED);
	window.SetFrameRate(60);

	aManager.Init(&window);

	Eagle::EventHandler handler;

	aManager.AddTexture("assets/goblin_king.png", "goblin");
	SDL_Rect rect = { 0, 0, 64, 64 };

	manager.Init();

	{
		Eagle::ECS::Signature signature;
		signature.set(manager.GetComponentType<Eagle::Transform>());
		signature.set(manager.GetComponentType<Eagle::RigidBody>());

		physicsSystem = manager.AddSystem<Eagle::PhysicsSystem>(signature);
	}

	{
		Eagle::ECS::Signature signature;
		signature.set(manager.GetComponentType<Eagle::Transform>());
		signature.set(manager.GetComponentType<Eagle::Sprite>());

		renderSystem = manager.AddSystem<Eagle::RenderSystem>(signature);
	}

	Eagle::ECS::EntityID wall = manager.CreateEntity();
	manager.AddComponent<Eagle::Transform>(wall, Eagle::Rect(800.0f, 100.0f, 20.0f, 300.0f), 0.0f);
	manager.AddComponent<Eagle::Sprite>(wall, "goblin", SDL_Rect{ 0, 0, 13, 25 });
	manager.AddComponent<Eagle::RigidBody>(wall, Eagle::Rect(0.0f, 0.0f, 20.0f, 280.0f));

	goblin = manager.CreateEntity();
	manager.AddComponent<Eagle::Transform>(goblin, Eagle::Rect(0.0f, 0.0f, 64.0f, 64.0f), 0.0f);
	manager.AddComponent<Eagle::Sprite>(goblin, "goblin", SDL_Rect{ 0, 0, 13, 25 });
	manager.AddComponent<Eagle::RigidBody>(goblin, Eagle::Rect(20.0f, 38.0f, 34.0f, 24.0f), Eagle::Vector2f(), Eagle::Vector2f());

	Eagle::Sprite& sprite = manager.GetComponent<Eagle::Sprite>(goblin);
	Eagle::Transform& trans = manager.GetComponent<Eagle::Transform>(goblin);
	Eagle::RigidBody& rb = manager.GetComponent<Eagle::RigidBody>(goblin);

	renderSystem->Init(&aManager);
	physicsSystem->Init();

	while (window.IsOpen())
	{
		SDL_Event event;
		Uint32 timeout = SDL_GetTicks() + 10;
		while (SDL_PollEvent(&event) && !SDL_TICKS_PASSED(SDL_GetTicks(), timeout))
		{
			handler.EventScript(event);
		}

		window.Clear();
		physicsSystem->Update();
		renderSystem->Update();
		SDL_Rect rect = { rb.hitbox.position.x, rb.hitbox.position.y, rb.hitbox.scale.x, rb.hitbox.scale.y, };
		SDL_SetRenderDrawColor(window.m_Renderer, 255, 0, 255, 255);
		SDL_RenderDrawRect(window.m_Renderer, &rect);
		window.Update();
	}

	manager.DestroyEntity(goblin);

	return 0;
}