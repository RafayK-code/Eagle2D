#include "egpch.h"
#include "Eagle2D.h"
#include <SDL.h>
#include <SDL_image.h>
#include <gl/gl.h>


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

void Eagle::EventScript(SDL_Event event)
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
	window.SetFrameRate(240);

	aManager.Init(&window);

	Eagle::EventHandler handler;

	aManager.AddTexture("assets/goblin_king.png", "goblin");
	aManager.AddTexture("assets/light.png", "shadow");
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

	Eagle::Transform& t = manager.GetComponent<Eagle::Transform>(wall);

	renderSystem->Init(&aManager);
	physicsSystem->Init();

	SDL_SetTextureBlendMode(aManager.GetTexture("shadow"), SDL_BLENDMODE_ADD);

	SDL_Texture* rend_shadow = SDL_CreateTexture(window.m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
	SDL_SetTextureBlendMode(rend_shadow, SDL_BLENDMODE_MOD);

	while (window.IsOpen())
	{
		//window.Clear();
		physicsSystem->Update();
		//renderSystem->Update();
		//SDL_Rect rect = { rb.hitbox.position.x, rb.hitbox.position.y, rb.hitbox.scale.x, rb.hitbox.scale.y, };
		//SDL_SetRenderDrawColor(window.m_Renderer, 255, 0, 255, 255);
		//SDL_RenderDrawRect(window.m_Renderer, &rect);
		//SDL_Rect rect2 = { 0, 0, 1280, 720 };
		//SDL_Rect src = { 0, 0, 64, 64 };
		//SDL_RenderCopy(window.m_Renderer, aManager.GetTexture("shadow"), nullptr, &rect2)

		//SDL_SetRenderDrawColor(window.m_Renderer, 0, 0, 0, 255);
		SDL_SetRenderDrawColor(window.m_Renderer, 0, 0, 0, 255);

		SDL_Rect light = { trans.transform.position.x - 200, trans.transform.position.y - 200, 400, 400 };
		SDL_Rect player = { trans.transform.position.x, trans.transform.position.y, 64, 64 };
		SDL_Rect wall = { 800, 100, 20, 300 };
		SDL_SetRenderTarget(window.m_Renderer, rend_shadow);
		SDL_RenderClear(window.m_Renderer);
		SDL_RenderCopy(window.m_Renderer, aManager.GetTexture("shadow"), nullptr, &light);

		handler.HandleEvents();
		SDL_SetRenderTarget(window.m_Renderer, NULL);
		SDL_RenderClear(window.m_Renderer);
		SDL_RenderCopy(window.m_Renderer, aManager.GetTexture("goblin"), nullptr, &player);
		SDL_RenderCopy(window.m_Renderer, aManager.GetTexture("goblin"), nullptr, &wall);
		SDL_RenderCopy(window.m_Renderer, rend_shadow, nullptr, nullptr);

		window.Update();
	}

	return 0;
}